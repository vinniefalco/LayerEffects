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
