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

#ifndef VF_UI_SLIDER_H
#define VF_UI_SLIDER_H

#include "Value.h"

namespace Ui {

// A slider is a bar or knob that can take on values from 0..1 inclusive

//------------------------------------------------------------------------------

namespace Model {

class Slider : public Model::Value
{
};

//------------------------------------------------------------------------------

class DummySlider : public Model::DummyValue
{
};

}

//------------------------------------------------------------------------------

namespace Facade {

class Slider : public Facade::Base
{
public:
  enum Style
  {
    rotary,
    topToBottom,
    bottomToTop,
    leftToRight,
  };

  explicit Slider (Style style);

  void setValue (double value);
  Style getStyle ();
  double getValue ();

private:
  Style m_style;
  double m_value;
};

}

//------------------------------------------------------------------------------

namespace Control {

class Slider
  : public Component
  , public Control::Base
{
public:
  Slider (Facade::Slider* facade, Model::Slider* model);
  ~Slider ();

  Model::Slider& getModel();
  Facade::Slider& getFacade();

  virtual int getStepCount();

  void paint (Graphics& g);
  void paintOverChildren (Graphics& g);

protected:
  void mouseDown (const MouseEvent& e);
  void mouseDrag (const MouseEvent& e);
  void mouseDoubleClick (const MouseEvent& e);
  void mouseWheelMove (const MouseEvent& event, const MouseWheelDetails& wheel);
  void enablementChanged ();
  void updateView ();

  double toFacadeValue (double modelValue);

private:
  Facade::Slider* m_facade;
  ReferenceCountedObjectPtr <Model::Slider> m_model;
  bool m_bEnableUnboundedMouseMovement;
  double m_startValue;
};

}

}

#endif