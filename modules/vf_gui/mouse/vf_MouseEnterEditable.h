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

#ifndef __VF_MOUSEENTEREDITABLE_VFHEADER__
#define __VF_MOUSEENTEREDITABLE_VFHEADER__

/*============================================================================*/
/**
    A mode activated on mouse enter.

    A MouseEnterEditable allows your Component to go into an 'edit mode' when
    the mouse enters. For example, zoom in/out buttons can appear when the mouse
    enters, and disappear when the mouse leaves.

    @ingroup vf_gui
*/
class MouseEnterEditable : Uncopyable
{
private:
  class Helper;

public:
  // A parent component must derive from this. Usually its the top level window.
  //
  class Container
    : private Timer
  {
  public:
    enum
    {
      lingerMilliseconds = 500
    };

    Container ();
    ~Container ();

    MouseEnterEditable* getCurrentEditable ();
    void exitCurrentEditMode ();

  private:
    void mouseEnterEditableActivity (MouseEnterEditable* editable,
                                     bool isMouseEnter);
    void timerCallback();

  private:
    friend class Helper;

    MouseEnterEditable* m_currentEdit;
    MouseEnterEditable* m_nextEdit;
  };

public:
  explicit MouseEnterEditable (Component* component);
  ~MouseEnterEditable ();

  bool isInMouseEnterEditMode ();
  void exitMouseEnterEditMode ();

protected:
  virtual void onMouseEnterEditMode (bool shouldBeInEditMode) = 0;

private:
  class Helper
    : private MouseListener
    , Uncopyable
  {
  public:
    Helper (Component* component, MouseEnterEditable* editable);
    ~Helper ();

    Component& getComponent ();

  private:
    void mouseEnter (const MouseEvent& e);
    void mouseExit (const MouseEvent& e);

  private:
    Component* const m_component;
    MouseEnterEditable* const m_editable;
  };

private:
  Helper m_helper;
};

#endif
