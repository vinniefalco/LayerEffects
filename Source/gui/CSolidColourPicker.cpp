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

CSolidColourPicker::CSolidColourPicker ()
  : m_colour (Colours::black)
{
}
  
CSolidColourPicker::~CSolidColourPicker ()
{
}

void CSolidColourPicker::addListener (Listener* listener)
{
  m_listeners.add (listener);
}

void CSolidColourPicker::removeListener (Listener* listener)
{
  m_listeners.remove (listener);
}

void CSolidColourPicker::setValue (Colour const& colour, bool sendChangeNotification)
{
  if (m_colour != colour)
  {
    if (sendChangeNotification)
    {
      m_listeners.call (&Listener::onSolidColourChanged, this);
    }
  }
}

Colour CSolidColourPicker::getValue () const
{
  return m_colour;
}

void CSolidColourPicker::paint (Graphics& g)
{
  Rectangle <int> b (getLocalBounds ());

  g.setColour (Colours::black);
  g.drawRect (b);

  g.setColour (Colours::white);
  g.drawRect (b.reduced (1));

  g.setColour (m_colour);
  g.fillRect (b.reduced (2));
}

class ColourSelectorWindow
  : public DocumentWindow
{
public:
  ColourSelectorWindow ()
    : DocumentWindow ("Select Colour", Colours::grey, DocumentWindow::closeButton, true)
  {
    ColourSelector* c = new ColourSelector (
      ColourSelector::showColourAtTop | ColourSelector::showSliders | ColourSelector::showColourspace);

    c->setSize (400, 300);

    setContentOwned (c, true);

    centreWithSize (getWidth(), getHeight());
    setVisible (true);
  }

  void closeButtonPressed ()
  {
    exitModalState (0);
  }
};

void CSolidColourPicker::mouseDown (const MouseEvent& e)
{
  ColourSelectorWindow* w = new ColourSelectorWindow;

  w->enterModalState (true, nullptr, true);
}


