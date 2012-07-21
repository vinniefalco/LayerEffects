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

namespace Ui {

namespace Model {

const String Button::getName ()
{
  return String::empty;
}

bool Button::isMomentary ()
{
  return false;
}

void Button::clicked (const ModifierKeys&)
{
}

void Button::pressed ()
{
}

void Button::released ()
{
}

//------------------------------------------------------------------------------

CheckButton::CheckButton ()
  : m_checked (false)
{
}

bool CheckButton::isChecked ()
{
  return m_checked;;
}

void CheckButton::setChecked (bool checked)
{
  if (m_checked != checked)
  {
    m_checked = checked;
    
    //updateAllViews ();
    modelChanged ();
    m_listeners.call (&Base::Listener::onModelChanged, (Model::Base*)this);
    m_listeners.call (&Listener::onCheckButtonChecked, this);
  }
}

//------------------------------------------------------------------------------

DummyButton::DummyButton (bool enabled)
{
  setEnabled (enabled);
}

//------------------------------------------------------------------------------

DummyCheckButton::DummyCheckButton (bool enabled)
{
  setEnabled (enabled);
}

void DummyCheckButton::clicked (ModifierKeys const&)
{
  setChecked (!isChecked ());
}

}

//------------------------------------------------------------------------------

namespace Facade {

Model::Button& Button::getModel ()
{
  return dynamic_cast <Model::Button&> (Base::getModel());
}

Control::Button& Button::getControl ()
{
  return dynamic_cast <Control::Button&> (Base::getControl ());
}

void Button::setButtonState (bool isMouseOverButton, bool isButtonDown)
{
  m_isMouseOverButton = isMouseOverButton;
  m_isButtonDown = isButtonDown;
}

bool Button::isMouseOverButton()
{
  return m_isMouseOverButton;
}

bool Button::isButtonDown()
{
  return m_isButtonDown;
}

void Button::onAttach ()
{
  Base::onAttach ();
}

//------------------------------------------------------------------------------

Model::CheckButton& CheckButton::getModel ()
{
  return dynamic_cast <Model::CheckButton&> (Base::getModel());
}

}

//------------------------------------------------------------------------------

namespace Control {

Button::StateDetector::StateDetector (Button* owner)
: m_owner (*owner)
, m_bWasDown (false)
{
}

void Button::StateDetector::buttonClicked (juce::Button* button)
{
}

void Button::StateDetector::buttonStateChanged (juce::Button* button)
{
  if( button->isDown() )
  {
    if( !m_bWasDown )
    {
      m_bWasDown = true;
      m_owner.getModel().pressed();
    }
  }
  else if( m_bWasDown )
  {
    m_bWasDown = false;
    m_owner.getModel().released();
  }
}

Button::Button (Facade::Button* facade,
                ReferenceCountedObjectPtr <Model::Button> model)
: Base (this, facade, model.getObject())
, juce::Button (String::empty)
, m_listener (this)
, m_bEnabledUnboundedMouseMovement (false)
{
  setTriggeredOnMouseDown (true);
  addListener (&m_listener);

  getModel().addView (this);
  getModel().addListener (this);

  setEnabled (getModel().isEnabled ());
}

Button::~Button()
{
  getModel().removeListener (this);
  getModel().removeView (this);
}

Model::Button& Button::getModel ()
{
  return dynamic_cast <Model::Button&> (Base::getModel());
}

Facade::Button& Button::getFacade ()
{
  return dynamic_cast <Facade::Button&> (Base::getFacade());
}

bool Button::isButtonDown ()
{
  return isDown ();
}

bool Button::isMouseOverButton ()
{
  return isOver();
}

void Button::paintButton (Graphics& g,
                          bool isMouseOverButton,
                          bool isButtonDown)
{
  getFacade().setEnabled (Button::isEnabled());
  getFacade().setButtonState (isMouseOverButton, isButtonDown);
  
#if 1
  getFacade().paintFacade (g);
#else
  getFacade().paint (g, getLocalBounds());
#endif
}

void Button::paintOverChildren (Graphics& g)
{
#if 1
  getFacade().paintOverChildren (g);
#else
  getFacade().paintOverChildren (g, getLocalBounds());
#endif
}

void Button::mouseDrag (const MouseEvent& e)
{
  if (Button::isEnabled())
  {
    if (getModel().isMomentary() && !m_bEnabledUnboundedMouseMovement)
    {
      e.source.enableUnboundedMouseMovement (true);
      m_bEnabledUnboundedMouseMovement = true;
    }

    Button::mouseDrag (e);
  }
}

void Button::mouseUp (const MouseEvent& e)
{
  if (Button::isEnabled())
  {
    m_bEnabledUnboundedMouseMovement=false;

    Button::mouseUp (e);
  }
}

void Button::clicked (const ModifierKeys& modifiers)
{
  getModel().clicked (modifiers);
}

void Button::enablementChanged ()
{
  if (isEnabled ())
    getFacade().setAlpha (1.f);
  else
    getFacade().setAlpha (.5f);

  updateView ();
}

void Button::updateView ()
{
#if 0
  setEnabled (getModel().isEnabled ());
  bool enabled = Button::isEnabled ();
  if (getFacade().isEnabled () != enabled)
    getFacade().setEnabled (enabled);

  // make the button look pressed when the model changes without user action
  //setState (getModel().isActive() ? buttonDown :
  //  (isMouseOver() ? buttonOver : buttonNormal));

  repaint();
#endif
}

}

}
