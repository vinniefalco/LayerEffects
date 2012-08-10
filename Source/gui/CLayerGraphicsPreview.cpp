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
{
}

CLayerGraphicsPreview::~CLayerGraphicsPreview ()
{
}

void CLayerGraphicsPreview::setOptions (Options* newOptions, bool updateNow)
{
  m_newOptions = *newOptions;

  if (updateNow)
  {
    m_options = m_newOptions;
    repaint ();
  }
  else
  {
    startTimer (250);
  }
}

void CLayerGraphicsPreview::paint (Graphics& g)
{
  paintBackground (g);

  vf::LayerGraphics lc (g, getLocalBounds ());

  lc.getOptions ().general = m_options.general;
  lc.getOptions ().fill = m_options.fill;
  lc.getOptions ().dropShadow = m_options.dropShadow;
  lc.getOptions ().bevelEmboss = m_options.bevelEmboss;
  lc.getOptions ().gradientOverlay = m_options.gradientOverlay;

  paintForeground (lc);
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
  g.fillAll (Colours::white);
#endif
}

void CLayerGraphicsPreview::paintForeground (Graphics& g)
{
  Rectangle <int> const b (getLocalBounds ());

#if 1
  // test
  g.setGradientFill (ColourGradient (
    Colours::red, float (b.getX ()), float (b.getY ()),
    Colours::yellow, float (b.getRight ()), float (b.getBottom ()),
    false));

  g.setFont (Font ("Impact", b.getHeight () / 3.f, Font::plain));
  g.drawFittedText ("Layer\nEffects", b, Justification::centred, 2);

#elif 0
  // dot
  g.setColour (Colours::black);
  g.fillRect (
    getLocalBounds ().getCentreX (),
    getLocalBounds ().getCentreY (),
    1, 1);

#else
  // square
  g.setColour (Colours::grey);
  int const x = getLocalBounds ().getWidth () / 4;
  int const y = getLocalBounds ().getHeight () / 4;
  g.fillRect (getLocalBounds ().getX () + x, getLocalBounds ().getY () + y, 2*x, 2*y);
#endif
}

void CLayerGraphicsPreview::timerCallback ()
{
  stopTimer ();

  m_options = m_newOptions;

  repaint ();
}

