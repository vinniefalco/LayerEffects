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

#ifndef LAYEREFFECTS_CIMAGEDROPTARGET_HEADER
#define LAYEREFFECTS_CIMAGEDROPTARGET_HEADER

/** Accepts a drag and dropped image.
*/
class CImageDropTarget
  : public Component
  , public FileDragAndDropTarget
{
public:
  struct Listener
  {
    virtual void onImageDropTargetDrop (int id, Image image) = 0;
  };

  explicit CImageDropTarget (int id);
  ~CImageDropTarget ();

  void paint (Graphics& g);

  bool isInterestedInFileDrag (const StringArray& files);
  void fileDragEnter (const StringArray& files, int x, int y);
  void fileDragExit (const StringArray& files);
  void filesDropped (const StringArray& files, int x, int y);

protected:
  void setFocused (bool isFocused);

private:
  int const m_id;
  bool m_isFocused;
  Image m_image;
};

#endif

