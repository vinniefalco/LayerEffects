/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

LayerContext::LayerContext (BackgroundContext& destinationContext,
                            Rectangle <int> const& drawBounds)
  : ContextImageBase (
      destinationContext.getImageBounds ().getIntersection (drawBounds),
      Image::ARGB)
  , Graphics (getImage ())
  , m_destinationContext (destinationContext)
{
  getImage ().clear (getImage ().getBounds (), Colour::fromRGBA (0, 0, 0, 0));
  
  setOrigin (-getImageBounds ().getX (), -getImageBounds ().getY ());
} 

//------------------------------------------------------------------------------

LayerContext::~LayerContext ()
{
  Image workImage (
    Image::RGB,
    getImageBounds ().getWidth (),
    getImageBounds ().getHeight (),
    false);

  // Copy the background layer into the work image.
  copyImage (workImage,
             Point <int> (0, 0),
             m_destinationContext.getImage (),
             getImageBounds (),
             normal,
             1);

  // Draw effects from the bottom up.

  applyDropShadow (workImage);

  applyFill (workImage);

  applyInnerShadow (workImage);

  applyEuclideanDistanceMap (workImage);

  // Copy the work image onto the background layer
  // using normal mode and the general opacity.
  copyImage (m_destinationContext.getImage (),
             getImageBounds ().getTopLeft (),
             workImage,
             workImage.getBounds (),
             normal,
             m_options.general.opacity);
}

//------------------------------------------------------------------------------

LayerContext::Options& LayerContext::getOptions ()
{
  return m_options;
}

//------------------------------------------------------------------------------

void LayerContext::applyDropShadow (Image& workImage)
{
  Options::DropShadow& dropShadow = m_options.dropShadow;

  if (!dropShadow.active)
    return;

  int const dx = static_cast <int> (
    - dropShadow.distance * std::cos (dropShadow.angle) + 0.5) - dropShadow.size;
  
  int const dy = static_cast <int> (
    dropShadow.distance * std::sin (dropShadow.angle) + 0.5) - dropShadow.size;

  // Get the layer mask as an individual channel.
  Image mask = ChannelImageType::fromImage (getImage (), 3);
  
  RadialImageConvolutionKernel k (dropShadow.size + 1);
  k.createGaussianBlur ();

  // Compute the shadow mask.
  Image shadow = k.createConvolvedImageFull (mask);

  // Optionally subtract layer mask from shadow mask.
  if (dropShadow.knockout)
    copyImage (
      shadow,
      Point <int> (-dx, -dy),
      mask,
      mask.getBounds (),
      subtract,
      1);

  // Fill the shadow mask.
  fillImage (workImage,
             getImageBounds ().getTopLeft (),
             shadow,
             shadow.getBounds (),
             dropShadow.mode,
             dropShadow.opacity,
             dropShadow.colour);
}

//------------------------------------------------------------------------------

static void InvertImage (Image image)
{
  switch (image.getFormat ())
  {
  case Image::SingleChannel:
    {
      Image::BitmapData bits (image, Image::BitmapData::readWrite);

      uint8* dest = bits.getLinePointer (0);
      int const rowBytes = bits.lineStride - bits.width * bits.pixelStride;

      for (int y = bits.height; y--;)
      {
        for (int x = bits.width; x--;)
        {
          *dest = 255 - *dest;
          dest += bits.pixelStride;
        }

        dest += rowBytes;
      }
    }
    break;

  default:
    jassertfalse;
    break;
  }
}

