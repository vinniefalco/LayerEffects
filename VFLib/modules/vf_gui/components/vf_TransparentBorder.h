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

#ifndef __VF_TRANSPARENTBORDER_VFHEADER__
#define __VF_TRANSPARENTBORDER_VFHEADER__

/*============================================================================*/
/**
    Transparent border for an opaque Component.

    This lets you make the sides of a component draw with transparency,
    while allowing the rest to take advantage of the opaque Component
    optimization (see Component::setOpaque).

    To use this, add TransparentBorder as a member of your Component
    derived class. Then call setComponent with the size of the desired
    transparent border.

    @ingroup vf_gui
*/
class TransparentBorder
  : private ComponentListener
  , LeakChecked <TransparentBorder>
{
public:
  TransparentBorder ();
  ~TransparentBorder ();

  enum
  {
    maxBorderSize = 0x1fffffff
  };

  static const BorderSize <int> fullyOpaque;      //!< No transparency
  static const BorderSize <int> fullyTransparent; //!< Full transparency

  /** Set up a Component to have a transparent border.

      The Component should have setOpaque (false).

      @param component The Component to have a transparent border.

      @param borderSize The number of transparent pixels on each side.
  */
  void setComponent (Component *component,
                     BorderSize <int> borderSize = BorderSize<int>());

  void setAlpha (float alpha);

private:
  bool isAttached ();
  void updateBounds ();
  void updateZOrder ();
  void componentMovedOrResized (Component& component,
                                bool wasMoved,
                                bool wasResized);
  void componentVisibilityChanged (Component& component);
  void componentChildrenChanged (Component& component);
  void componentParentHierarchyChanged (Component& component);
  void componentBeingDeleted (Component& component);

private:
  class OpaqueComponent : public Component
  {
  public:
    OpaqueComponent ();
    ~OpaqueComponent ();
    void paint (Graphics& g);
  };

  Component* m_component;
  Component* m_parent;
  ScopedPointer <OpaqueComponent> m_opaque;
  BorderSize <int> m_borderSize;
  bool m_visible;
};

#endif
