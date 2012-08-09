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

//------------------------------------------------------------------------------

LayerGraphicsBase::LayerGraphicsBase (
  Graphics& g, Rectangle <int> const& fillBounds)
{
  /* fillBounds cannot be empty. */
  jassert (!fillBounds.isEmpty ());

  LowLevelGraphicsSoftwareRenderer* renderer =
    dynamic_cast <LowLevelGraphicsSoftwareRenderer*> (
      &g.getInternalContext ());
  
  /* If this goes off it means you aren't using the software renderer for your
     Image!. LayerGraphics only works with the software renderer!
  */
  jassert (renderer != nullptr);

  RenderingHelpers::TranslationOrTransform const& transform = renderer->getTransform ();

  /* If this goes off it means you have something other than a simple
     translation in the transform. LayerGraphics does not support transforms other
     than translations!
  */
  jassert (transform.isOnlyTranslated);

  m_base = renderer->getImage ();

  Rectangle <int> const clipBounds (g.getClipBounds ().
    translated (transform.xOffset, transform.yOffset));
  
  jassert (m_base.getBounds ().contains (clipBounds));

  m_fill = Image (Image::ARGB, fillBounds.getWidth (), fillBounds.getHeight (), true);

  m_fillOrigin = fillBounds.getTopLeft ().translated (transform.xOffset, transform.yOffset);

  Rectangle <int> const workBounds =
    clipBounds.getIntersection (fillBounds.translated (transform.xOffset, transform.yOffset));

  jassert (m_base.getBounds ().contains (workBounds));

  m_work = Image (Image::RGB, workBounds.getWidth (), workBounds.getHeight(), false);

  m_workOrigin = workBounds.getTopLeft ();

  // Calculate the portion of m_fill which corresponds to m_work
  m_fillBounds = workBounds -
    fillBounds.getTopLeft ().translated (transform.xOffset, transform.yOffset);

  jassert (m_fill.getBounds ().contains (m_fillBounds));

  // Copy the base image into the work image.
  copyImage (
    m_work,
    Point <int> (0, 0),
    m_base,
    Rectangle <int> (
      m_workOrigin.getX (), m_workOrigin.getY (),
      m_work.getWidth (), m_work.getHeight ()),
    BlendMode::modeNormal,
    1);
}

//------------------------------------------------------------------------------

LayerGraphics::LayerGraphics (Graphics& g, Rectangle <int> const& fillBounds)
  : LayerGraphicsBase (g, fillBounds)
  , Graphics (m_fill)
{ 
  setOrigin (-fillBounds.getX (), -fillBounds.getY ());
}

//------------------------------------------------------------------------------

LayerGraphics::~LayerGraphics ()
{
  // Convert from premultiplied to normal.
  //
  unPremultiplyImage (m_fill);

  // Extract the layer's RGB components as Image::RGB
  //
  Image fillImage (ChannelImageType::fromImage (m_fill, -1));

  // Extract the layer's alpha mask as a single channel image.
  //
  Image maskImage (ChannelImageType::fromImage (m_fill, PixelARGB::indexA));

  // Obtain bitmap data for mask and fill.
  //
  Pixels fillPixels (m_fill);
  Pixels maskPixels (maskImage);
  Pixels workPixels (m_work);

  //
  // Apply overlays to fill image, bottom up.
  //

  if (m_options.gradientOverlay.active)
  {
    GradientOverlayStyle::render (fillPixels, m_options.gradientOverlay);
  }

  //applyInnerShadow (m_work);

  //
  // Apply effects to work image, bottom up.
  //

  applyDropShadow (m_work);

  applyFill ();

  if (m_options.bevelEmboss.active)
  {
    BevelEmbossStyle::render (workPixels, maskPixels, m_options.bevelEmboss);
  }

  // Copy the work image onto the background layer
  // using normal mode and the general opacity.
  copyImage (
    m_base,
    m_workOrigin,
    m_work,
    m_work.getBounds (),
    BlendMode::modeNormal,
    m_options.general.opacity);
}

//------------------------------------------------------------------------------

LayerGraphics::Options& LayerGraphics::getOptions ()
{
  return m_options;
}

//------------------------------------------------------------------------------

void LayerGraphics::applyDropShadow (Image& workImage)
{
  Options::DropShadow& dropShadow = m_options.dropShadow;

  if (!dropShadow.active)
    return;

#if 0
  int const dx = static_cast <int> (
    - dropShadow.distance * std::cos (dropShadow.angle) + 0.5) - dropShadow.size;
  
  int const dy = static_cast <int> (
    dropShadow.distance * std::sin (dropShadow.angle) + 0.5) - dropShadow.size;
#endif

  // Get the layer mask as an individual channel.
  Image mask = ChannelImageType::fromImage (m_fill, PixelARGB::indexA);
  
  RadialImageConvolutionKernel k (dropShadow.size + 1);
  k.createGaussianBlur ();

  // Compute the shadow mask.
  Image shadow = k.createConvolvedImageFull (mask);

  // Optionally subtract layer mask from shadow mask.
  if (dropShadow.knockout)
    copyImage (
      shadow,
      //Point <int> (dropShadow.size + dx, dropShadow.size + dy),
      Point <int> (0, 0),
      mask,
      mask.getBounds (),
      BlendMode::modeSubtract,
      1);

  // Fill the shadow mask.
  fillImage (workImage,
             Point <int> (0, 0),
             shadow,
             shadow.getBounds (),
             dropShadow.mode,
             dropShadow.opacity,
             dropShadow.colour);
}

//------------------------------------------------------------------------------

#if 0
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
#endif

void LayerGraphics::applyInnerShadow (Image& workImage)
{
  Options::InnerShadow& innerShadow = m_options.innerShadow;

  if (!innerShadow.active)
    return;

#if 0
  int const dx = static_cast <int> (
    - innerShadow.distance * std::cos (innerShadow.angle) + 0.5) - innerShadow.size;
  
  int const dy = static_cast <int> (
    innerShadow.distance * std::sin (innerShadow.angle) + 0.5) - innerShadow.size;
#endif

  Image mask = ChannelImageType::fromImage (m_fill, PixelARGB::indexA);
  
  RadialImageConvolutionKernel k (innerShadow.size + 1);
  k.createGaussianBlur ();

  Image shadow = k.createConvolvedImage (mask);

  // Apply inner shadow using layer mask.
  fillImage (workImage,
             Point <int> (0, 0),
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
             BlendMode::modeDarken,
             1);
  // DO THIS CLIP FIRST so we have fewer pixels to process?
  //shadow = shadow.getClippedImage (mask.m_bounds + Point <int> (dx, dy));

  // Fill the shadow mask.
  fillImage (workImage,
             Point <int> (0, 0),
             shadow,
             shadow.getBounds (),
             innerShadow.mode,
             innerShadow.opacity,
             innerShadow.colour);
}

//------------------------------------------------------------------------------

void LayerGraphics::applyFill ()
{
  copyImage (
    m_work,
    Point <int> (0, 0),
    m_fill,
    m_fillBounds,
    m_options.fill.mode,
    m_options.fill.opacity);
}
