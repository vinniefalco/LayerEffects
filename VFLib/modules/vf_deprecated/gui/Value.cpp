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

DummyValue::DummyValue (double value, const String name)
: m_name (name)
, m_value (value)
{
}

const String DummyValue::getName ()
{
  return m_name;
}

double DummyValue::getValue ()
{
  return m_value;
}

const String DummyValue::getValueAsText ()
{
  return String (m_value, 3);
}

double DummyValue::getDefaultValue ()
{
  return 0;
}

void DummyValue::setValue (double newValue)
{
  newValue = jlimit (0., 1., newValue);

  if (m_value != newValue)
  {
    m_value = newValue;
    updateAllViews ();
  }
}

}

}
