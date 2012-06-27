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

InterruptibleThread::InterruptibleThread (String name)
  : Thread (name)
  , m_state (stateRun)
{
}

InterruptibleThread::~InterruptibleThread ()
{
  m_runEvent.signal ();

  join ();
}

void InterruptibleThread::start (const Function <void (void)>& f)
{
  m_function = f;

  Thread::startThread ();

  // prevents data race with member variables
  m_runEvent.signal ();
}

void InterruptibleThread::join ()
{
  Thread::stopThread (-1);
}

bool InterruptibleThread::wait (int milliSeconds)
{
  // Can only be called from the current thread
  vfassert (isTheCurrentThread ());

  bool interrupted = false;

  for (;;)
  {
    vfassert (m_state != stateWait);

    // See if we are interrupted
    if (m_state.tryChangeState (stateInterrupt, stateRun))
    {
      // We were interrupted, state is changed to Run.
      // Caller must run now.
      interrupted = true;
      break;
    }
    else if (m_state.tryChangeState (stateRun, stateWait) ||
      m_state.tryChangeState (stateReturn, stateWait))
    {
      // Transitioned to wait.
      // Caller must wait now.
      interrupted = false;
      break;
    }
  }

  if (!interrupted)
  {
    interrupted = Thread::wait (milliSeconds);

    if (!interrupted)
    {
      if (m_state.tryChangeState (stateWait, stateRun))
      {
        interrupted = false;
      }
      else
      {
        vfassert (m_state == stateInterrupt);

        interrupted = true;
      }
    }
  }

  return interrupted;
}

void InterruptibleThread::interrupt ()
{
  for (;;)
  {
    int const state = m_state;

    if (state == stateInterrupt ||
      state == stateReturn ||
      m_state.tryChangeState (stateRun, stateInterrupt))
    {
      // Thread will see this at next interruption point.
      break;
    }
    else if (m_state.tryChangeState (stateWait, stateRun))
    {
      Thread::notify ();
      break;
    }
  }
}

bool InterruptibleThread::interruptionPoint ()
{
  // Can only be called from the current thread
  vfassert (isTheCurrentThread ());

  if (m_state == stateWait)
  {
    // It is impossible for this function
    // to be called while in the wait state.
    Throw (Error().fail (__FILE__, __LINE__));
  }
  else if (m_state == stateReturn)
  {
    // If this goes off it means the thread called the
    // interruption a second time after already getting interrupted.
    Throw (Error().fail (__FILE__, __LINE__));
  }

  // Switch to Return state if we are interrupted
  //bool const interrupted = m_state.tryChangeState (stateInterrupt, stateReturn);
  bool const interrupted = m_state.tryChangeState (stateInterrupt, stateRun);

  return interrupted;
}

InterruptibleThread::id InterruptibleThread::getId () const
{
  return m_threadId;
}

bool InterruptibleThread::isTheCurrentThread () const
{
  return Thread::getCurrentThreadId () == m_threadId;
}

void InterruptibleThread::setPriority (int priority)
{
  Thread::setPriority (priority);
}

void InterruptibleThread::run ()
{
  m_threadId = Thread::getThreadId ();

  m_runEvent.wait ();

  CatchAny (m_function);
}

//------------------------------------------------------------------------------

namespace CurrentInterruptibleThread
{

bool interruptionPoint ()
{
  bool interrupted = false;

  Thread* const thread = Thread::getCurrentThread();

  // Can't use interruption points on the message thread
  vfassert (thread != nullptr);

  if (thread)
  {
    InterruptibleThread* const interruptibleThread = dynamic_cast <InterruptibleThread*> (thread);

    vfassert (interruptibleThread != nullptr);

    if (interruptibleThread != nullptr)
    {
      interrupted = interruptibleThread->interruptionPoint ();
    }
    else
    {
      interrupted = false;
    }
  }
  else
  {
    interrupted = false;
  }

  return interrupted;
}

}
