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

struct CopyGrayToRGB
{
  void operator () (uint8* dest, uint8 const* src) const
  {
    PixelRGB* d ((PixelRGB*)dest);
    d->getRed () = *src;
    d->getGreen () = *src;
    d->getBlue () = *src;
  }
};

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
  // Extract the layer's RGB components as Image::RGB
  Image fillImage (ChannelImageType::fromImage (m_fill, -1));

  // Extract the layer's alpha mask as a single channel image.
  Image maskImage (ChannelImageType::fromImage (m_fill, PixelARGB::indexA));

  // Obtain bitmap data for mask and fill
  Pixels fillPixels (m_fill);

  unPremultiplyImage (m_fill);

  //
  // Apply overlays to the fill image.
  //

  if (m_options.gradientOverlay.active)
  {
    GradientOverlayStyle::render (fillPixels, m_options.gradientOverlay);
  }

  // Draw effects from the bottom up.

#if 1
  applyDropShadow (m_work);

  applyFill ();

  //applyInnerShadow (m_work);

  //applyEuclideanDistanceMap (m_work);
#endif

#if 0
  Image distanceMap = calcDistanceMap (ChannelImageType::fromImage (m_fill, PixelARGB::indexA), 6);
  RadialImageConvolutionKernel k (4);
  k.createGaussianBlur ();
  distanceMap = k.createConvolvedImage (distanceMap);
  Image embossMap = calcEmbossMap (distanceMap);
  fillImage (m_work,
             Point <int> (0, 0),
             embossMap,
             embossMap.getBounds (),
             normal,
             1,
             Colours::yellow);
#endif

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

//------------------------------------------------------------------------------

/*
float calcEuclideanDistance (Pixels const& mask, int x, int y, int radius)
{
  float dist = std::numeric_limits <float>::infinity ();

  int const x0 = jmax (x - radius, 0);
  int const x1 = jmin (x + radius, mask.width);
  int const y0 = jmax (y - radius, 0);
  int const y1 = jmin (y + radius, mask.height);

  for (int py = y0; py < y1; ++py)
  {
    float const dy = float (y-py);
    float const dys = dy * dy;

    for (int px = x0; px < x1; ++px)
    {
      uint8 const m = *mask.getPixelPointer (px, py);

      if (m != 0)
      {
        float const dx = float (x-px);
        float d = dx * dx + dys;
        if (d < dist)
          dist = d;
      }
    }
  }

  dist = sqrt (dist) / float (radius + 1);

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

void LayerGraphics::applyEuclideanDistanceMap (Image& workImage)
{
  Image mask = ChannelImageType::fromImage (m_fill, PixelARGB::indexA);
  Image map (Image::SingleChannel, workImage.getWidth (), workImage.getHeight (), true);

  calcEuclideanDistanceMap (map, mask, 10);

  Pixels p (workImage);
  p.iterate (Pixels (mask), CopyGrayToRGB());
}
*/

//------------------------------------------------------------------------------

float calcDistancePixel (Pixels mask, int x, int y, int radius)
{
  float dist = float ((radius + 1) * (radius + 1));

  int const x0 = jmax (x - radius, 0);
  int const x1 = jmin (x + radius, mask.getCols ());
  int const y0 = jmax (y - radius, 0);
  int const y1 = jmin (y + radius, mask.getRows ());

  if (*mask.getPixelPointer (x, y) > 127)
  {
    for (int py = y0; py < y1; ++py)
    {
      float const dy = float (y-py);
      float const dys = dy * dy;

      for (int px = x0; px < x1; ++px)
      {
        uint8 const m = *mask.getPixelPointer (px, py);

        if (m < 127)
        {
          float const dx = float (x-px);
          float d = dx * dx + dys;
          if (d < dist)
            dist = d;
        }
      }
    }

    dist = sqrt (dist) / float (radius + 1);

    if (dist > 1)
      dist = 1;
  }
  else
  {
    dist = 1;
  }

  return dist;
}

Image LayerGraphics::calcDistanceMap (Image maskImage, int radius)
{
  Image destImage (
    Image::SingleChannel,
    maskImage.getWidth (),
    maskImage.getHeight (),
    true);

  Pixels dest (destImage, destImage.getBounds ());
  Pixels mask (maskImage, maskImage.getBounds ());

  for (int y = 0; y < dest.getRows (); ++y)
  {
    for (int x = 0; x < dest.getCols (); ++x)
    {
      float df = calcDistancePixel (mask, x, y, radius);
      uint8 dist = static_cast <uint8> (255 * (1 - df) + 0.5);

      *dest.getPixelPointer (x, y) = dist;
    }
  }

  return destImage;
}

//------------------------------------------------------------------------------

template <class T>
struct Vec3
{
  Vec3 ()
  {
  }

  Vec3 (T x_, T y_, T z_) : x (x_), y (y_), z (z_)
  {
  }

  T getNormal () const
  {
    return sqrt (x*x + y*y + z*z);
  }

  void normalize ()
  {
    T n = getNormal ();

    if (n != 0)
    {
      n = 1 / n;
      x *= n;
      y *= n;
      z *= n;
    }
  }

  template <class U>
  Vec3& operator+ (Vec3 <U> const& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  template <class U>
  Vec3& operator- (Vec3 <U> const& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template <class U>
  T getDotProduct (Vec3 <U> const& t) const
  {
    return x * t.x + y * t.y + z * t.z;
  }

  template <class U>
  Vec3 <T> getCrossProduct (Vec3 <U> const& t) const
  {
    return Vec3 <T> (
       y * t.z - z * t.y,
      -x * t.z + z * t.x,
       x * t.y - y * t.x);
  }

  template <class U>
  T getCosAngle (Vec3 <U> const& t) const
  {
    return getDotProduct (t) / (getNormal () * t.getNormal ());
  }

  float x;
  float y;
  float z;
};

Image LayerGraphics::calcEmbossMap (Image sourceImage)
{
  float lightElevation = 45;
  float lightAngle = 135;

  lightElevation = 3.14159265358979f * lightElevation / 180;
  lightAngle = 3.14159265358979f * lightAngle / 180;

  Vec3 <float> lightNormal (
    cos (lightElevation) * cos (lightAngle),
    -cos (lightElevation) * sin (lightAngle),
    sin (lightElevation));

  Image destImage (
    Image::SingleChannel,
    sourceImage.getWidth (),
    sourceImage.getHeight (),
    true);

  Pixels src (sourceImage);
  Pixels dest (destImage);

  for (int y = 1; y < dest.getRows ()-1; ++y)
  {
    for (int x = 1; x < dest.getCols ()-1; ++x)
    {
      uint8* ps = src.getPixelPointer (x, y);

      Vec3 <float> n (
        float (ps [-src.getColBytes ()] - ps [src.getColBytes ()]),
        float (ps [-src.getRowBytes ()] - ps [src.getRowBytes ()]),
        float (1));

      float incidentLight = n.getDotProduct (lightNormal) / n.getNormal ();

      if (incidentLight > 0)
        *dest.getPixelPointer (x, y) = uint8 (255 * incidentLight);
      //else
      //  *dest.getPixelPointer (x, y) = uint8 (-255 * incidentLight);
    }
  }

  copyImage (destImage,
             Point <int> (0, 0),
             sourceImage,
             sourceImage.getBounds (),
             BlendMode::modeDarken,
             1);

  return destImage;
}

//------------------------------------------------------------------------------
