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

#ifndef VF_UI_POPUPBUTTON_H
#define VF_UI_POPUPBUTTON_H

namespace Ui {

namespace Model {

class Popup : public Ui::Model::Base
{
public:
  virtual String getCurrentItemText();
  virtual void buildMenu (PopupMenu& menu);
  virtual void doMenuItem (int menuItemId);
};

}

//------------------------------------------------------------------------------

namespace Control {

class PopupButton
  : public juce::Button
  , public Control::View
{
public:
  PopupButton (Facade::Button* facade, Model::Popup* model);
  ~PopupButton ();

  Model::Popup& getModel();
  Facade::Button& getFacade();

  void setMenuItemHeight (int menuitemHeight);

protected:
  void doMenuItem (int menuItemId);
  void paintButton (Graphics& g,
                    bool isMouseOverButton,
                    bool isButtonDown);
  void clicked (const ModifierKeys&);
  void updateView ();

private:
  struct PopupLookAndFeel : LookAndFeel
  {
    LookAndFeel& m_owner;
    PopupLookAndFeel (LookAndFeel& owner);
  };

  struct Callback : ModalComponentManager::Callback, PopupLookAndFeel
  {
    PopupButton& m_owner;
    Callback (PopupButton& owner);
    void modalStateFinished (int returnValue);
  };

private:
  ScopedPointer<Facade::Button> m_facade;
  ReferenceCountedObjectPtr<Model::Popup> m_model;
  int m_menuItemHeight;
};

//------------------------------------------------------------------------------

template<class Facade, class Model>
class PopupButtonType
  : public PopupButton
{
public:
  PopupButtonType (Facade* facade, Model* model)
    : PopupButton (facade, model)
    , m_model (*model)
    , m_facade (*facade)
  {
  }

  Model& getModel()
  {
    return m_model;
  }

  Facade& getFacade()
  {
    return m_facade;
  }

private:
  Model& m_model;
  Facade& m_facade;
};

}

}

#endif
