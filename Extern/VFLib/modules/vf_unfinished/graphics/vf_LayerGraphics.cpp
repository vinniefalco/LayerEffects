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

  m_work = Image (Image::RGB,
                  workBounds.getWidth (),
                  workBounds.getHeight(),
                  false,
                  SoftwareImageType ());

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
  Pixels fillPixels (fillImage);
  Pixels maskPixels (maskImage);
  Pixels workPixels (m_work);

  m_options.dropShadow (workPixels, maskPixels);
  m_options.outerGlow (workPixels, maskPixels);
  m_options.stroke (workPixels, maskPixels);
  m_options.bevelEmboss (workPixels, maskPixels);

  if (m_options.general.groupInteriorEffects)
  {
    m_options.patternOverlay (fillPixels);
    m_options.gradientOverlay (fillPixels);
    m_options.colourOverlay (fillPixels);
    // satin
    m_options.innerGlow (fillPixels, maskPixels);
    m_options.innerShadow (fillPixels, maskPixels);
    m_options.fill (m_work, m_fill);
  }
  else
  {
    m_options.patternOverlay (workPixels);
    m_options.gradientOverlay (workPixels);
    m_options.colourOverlay (workPixels);
    // satin
    m_options.innerGlow (workPixels, maskPixels);
    m_options.innerShadow (workPixels, maskPixels);
    m_options.fill (m_work, m_fill);
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
