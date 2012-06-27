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

#ifndef VF_UI_VALUE_H
#define VF_UI_VALUE_H

#include "Meter.h"

namespace Ui {

// A Value is a Meter which can be changed through user interaction

//------------------------------------------------------------------------------

namespace Model {

class Value : public Model::Meter
{
public:
  virtual double getDefaultValue () = 0;
  virtual void setValue (double newValue) = 0;
};

//------------------------------------------------------------------------------

class DummyValue : public Value
{
public:
  DummyValue (double value = 0, const String name = String::empty);
  const String getName ();
  double getValue ();
  const String getValueAsText ();
  double getDefaultValue ();
  void setValue (double newValue);

private:
  String m_name;
  double m_value;
};

}

//------------------------------------------------------------------------------

namespace Facade {

}

//------------------------------------------------------------------------------

namespace Control {

}

}

#endif