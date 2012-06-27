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

#ifndef VF_LEAKCHECKED_VFHEADER
#define VF_LEAKCHECKED_VFHEADER

#include "vf_Error.h"
#include "vf_Throw.h"
#include "../memory/vf_StaticObject.h"
#include "../containers/vf_LockFreeStack.h"

//
// Derived classes are automatically leak-checked on exit
//

#if VF_USE_LEAKCHECKED

class LeakCheckedBase
{
public:
  static void detectAllLeaks ();

protected:
  class CounterBase : public LockFreeStack <CounterBase>::Node
  {
  public:
    CounterBase ();

    static void detectAllLeaks ();

  private:
    virtual void detectLeaks () = 0;

  private:
    class Singleton;
  };
};

//------------------------------------------------------------------------------

template <class Object>
class LeakChecked : private LeakCheckedBase
{
protected:
  LeakChecked () noexcept
  {
    if (getLeakCheckedCounter().increment () == 0)
    {
      DBG ("[LOGIC] " << getLeakCheckedName ());
      Throw (Error().fail (__FILE__, __LINE__));
    }
  }

  LeakChecked (const LeakChecked&) noexcept
  {
    if (getLeakCheckedCounter().increment() == 0)
    {
      DBG ("[LOGIC] " << getLeakCheckedName ());
      Throw (Error().fail (__FILE__, __LINE__));
    }
  }

  ~LeakChecked()
  {
    if (getLeakCheckedCounter().decrement () < 0)
    {
      DBG ("[LOGIC] " << getLeakCheckedName ());
      Throw (Error().fail (__FILE__, __LINE__));
    }
  }

private:
  class Counter : private CounterBase
  {
  public:
    inline int increment ()
    {
      return ++m_count;
    }

    inline int decrement ()
    {
      return --m_count;
    }
    
    void detectLeaks ()
    {
      const int count = m_count.get ();

      if (count > 0)
      {
        DBG ("[LEAK] " << count << " of " << getLeakCheckedName());
      }
    }

  private:
    Atomic <int> m_count;
  };

  static const char* getLeakCheckedName ()
  {
    return typeid (Object).name ();
  }

  static Counter& getLeakCheckedCounter() noexcept
  {
    static Counter* volatile s_instance;
    static Static::Initializer s_initializer;

    if (s_initializer.begin ())
    {
      static Counter s_object;
      s_instance = &s_object;
      s_initializer.end ();
    }

    return *s_instance;
  }
};

#else

class LeakCheckedBase
{
private:
  friend class PerformedAtExit;

  static void detectAllLeaks () { }
};

template <class Object>
struct LeakChecked : LeakCheckedBase
{
};

#endif

#endif
