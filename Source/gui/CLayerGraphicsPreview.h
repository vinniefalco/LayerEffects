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

#ifndef LAYEREFFECTS_CLAYERGRAPHICSPREVIEW_HEADER
#define LAYEREFFECTS_CLAYERGRAPHICSPREVIEW_HEADER

/** Displays a preview of the layer graphics effects.
*/
class CLayerGraphicsPreview
  : public Component
  , public FileDragAndDropTarget
  , public BackgroundThread::Listener
{
public:
  struct Listener
  {
    virtual void onPreviewOffset (Point <int> offset) { }
  };

  CLayerGraphicsPreview ();
  ~CLayerGraphicsPreview ();

  void setOptions (Options* newOptions);

  void resized ();

  void paint (Graphics& g);

  void mouseDown (MouseEvent const& e);
  void mouseDrag (MouseEvent const& e);
  void mouseUp (MouseEvent const& e);

private:
  bool isInterestedInFileDrag (const StringArray& files);
  void fileDragEnter (const StringArray& files, int x, int y);
  void fileDragExit (const StringArray& files);
  void filesDropped (const StringArray& files, int x, int y);

private:
  void recalculateSettings ();

  void paintBackground (Graphics& g);
  void paintForeground (Graphics& g);

  void onImageReady (Image image);

private:
  BackgroundThread m_thread;
  BackgroundThread::Settings m_settings;
  Image m_foregroundImage;
  Image m_displayImage;

  Point <int> m_offset;
  bool m_isDragging;
  Point <int> m_startOffset;
  Point <int> m_dragStart;
};

#endif
