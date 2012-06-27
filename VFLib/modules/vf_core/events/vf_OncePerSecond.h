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

#ifndef VF_ONCEPERSECOND_VFHEADER
#define VF_ONCEPERSECOND_VFHEADER

#include "../containers/vf_List.h"

/*============================================================================*/
/** 
    Provides a once per second notification.

    Derive your class from OncePerSecond and override doOncePerSecond(). Then,
    call startOncePerSecond() to begin receiving the notifications. No clean-up
    or other actions are required.

    @ingroup vf_core
*/
class OncePerSecond : Uncopyable
{
public:
  OncePerSecond ();
  ~OncePerSecond ();

  /** Begin receiving notifications. */
  void startOncePerSecond ();

  /** Stop receiving notifications. */
  void endOncePerSecond ();

protected:
  /** Called once per second. */
  virtual void doOncePerSecond () = 0;

private:
  class TimerSingleton;
  typedef ReferenceCountedObjectPtr <TimerSingleton> TimerPtr;

  struct Elem;
  typedef List <Elem> List;
  struct Elem : List::Node
  {
    TimerPtr instance;
    OncePerSecond* object;
  };

  Elem m_elem;
};

#endif
