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

CTextDemo::CTextDemo ()
{
  setSize (512, 512);
}

CTextDemo::~CTextDemo ()
{
}

void CTextDemo::paint (Graphics& g)
{
  Rectangle <int> const b (getLocalBounds ());

  // Photoshop "Background" Layer
  vf::BackgroundContext bc (g, b);
  bc.fillAll (Colours::black);

  // Photoshop Layer + Mask, with Layer Effects
  vf::LayerContext lc (bc, b);

  lc.setGradientFill (ColourGradient (
    Colours::red, b.getX (), b.getY (),
    Colours::yellow, b.getRight (), b.getBottom (),
    false));
  lc.setFont (b.getHeight () / 3.f);
  lc.drawFittedText ("Layer\nEffects",
    b, Justification::centred, 2);

  vf::LayerContext::Options::Fill&
    fill (lc.getOptions ().fill);
  fill.mode = vf::screen;
  fill.opacity = .9;

  vf::LayerContext::Options::DropShadow&
    dropShadow (lc.getOptions ().dropShadow);
  dropShadow.active   = true;
  dropShadow.mode     = vf::softLight;
  dropShadow.colour   = Colours::cyan;
  dropShadow.angle    = 2*3.14159 * 45 / 360;
  dropShadow.distance = 4;
  dropShadow.spread   = 0.5;
  dropShadow.size     = 8;
  dropShadow.knockout = true;
}

void CTextDemo::mouseDown (MouseEvent const& e)
{
  repaint ();
}

