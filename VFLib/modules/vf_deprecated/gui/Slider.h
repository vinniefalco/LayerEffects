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