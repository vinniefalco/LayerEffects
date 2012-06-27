/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
