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

#ifndef VF_SAFEBOOL_VFHEADER
#define VF_SAFEBOOL_VFHEADER

//
// From http://www.artima.com/cppsource/safebool.html
//
// Allows evaluation of an object as bool,
// without the usual harmful side effects.
//

//------------------------------------------------------------------------------

namespace detail {

class SafeBoolBase
{
private:
  void disallowed () const { }

public:
  void allowed () const { }

protected:
  typedef void (SafeBoolBase::*boolean_t)() const;

  SafeBoolBase () { }
  SafeBoolBase (SafeBoolBase const&) { }
  SafeBoolBase& operator= (SafeBoolBase const&) { return *this; }
  ~SafeBoolBase () { }
};

}

//------------------------------------------------------------------------------

template <typename T = void>
class SafeBool : public detail::SafeBoolBase
{
public:
  operator boolean_t () const
  {
    return (static_cast <const T*> (this))->asBoolean ()
      ? &detail::SafeBoolBase::allowed : 0;
  }

protected:
  ~SafeBool() { }
};

template <typename T, typename U> 
void operator== (SafeBool <T> const& lhs, SafeBool <U> const& rhs)
{
  lhs.disallowed ();
}

template <typename T,typename U> 
void operator!= (SafeBool <T> const& lhs, SafeBool <U> const& rhs)
{
  lhs.disallowed ();
}

#endif


