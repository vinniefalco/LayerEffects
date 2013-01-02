//------------------------------------------------------------------------------
/*
  LayerEffects for JUCE

  Official project location:
  https://github.com/vinniefalco/LayerEffects

  ------------------------------------------------------------------------------

  License: MIT License (http://www.opensource.org/licenses/mit-license.php)
  Copyright (c) 2012 by Vinnie Falco

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
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
//------------------------------------------------------------------------------

CLayerGraphicsPreview::CLayerGraphicsPreview ()
  : m_offset (0, 0)
{
  m_thread.addListener (this, vf::MessageThread::getInstance ());
}

CLayerGraphicsPreview::~CLayerGraphicsPreview ()
{
  m_thread.removeListener (this);
}

void CLayerGraphicsPreview::setOptions (Options* newOptions)
{
  m_settings.options.general          = newOptions->general;
  m_settings.options.fill             = newOptions->fill;
  m_settings.options.dropShadow       = newOptions->dropShadow;
  m_settings.options.innerShadow      = newOptions->innerShadow;
  m_settings.options.outerGlow        = newOptions->outerGlow;
  m_settings.options.innerGlow        = newOptions->innerGlow;
  m_settings.options.bevelEmboss      = newOptions->bevelEmboss;
  m_settings.options.colourOverlay    = newOptions->colourOverlay;
  m_settings.options.gradientOverlay  = newOptions->gradientOverlay;
  m_settings.options.patternOverlay   = newOptions->patternOverlay;
  m_settings.options.stroke           = newOptions->stroke;

  recalculateSettings ();

  repaint ();
}

void CLayerGraphicsPreview::resized ()
{
  recalculateSettings ();
}

void CLayerGraphicsPreview::paint (Graphics& g)
{
  g.fillAll (Colours::red);
  g.drawImageAt (m_displayImage, 0, 0);
}

//------------------------------------------------------------------------------

void CLayerGraphicsPreview::mouseDown (MouseEvent const& e)
{
  m_startOffset = m_offset;
}

void CLayerGraphicsPreview::mouseDrag (MouseEvent const& e)
{
  m_offset.x = m_startOffset.x + e.getDistanceFromDragStartX ();
  m_offset.y = m_startOffset.y + e.getDistanceFromDragStartY ();

  vf::componentBroadcast (getTopLevelComponent (), &Listener::onPreviewOffset, m_offset);
}

void CLayerGraphicsPreview::mouseUp (MouseEvent const& e)
{
}

//------------------------------------------------------------------------------

bool CLayerGraphicsPreview::isInterestedInFileDrag (const StringArray& files)
{
  bool isInterested = false;

  if (files.size () == 1)
  {
    isInterested = true;
  }

  return isInterested;
}

void CLayerGraphicsPreview::fileDragEnter (const StringArray& files, int x, int y)
{
//  setFocused (true);
}

void CLayerGraphicsPreview::fileDragExit (const StringArray& files)
{
//  setFocused (false);
}

void CLayerGraphicsPreview::filesDropped (const StringArray& files, int x, int y)
{
  if (files.size () == 1)
  {
    Image image = ImageFileFormat::loadFrom (File (files [0]));

    if (image.isValid ())
    {
      m_foregroundImage = image;
      recalculateSettings ();
    }
  }

//  setFocused (false);
}

//------------------------------------------------------------------------------

void CLayerGraphicsPreview::recalculateSettings ()
{
  {
    Image bk (Image::RGB, getWidth (), getHeight (), false);
    Graphics g (bk);
    paintBackground (g);
    m_settings.backgroundImage = bk;
  }

  {
    Image fg (Image::ARGB, getWidth (), getHeight (), true);
    Graphics g (fg);
    paintForeground (g);
    m_settings.foregroundImage = fg;
  }

  m_thread.changeSettings (m_settings);
}

void CLayerGraphicsPreview::paintBackground (Graphics& g)
{
#if 1
  g.setGradientFill (ColourGradient (
    Colours::black, 0.f, 0.f,
    Colours::white, 0.f, float (getLocalBounds ().getHeight ()),
    false));
  g.fillRect (getLocalBounds ());
#else
  //g.fillAll (Colours::black);
  g.fillAll (Colours::white);
#endif
}

void CLayerGraphicsPreview::paintForeground (Graphics& g)
{
  Rectangle <int> const b (getLocalBounds ());

  if (m_foregroundImage.isValid ())
  {
    g.drawImageAt (m_foregroundImage, 0, 0);
  }
  else
  {
#if 1
    // test
    g.setGradientFill (ColourGradient (
      Colours::red, float (b.getX ()), float (b.getY ()),
      Colours::yellow, float (b.getRight ()), float (b.getBottom ()),
      false));

    g.setFont (Font ("Impact", b.getHeight () / 3.f, Font::plain));
    g.drawFittedText ("Layer\nEffects", b, Justification::centred, 2);

#elif 1
    // dot
    g.setColour (Colours::black);
    g.fillRect (
      getLocalBounds ().getCentreX (),
      getLocalBounds ().getCentreY (),
      1, 1);

#elif 0
    // square
    g.setColour (Colours::grey);
    int const x = getLocalBounds ().getWidth () / 4;
    int const y = getLocalBounds ().getHeight () / 4;
    g.fillRect (getLocalBounds ().getX () + x, getLocalBounds ().getY () + y, 2*x, 2*y);

#elif 1
    // ellipse
    g.setColour (Colours::grey);
    int const x = getLocalBounds ().getWidth () / 4;
    int const y = getLocalBounds ().getHeight () / 4;
    g.fillEllipse (getLocalBounds ().getX () + x, getLocalBounds ().getY () + y, 2*x, 2*y);

#endif
  }
}

void CLayerGraphicsPreview::onImageReady (Image image)
{
  m_displayImage = image;

  repaint ();
}
