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

#if VF_USE_LEAKCHECKED

/*============================================================================*/
// Type-independent portion of Counter
class LeakCheckedBase::CounterBase::Singleton
{
public:
  void push_back (CounterBase* counter)
  {
    m_list.push_front (counter);
  }

  void detectAllLeaks ()
  {
    CounterBase* counter = m_list.pop_front ();
    
    while (counter != nullptr)
    {
      counter->detectLeaks ();
      
      counter = m_list.pop_front ();
    }
  }

  static Singleton& getInstance ()
  {
    static Singleton instance;

    return instance;
  }

private:
  LockFreeStack <CounterBase> m_list;
};

//------------------------------------------------------------------------------

LeakCheckedBase::CounterBase::CounterBase ()
{
  Singleton::getInstance().push_back (this);
}

void LeakCheckedBase::CounterBase::detectAllLeaks ()
{
  Singleton::getInstance().detectAllLeaks ();
}

//------------------------------------------------------------------------------

void LeakCheckedBase::detectAllLeaks ()
{
  CounterBase::detectAllLeaks ();
}

#endif
