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

CColourPickerDialog::CColourPickerDialog () : DocumentWindow (
  "Select Colour",
  Colours::grey,
  DocumentWindow::closeButton,
  true)
{
  m_colourSelector = new ColourSelector (
    ColourSelector::showColourAtTop | ColourSelector::showSliders | ColourSelector::showColourspace);

  m_colourSelector->setSize (400, 300);
  m_colourSelector->addChangeListener (this);

  setContentOwned (m_colourSelector, true);

  centreWithSize (getWidth(), getHeight());
  setVisible (true);
}

void CColourPickerDialog::addListener (Listener* listener)
{
  m_listeners.add (listener);
}

void CColourPickerDialog::removeListener (Listener* listener)
{
  m_listeners.remove (listener);
}

void CColourPickerDialog::closeButtonPressed ()
{
  exitModalState (0);
}

void CColourPickerDialog::changeListenerCallback (ChangeBroadcaster* source)
{
  if (source == m_colourSelector)
  {
    m_listeners.call (&Listener::onColourPickerDialogChanged, this, m_colourSelector->getCurrentColour ());
  }
}

