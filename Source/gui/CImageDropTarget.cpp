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

CImageDropTarget::CImageDropTarget (int id)
  : m_id (id)
  , m_isFocused (false)
{
  setOpaque (false);
}

CImageDropTarget::~CImageDropTarget ()
{
}

void CImageDropTarget::paint (Graphics& g)
{
  if (m_image.isValid ())
  {
    g.drawImageWithin (m_image, 0, 0, getWidth (), getHeight (), RectanglePlacement::stretchToFit);
  }
  else
  {
    g.setColour (Colours::black);
    g.drawText ("Drop Image", getLocalBounds (), Justification::centred, true);
  }

  if (m_isFocused)
  {
    g.setColour (findColour (TextEditor::highlightColourId));
    g.drawRect (getLocalBounds (), 4);
  }
}

bool CImageDropTarget::isInterestedInFileDrag (const StringArray& files)
{
  bool isInterested = false;

  if (files.size () == 1)
  {
    isInterested = true;
  }

  return isInterested;
}

void CImageDropTarget::fileDragEnter (const StringArray& files, int x, int y)
{
  setFocused (true);
}

void CImageDropTarget::fileDragExit (const StringArray& files)
{
  setFocused (false);
}

void CImageDropTarget::filesDropped (const StringArray& files, int x, int y)
{
  if (files.size () == 1)
  {
    Image image = ImageFileFormat::loadFrom (File (files [0]));

    if (image.isValid ())
    {
      m_image = image;
      repaint ();

      vf::componentNotifyParent (this, &Listener::onImageDropTargetDrop, m_id, image);
    }
  }

  setFocused (false);
}

void CImageDropTarget::setFocused (bool isFocused)
{
  if (m_isFocused != isFocused)
  {
    m_isFocused = isFocused;
    repaint ();
  }
}
