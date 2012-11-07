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

/*
 NOTE

 This will not handle the case where a component is in edit
 mode and becomes de-parented.
*/

//------------------------------------------------------------------------------

MouseEnterEditable::Helper::Helper (Component* component,
                                    MouseEnterEditable* editable)
: m_component (component)
, m_editable (editable)
{
  m_component->addMouseListener (this, true);
}

MouseEnterEditable::Helper::~Helper ()
{
  m_component->removeMouseListener (this);
}

Component& MouseEnterEditable::Helper::getComponent ()
{
  return *m_component;
}

void MouseEnterEditable::Helper::mouseEnter (const MouseEvent& e)
{
  Container* container = m_component->findParentComponentOfClass <Container> ();
  jassert (container != nullptr);

  if (container != nullptr)
    container->mouseEnterEditableActivity (m_editable, true);
}

void MouseEnterEditable::Helper::mouseExit (const MouseEvent& e)
{
  Container* container = m_component->findParentComponentOfClass <Container> ();
  jassert (container != nullptr);

  if (container != nullptr)
    container->mouseEnterEditableActivity (m_editable, false);
}

//------------------------------------------------------------------------------

MouseEnterEditable::Container::Container ()
  : m_currentEdit (nullptr)
  , m_nextEdit (nullptr)
{
}

MouseEnterEditable::Container::~Container ()
{
}

MouseEnterEditable* MouseEnterEditable::Container::getCurrentEditable ()
{
  return m_currentEdit;
}

void MouseEnterEditable::Container::exitCurrentEditMode ()
{
  if (m_currentEdit != nullptr)
  {
    MouseEnterEditable* editable = m_currentEdit;
    m_currentEdit = nullptr;
    editable->onMouseEnterEditMode (false);
  }

  stopTimer ();
}

void MouseEnterEditable::Container::mouseEnterEditableActivity (
  MouseEnterEditable* editable,
  bool isMouseEnter)
{
  if (isMouseEnter)
  {
    stopTimer ();

    if (m_currentEdit != editable)
    {
      if (m_currentEdit != nullptr)
      {
        MouseEnterEditable* editable = m_currentEdit;
        m_currentEdit = nullptr;
        editable->onMouseEnterEditMode (false);
      }

      m_currentEdit = editable;
      m_currentEdit->onMouseEnterEditMode (true);
    }
  }
  else
  {
    startTimer (lingerMilliseconds);
  }
}

void MouseEnterEditable::Container::timerCallback ()
{
  jassert (m_currentEdit != nullptr);

  exitCurrentEditMode ();
}

//------------------------------------------------------------------------------

MouseEnterEditable::MouseEnterEditable (Component* component)
  : m_helper (component, this)
{
}

MouseEnterEditable::~MouseEnterEditable ()
{
  exitMouseEnterEditMode ();
}

bool MouseEnterEditable::isInMouseEnterEditMode ()
{
  bool inEditMode;
  Container* container = m_helper.getComponent().findParentComponentOfClass <Container> ();

  if (container != nullptr)
  {
    inEditMode = container->getCurrentEditable() == this;
  }
  else
  {
    inEditMode = false;
  }

  return inEditMode;
}

void MouseEnterEditable::exitMouseEnterEditMode ()
{
  Container* container = m_helper.getComponent().findParentComponentOfClass <Container> ();

  if (container != nullptr)
  {
    if (container->getCurrentEditable() == this)
      container->exitCurrentEditMode ();
  }
}
