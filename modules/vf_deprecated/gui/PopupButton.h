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
