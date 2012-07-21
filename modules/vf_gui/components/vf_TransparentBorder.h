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
