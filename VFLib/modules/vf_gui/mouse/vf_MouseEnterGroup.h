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

#ifndef VF_MOUSEENTERGROUP_VFHEADER
#define VF_MOUSEENTERGROUP_VFHEADER

/*============================================================================*/
/**
    Consolidated mouse enter and exits for a Component and its children.

    Derive your Component-derived class from this object in order to receive
    mouse enter and mouse exit messages that treat your component and all of
    it's children as a group.

    @ingroup vf_gui
*/
class MouseEnterGroup
{
public:
  explicit MouseEnterGroup (Component* parentComponent)
    : m_parentComponent (parentComponent)
    , m_helper (this)
    , m_mouseInside (false)
    , m_mouseInsideNext (false)
  {
  }

  ~MouseEnterGroup ()
  {
  }

  bool isMouseInsideGroup () const
  {
    return m_mouseInside;
  }

  // Called when the mouse enters or exits the group.
  // The event will be relative to the parent Component.
  //
  virtual void onMouseEnterGroup (MouseEvent const& e) { }
  virtual void onMouseExitGroup (MouseEvent const& e) { }

private:
  void updateState ()
  {
    if (m_mouseInside != m_mouseInsideNext)
    {
      if (m_mouseInsideNext)
      {
        m_mouseInside = true;
        onMouseEnterGroup (getMouseEvent ());
      }
      else
      {
        m_mouseInside = false;
        onMouseExitGroup (getMouseEvent ());
      }
    }
  }

private:
   // HACK because of Juce
  inline void setMouseEvent (MouseEvent const& mouseEvent)
    { memcpy (m_mouseEvent, &mouseEvent, sizeof (mouseEvent)); }
  inline MouseEvent const& getMouseEvent () const
    { return *reinterpret_cast <MouseEvent const*> (m_mouseEvent); }

  class Helper
    : private MouseListener
    , private AsyncUpdater
  {
  public:
    explicit Helper (MouseEnterGroup* const owner)
      : m_owner (*owner)
    {
      m_owner.m_parentComponent->addMouseListener (this, true);
    }

    ~Helper ()
    {
      m_owner.m_parentComponent->removeMouseListener (this);
    }

    void mouseEnter (MouseEvent const& e)
    {
      m_owner.m_mouseInsideNext = true;
      m_owner.setMouseEvent (e.getEventRelativeTo (m_owner.m_parentComponent));
      triggerAsyncUpdate ();
    }

    void mouseExit (MouseEvent const& e)
    {
      m_owner.m_mouseInsideNext = false;
      m_owner.setMouseEvent (e.getEventRelativeTo (m_owner.m_parentComponent));
      triggerAsyncUpdate ();
    }

    void handleAsyncUpdate ()
    {
      m_owner.updateState ();
    }

  private:
    MouseEnterGroup& m_owner;
  };

private:
  struct SavedMouseEvent
  {
    SavedMouseEvent (MouseEvent const& e)
    {
      source = &e.source;
      position = Point <int> (e.x, e.y);
      modifiers = e.mods;
      eventComponent = e.eventComponent;
      originator = e.originalComponent;
      eventTime = e.eventTime;
      mouseDownPos = e.getMouseDownPosition ();
      mouseDownTime = Time (0); // ???
      numberOfClicks = e.getNumberOfClicks();
      mouseWasDragged = !e.mouseWasClicked ();
    }

    MouseInputSource* source;
    Point <int>       position;
    ModifierKeys      modifiers;
    Component*        eventComponent;
    Component*        originator;
    Time              eventTime;
    Point <int>       mouseDownPos;
    Time              mouseDownTime;
    int               numberOfClicks;
    bool              mouseWasDragged;
  };

  Component* const m_parentComponent;
  Helper m_helper;
  bool m_mouseInside;
  bool m_mouseInsideNext;
  char m_mouseEvent [sizeof (MouseEvent)]; // HACK because of Juce!
};

#endif

