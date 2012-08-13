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
  virtual ~MouseEnterEditable ();

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
