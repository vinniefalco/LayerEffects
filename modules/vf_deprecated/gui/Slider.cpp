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

}

//------------------------------------------------------------------------------

namespace Facade {

Slider::Slider(Style style)
: m_style (style)
, m_value (0)
{
}

void Slider::setValue (double value)
{
  m_value = jlimit (0., 1., value);
}

Slider::Style Slider::getStyle ()
{
  return m_style;
}

double Slider::getValue ()
{
  return m_value;
}

}

//------------------------------------------------------------------------------

namespace Control {

Slider::Slider (Facade::Slider* facade, Model::Slider* model)
: Base (this, facade, model)
, m_facade(facade)
, m_model(model)
, m_bEnableUnboundedMouseMovement (false)
{
  m_model->addView (this);
}

Slider::~Slider()
{
  m_model->removeView (this);
}

Model::Slider& Slider::getModel ()
{
  return *m_model;
}

Facade::Slider& Slider::getFacade()
{
  return *m_facade;
}

int Slider::getStepCount ()
{
  return 16;
}

void Slider::paint (Graphics& g)
{
  m_facade->paint (g);
}

void Slider::paintOverChildren (Graphics& g)
{
  m_facade->paintOverChildren (g);
}

void Slider::mouseDown (const MouseEvent& e)
{
  if (isEnabled())
  {
    m_startValue = m_model->getValue();

    m_bEnableUnboundedMouseMovement = true;
  }
}

void Slider::mouseDrag (const MouseEvent& e)
{
  if (isEnabled())
  {
    // we do this here instead of mouseDown so that
    // the cursor doesn't disappear on a double click.
    if (m_bEnableUnboundedMouseMovement)
    {
      e.source.enableUnboundedMouseMovement (true, false);
      m_bEnableUnboundedMouseMovement = false;
    }

    double newValue;
    Facade::Slider::Style style = m_facade->getStyle ();

    double x = e.getDistanceFromDragStartX();
    double y = e.getDistanceFromDragStartY();

    switch (style)
    {
    case Facade::Slider::rotary:
    case Facade::Slider::bottomToTop:
      x = x / 1500;
      y = -y / 250;
      break;

    case Facade::Slider::topToBottom:
      x = -x / 1500;
      y = y / 250;
      break;

    case Facade::Slider::leftToRight:
      x = x / 250;
      y = -y / 1500;
      break;

    default:
      newValue=0;
      break;
    };

    newValue = m_startValue + x + y;

    if (newValue > 1)
    {
      m_startValue -= newValue - 1;
      newValue = 1;
    }
    else if( newValue < 0 )
    {
      m_startValue -= newValue;
      newValue = 0;
    }

    m_model->setValue (newValue);
  }
}

void Slider::mouseDoubleClick (const MouseEvent& e)
{
  if (isEnabled())
    m_model->setValue (m_model->getDefaultValue ());
}

void Slider::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
{
  if (isEnabled())
  {
    int stepCount = getStepCount();
    if (stepCount > 0)
    {
      double step = (wheel.isReversed ? -1. : 1) /getStepCount() * ( wheel.deltaY > 0 ? 1 : -1 );
      double newValue = m_model->getValue() + step;
      m_model->setValue (newValue);
    }
  }
}

void Slider::enablementChanged ()
{
  updateView ();
}

void Slider::updateView ()
{
  setEnabled (m_model->isEnabled());

  // we could still be disabled here if a parent Component is
  // disabled, so we have to call Component::isEnabled() to get
  // the actual state.
  m_facade->setEnabled (isEnabled ());
  m_facade->setValue ( toFacadeValue (m_model->getValue ()));
  repaint ();
}

double Slider::toFacadeValue (double modelValue)
{
  double facadeValue;

  switch (m_facade->getStyle())
  {
  case Facade::Slider::topToBottom:
    facadeValue = 1 - modelValue;
    break;
  
  default:
    facadeValue = modelValue;
    break;
  };

  return facadeValue;
}

}

}
