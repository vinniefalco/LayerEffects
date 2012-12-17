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

  virtual ~MouseEnterGroup ()
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

