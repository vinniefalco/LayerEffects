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

String Popup::getCurrentItemText ()
{
  return String::empty;
}

void Popup::buildMenu (PopupMenu& menu)
{
}

void Popup::doMenuItem (int menuItemId)
{
}

}

//------------------------------------------------------------------------------

namespace Control {

PopupButton::PopupLookAndFeel::PopupLookAndFeel (LookAndFeel& owner)
: m_owner (owner)
{
}

PopupButton::Callback::Callback (PopupButton& owner)
  : PopupLookAndFeel (owner.getLookAndFeel())
  , m_owner (owner)
{
}

void PopupButton::Callback::modalStateFinished (int returnValue)
{
  if (returnValue)
    m_owner.doMenuItem (returnValue);
}

PopupButton::PopupButton (Facade::Button* facade, Model::Popup* model)
: Button (String::empty)
, m_facade (facade)
, m_model (model)
, m_menuItemHeight (15)
{
  if (m_model)
    m_model->addView (this);
}

PopupButton::~PopupButton ()
{
  if (m_model)
    m_model->removeView (this);
}

Model::Popup& PopupButton::getModel ()
{
  return *m_model;
}

Facade::Button& PopupButton::getFacade()
{
  return *m_facade;
}

void PopupButton::setMenuItemHeight (int menuItemHeight)
{
  m_menuItemHeight = menuItemHeight;
}

void PopupButton::doMenuItem (int menuItemId)
{
  if (m_model)
    m_model->doMenuItem (menuItemId);
}

void PopupButton::paintButton (Graphics& g,
                             bool isMouseOverButton,
                             bool isButtonDown)
{
  m_facade->setEnabled (isEnabled());
  m_facade->setButtonState (isMouseOverButton, isButtonDown);
  m_facade->paint (g, getLocalBounds());
}

void PopupButton::clicked (const ModifierKeys&)
{
  if (m_model)
  {
    PopupMenu menu;
    m_model->buildMenu (menu);

    Callback* c = new Callback (*this);

    Colour color = findColour (PopupMenu::backgroundColourId, true);
    c->setColour (PopupMenu::backgroundColourId, findColour (PopupMenu::backgroundColourId, true));
    c->setColour (PopupMenu::textColourId, findColour (PopupMenu::textColourId, true));
    c->setColour (PopupMenu::headerTextColourId, findColour (PopupMenu::headerTextColourId, true));
    c->setColour (PopupMenu::highlightedBackgroundColourId, findColour (PopupMenu::highlightedBackgroundColourId, true));
    c->setColour (PopupMenu::highlightedTextColourId, findColour (PopupMenu::highlightedTextColourId, true));

    setState (buttonDown);

    menu.setLookAndFeel (c);
    menu.showAt (this, 0, 0, 0, m_menuItemHeight, c);
  }
}

void PopupButton::updateView ()
{
  if (m_model)
  {
    m_facade->setEnabled (m_model->isEnabled ());
    //m_facade->setTextLabel (m_model->getCurrentItemText());
    repaint ();
  }
}

}

}
