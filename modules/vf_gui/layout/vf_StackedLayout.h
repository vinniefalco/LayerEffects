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

#ifndef VF_STACKEDLAYOUT_VFHEADER
#define VF_STACKEDLAYOUT_VFHEADER

#include "vf_ResizableLayout.h"

class StackedLayout
  : public Component
  , public ResizableChild
  , private ComponentListener
  , private AsyncUpdater
{
public:
  class Band
  {
  public:
    Band ();

  private:
    friend class StackedLayout;

    bool m_resizable;
    Component* m_component;
  };

public:
  StackedLayout (bool vertical,
                 BorderSize <int> borderSize,
                 int gapSize);
  ~StackedLayout ();

  void addBand (Component* component);

  void setBandVisible (int index, bool visible);

  void recalculateLayout ();

  void activateStackedLayout ();

  void resized ();

private:
  void resizeStart ();

  void componentMovedOrResized (Component& component,
                                bool wasMoved,
                                bool wasResized);

  void componentVisibilityChanged (Component& component);

  void componentBeingDeleted (Component& component);

  void handleAsyncUpdate ();

private:
  struct Item
  {
    Component* component;
    ResizableChild* resizableChild;
  };

  bool const m_vertical;
  bool m_active;
  const BorderSize<int> m_borderSize;
  const int m_gapSize;
  std::vector <Item> m_bands; // yuck
};

#endif
