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
