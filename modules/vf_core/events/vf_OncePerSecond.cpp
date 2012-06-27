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

class OncePerSecond::TimerSingleton
  : public ReferenceCountedSingleton <OncePerSecond::TimerSingleton>
{
private:
  TimerSingleton ()
    : ReferenceCountedSingleton <OncePerSecond::TimerSingleton> (
		SingletonLifetime::persistAfterCreation)
    , m_thread ("Once Per Second")
  {
    m_thread.start (vf::bind (&TimerSingleton::run, this));
  }

  ~TimerSingleton ()
  {
    m_thread.join ();

    vfassert (m_list.empty ());
  }

  void run ()
  {
    for(;;)
    {
      const bool interrupted = m_thread.wait (1000);

      if (interrupted)
        break;

      notify();
    }
  }

  void notify ()
  {
    CriticalSection::ScopedLockType lock (m_mutex);

    for (List::iterator iter = m_list.begin(); iter != m_list.end();)
    {
      OncePerSecond* object = iter->object;
      ++iter;
      object->doOncePerSecond ();
    }
  }

public:
  void insert (Elem* elem)
  {
    CriticalSection::ScopedLockType lock (m_mutex);

    m_list.push_back (*elem);
  }

  void remove (Elem* elem)
  {
    CriticalSection::ScopedLockType lock (m_mutex);

    m_list.erase (m_list.iterator_to (*elem));
  }

  static TimerSingleton* createInstance ()
  {
    return new TimerSingleton;
  }

private:
  InterruptibleThread m_thread;
  CriticalSection m_mutex;
  List m_list;
};

//------------------------------------------------------------------------------

OncePerSecond::OncePerSecond ()
{
  m_elem.instance = TimerSingleton::getInstance ();
  m_elem.object = this;
}

OncePerSecond::~OncePerSecond ()
{
}

void OncePerSecond::startOncePerSecond ()
{
  m_elem.instance->insert (&m_elem);
}

void OncePerSecond::endOncePerSecond ()
{
  m_elem.instance->remove (&m_elem);
}
