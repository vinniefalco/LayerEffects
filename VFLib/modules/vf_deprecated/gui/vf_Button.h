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

#ifndef __VF_BUTTON_VFHEADER__
#define __VF_BUTTON_VFHEADER__

#include "vf_UiBase.h"

namespace Model {

// A Button can be pressed and released
//
class Button : public Model::Base
{
public:
  Button ();

  class Listener : public ListenerBase
  {
  public:
    virtual void onModelChecked (Button* model) = 0;
  };

  bool isChecked ();
  void setChecked (bool checked);

  // A momentary button maintains some continuous action or state while it
  // is pressed. The default control hides the cursor for momentary buttons.
  //
  virtual bool isMomentary ();

  virtual void clicked (ModifierKeys const& modifiers);
  virtual void pressed ();
  virtual void released ();

private:
  bool m_checked;
};

//------------------------------------------------------------------------------

// Simple button model as a placeholder to get things up and running
//
class DummyButton : public Button
{
public:
  DummyButton (bool enabled, bool checkButton = false);
  void clicked (ModifierKeys const& modifiers);

private:
  bool const m_checkButton;
};

}

//------------------------------------------------------------------------------

namespace Facade {

class Button : public ConnectedEdges
{
public:
  Button ();

  bool isMouseOverButton () const;
  bool isButtonDown () const;
  bool isEnabled () const;
  bool isChecked () const;

  void setMouseOverButton (bool isMouseOverButton);
  void setButtonDown (bool isButtonDown);
  void setEnabled (bool isEnabled);
  void setChecked (bool isChecked);

private:
  bool m_isMouseOverButton;
  bool m_isButtonDown;
  bool m_isEnabled;
  bool m_isChecked;
};

}

//------------------------------------------------------------------------------

namespace Control {

class Button
  : public Base
  , public Model::Button::Listener
  , public juce::Button
{
public:
  explicit Button (Model::Button* model = nullptr);
  ~Button ();

  void setConnectedEdgeFlag (int flag, bool connected)
  {
    if (connected)
      setConnectedEdges (getConnectedEdgeFlags () | flag);
    else
      setConnectedEdges (getConnectedEdgeFlags () & ~flag);
  }

  void setConnectedOnLeft (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnLeft, connected); }

  void setConnectedOnRight (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnRight, connected); }

  void setConnectedOnTop (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnTop, connected); }

  void setConnectedOnBottom (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnBottom, connected); }

  virtual bool isMomentary ();
  virtual void clicked (ModifierKeys const& modifiers);
  virtual void pressed ();
  virtual void released ();

  void paintButton (Graphics& g,
                    bool isMouseOverButton,
                    bool isButtonDown);

  void paintOverChildren (Graphics& g);

protected:
  virtual void updateFacade ();

  void enablementChanged ();
  void mouseDrag (MouseEvent const& e);
  void mouseUp (MouseEvent const& e);

  void onModelChecked (Model::Button* model);

private:
  class StateDetector
    : public juce::Button::Listener
    , public Uncopyable
  {
  public:
    explicit StateDetector (Button* owner);

  private:
    void buttonClicked (juce::Button* button);
    void buttonStateChanged (juce::Button* button);

  private:
    Button& m_owner;
    bool m_wasDown;
  };

private:
  StateDetector m_listener;
  bool m_bEnabledUnboundedMouseMovement;
};

}

#endif
