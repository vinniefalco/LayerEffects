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

//------------------------------------------------------------------------------

namespace Model {

const String Meter::getValueAsText ()
{
  return String::empty;
}

//------------------------------------------------------------------------------

DummyMeter::DummyMeter (double value, const String name)
: m_name (name)
, m_value (value)
{
}

const String DummyMeter::getName ()
{
  return m_name;
}

double DummyMeter::getValue ()
{
  return m_value;
}

const String DummyMeter::getValueAsText ()
{
  return String (m_value, 3);
}

}

//------------------------------------------------------------------------------

namespace Facade {

Meter::Meter()
  : m_value (0)
{
}

void Meter::setValue (double value)
{
  m_value = value;
}

double Meter::getValue ()
{
  return m_value;
}

}

//------------------------------------------------------------------------------

namespace Control {

Meter::Meter (Facade::Meter* facade, Model::Meter* model)
: Base (this, facade, model)
, m_facade (facade)
, m_model(model)
{
  getModel().addView (this);
}

Meter::~Meter()
{
  getModel().removeView (this);
}

Model::Meter& Meter::getModel()
{
  return *m_model;
}

Facade::Meter& Meter::getFacade()
{
  return *m_facade;
}

void Meter::paint (Graphics& g)
{
  getFacade().paint (g, getLocalBounds());
}

void Meter::paintOverChildren (Graphics& g)
{
  getFacade().paintOverChildren (g, getLocalBounds());
}

void Meter::enablementChanged ()
{
  updateView ();
}

void Meter::updateView ()
{
  setEnabled (getModel().isEnabled());
  getFacade().setEnabled (isEnabled ());
  getFacade().setValue (getModel().getValue ());
  repaint();
}

}

}
