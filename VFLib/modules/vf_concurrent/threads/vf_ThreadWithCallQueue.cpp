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

ThreadWithCallQueue::ThreadWithCallQueue (String name)
  : CallQueue (name)
  , m_thread (name)
  , m_calledStart (false)
  , m_calledStop (false)
  , m_shouldStop (false)
{
}

ThreadWithCallQueue::~ThreadWithCallQueue ()
{
  stop (true);
}

void ThreadWithCallQueue::start (idle_t worker_idle,
  init_t worker_init,
  exit_t worker_exit)
{
  {
    // TODO: Atomic for this
    CriticalSection::ScopedLockType lock (m_mutex);

    // start() MUST be called.
    vfassert (!m_calledStart);
    m_calledStart = true;
  }

  m_init = worker_init;
  m_idle = worker_idle;
  m_exit = worker_exit;

  m_thread.start (vf::bind (&ThreadWithCallQueue::run, this));
}

void ThreadWithCallQueue::stop (bool const wait)
{
  // can't call stop(true) from within a thread function
  vfassert (!wait || !m_thread.isTheCurrentThread ());

  {
    CriticalSection::ScopedLockType lock (m_mutex);

    // start() MUST be called.
    vfassert (m_calledStart);

    // TODO: Atomic for this
    if (!m_calledStop)
    {
      m_calledStop = true;

      {
        CriticalSection::ScopedUnlockType unlock (m_mutex); // getting fancy

        call (&ThreadWithCallQueue::do_stop, this);

        // in theory something could slip in here

        close ();
      }
    }
  }

  if (wait)
    m_thread.join ();
}

// Should be called periodically by the idle function.
// There are three possible results:
//
// #1 Returns false. The idle function may continue or return.
// #2 Returns true. The idle function should return as soon as possible.
// #3 Throws a Thread::Interruption exception.
//
// If interruptionPoint returns true or throws, it must
// not be called again before the thread has the opportunity to reset.
//
bool ThreadWithCallQueue::interruptionPoint ()
{
  return m_thread.interruptionPoint ();
}

// Interrupts the idle function by queueing a call that does nothing.
void ThreadWithCallQueue::interrupt ()
{
  call (Function <void (void)>::None ());
}

void ThreadWithCallQueue::signal ()
{
  m_thread.interrupt ();
}

void ThreadWithCallQueue::reset ()
{
}

void ThreadWithCallQueue::do_stop ()
{
  m_shouldStop = true;
}

void ThreadWithCallQueue::run ()
{
  m_init ();

  for (;;)
  {
    CallQueue::synchronize ();

    if (m_shouldStop)
      break;

    // idle_t::None() must return false for this to work.
    bool interrupted = m_idle ();

    if (!interrupted)
      interrupted = interruptionPoint ();

    if (!interrupted)
      m_thread.wait ();
  }

  m_exit ();
}