void LayerContext::applyInnerShadow (Image& workImage)
{
  Options::InnerShadow& innerShadow = m_options.innerShadow;

  if (!innerShadow.active)
    return;

  int const dx = static_cast <int> (
    - innerShadow.distance * std::cos (innerShadow.angle) + 0.5) - innerShadow.size;
  
  int const dy = static_cast <int> (
    innerShadow.distance * std::sin (innerShadow.angle) + 0.5) - innerShadow.size;

  Image mask = ChannelImageType::fromImage (getImage (), 3);
  
  RadialImageConvolutionKernel k (innerShadow.size + 1);
  k.createGaussianBlur ();

  Image shadow = k.createConvolvedImage (mask);

  // Apply inner shadow using layer mask.
  fillImage (workImage,
             getImageBounds ().getTopLeft (),
             mask,
             mask.getBounds (),
             innerShadow.mode,
             innerShadow.opacity,
             innerShadow.colour);

  //InvertImage (shadow);

  // clip inverse shadow mask to interior of layer
  copyImage (shadow,
             Point <int> (0, 0),
             mask,
             mask.getBounds (),
             darken,
             1);
  // DO THIS CLIP FIRST so we have fewer pixels to process?
  //shadow = shadow.getClippedImage (mask.getBounds () + Point <int> (dx, dy));

  // Fill the shadow mask.
#if 0
  fillImage (workImage,
             getImageBounds ().getTopLeft (),
             shadow,
             shadow.getBounds (),
             innerShadow.mode,
             innerShadow.opacity,
             innerShadow.colour);
#endif
}

//------------------------------------------------------------------------------
void LayerContext::applyFill (Image& workImage)
{
  copyImage (workImage,
             getImageBounds ().getTopLeft (),
             getImage (),
             getImageBounds (),
             m_options.fill.mode,
             m_options.fill.opacity);
}

//------------------------------------------------------------------------------

struct CopyGray
{
  void operator () (uint8* dest, uint8 const* src) const
  {
    *dest = *src;
  }
};

float calcEuclideanDistance (Pixels const& mask, int x, int y, int radius)
{
  float dist = 1;

  int const x0 = jmax (x - radius, 0);
  int const x1 = jmin (x + radius, mask.width);
  int const y0 = jmax (y - radius, 0);
  int const y1 = jmin (y + radius, mask.height);

  for (int py = y0; py < y1; ++py)
  {
    for (int px = x0; px < x1; ++px)
    {
      uint8 const m = *mask.getPixelPointer (px, py);

      if (m != 0)
      {
        float d = sqrt (float(x-px)*(x-px)+(y-py)*(y-py)) / float (radius + 1);
        if (d < dist)
          dist = d;
      }
    }
  }

  return dist;
}

void calcEuclideanDistanceMap (Image& destImage, Image const& maskImage, int radius)
{
  Pixels dest (destImage, destImage.getBounds ());
  Pixels mask (maskImage, maskImage.getBounds ());

  for (int y = 0; y < dest.height; ++y)
  {
    for (int x = 0; x < dest.width; ++x)
    {
      uint8 dist = static_cast <uint8> (
        255 * (1 - calcEuclideanDistance (mask, x, y, radius)) + 0.5);

      *dest.getPixelPointer (x, y) = dist;
    }
  }
}

void LayerContext::applyEuclideanDistanceMap (Image& workImage)
{
#if 0
  Image mask = ChannelImageType::fromImage (getImage (), 3);
  Image map (Image::SingleChannel, workImage.getWidth (), workImage.getHeight (), true);

  InvertImage (mask);

  calcEuclideanDistanceMap (map, mask, 16);

  InvertImage (map);

  for (int i = 0; i < 3; ++i)
  {
    Image dest = ChannelImageType::fromImage (workImage, i);

    Pixels p (dest, dest.getBounds ());
    p.iterate (Pixels (map, map.getBounds ()), CopyGray ());
  }
#else
  Image mask = ChannelImageType::fromImage (getImage (), 3);
  Image map (Image::SingleChannel, workImage.getWidth (), workImage.getHeight (), true);

  calcEuclideanDistanceMap (map, mask, 8);

  for (int i = 0; i < 3; ++i)
  {
    Image dest = ChannelImageType::fromImage (workImage, i);

    Pixels p (dest, dest.getBounds ());
    p.iterate (Pixels (map, map.getBounds ()), CopyGray ());
  }
#endif
}

//------------------------------------------------------------------------------
