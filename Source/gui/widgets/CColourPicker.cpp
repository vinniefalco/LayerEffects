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

CColourPicker::CColourPicker ()
  : m_colour (Colours::black)
{
}
  
CColourPicker::~CColourPicker ()
{
}

void CColourPicker::addListener (Listener* listener)
{
  m_listeners.add (listener);
}

void CColourPicker::removeListener (Listener* listener)
{
  m_listeners.remove (listener);
}

void CColourPicker::setValue (Colour const& colour, bool sendChangeNotification)
{
  if (m_colour != colour)
  {
    m_colour = colour;
    repaint ();

    if (sendChangeNotification)
    {
      m_listeners.call (&Listener::onColourPickerChanged, this, colour);
    }
  }
}

Colour CColourPicker::getValue () const
{
  return m_colour;
}

void CColourPicker::paint (Graphics& g)
{
  Rectangle <int> b (getLocalBounds ());

  g.setColour (Colours::black);
  g.drawRect (b);

  g.setColour (Colours::white);
  g.drawRect (b.reduced (1));

  g.setColour (m_colour);
  g.fillRect (b.reduced (2));
}

void CColourPicker::mouseDown (const MouseEvent& e)
{
  CColourPickerDialog* w = new CColourPickerDialog;

  w->addListener (this);

  w->enterModalState (true, nullptr, true);
}

void CColourPicker::onColourPickerDialogChanged (CColourPickerDialog* dialog, Colour colour)
{
  setValue (colour, true);
}