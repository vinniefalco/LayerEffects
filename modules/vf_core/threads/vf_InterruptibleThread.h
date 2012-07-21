/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

#ifndef VF_INTERRUPTIBLETHREAD_VFHEADER
#define VF_INTERRUPTIBLETHREAD_VFHEADER

#include "../diagnostic/vf_SafeBool.h"
#include "../functor/vf_Function.h"

/*============================================================================*/
/**
  A thread with soft interruption support.

  The thread must periodically call interruptionPoint(), which returns
  true the first time an interruption has occurred since the last call to
  interruptionPoint().

  @ingroup vf_core
*/
class InterruptibleThread : public Thread
{
public:
  typedef Thread::ThreadID id;

  /**
    Construct an interruptible thread.

    The name is used for debugger diagnostics.

    @param name The name of the thread.
  */
  explicit InterruptibleThread (String name);

  /**
    Destroy the interruptible thread.

    This will signal an interrupt and wait until the thread exits.
  */
  ~InterruptibleThread ();

  /**
    Start the thread.
  */
  void start (Function <void (void)> const& f);

  /**
    Wait for the thread to exit.
  */
  void join ();

  /**
    Wait for interrupt or timeout.

    This call blocks until the thread is interrupted, or until the timeout
    expires if milliSeconds is non-negative.

    May only be called by the thread of execution.

    @param milliSeconds The amount of time to wait.
                        Negative values mean no timeout.
                        
    @return \c true if the interrupt occurred, or \c false if the timeout expired.
  */
  bool wait (int milliSeconds = -1);

  /**
    Interrupt the thread of execution.

    This can be called from any thread.
  */
  void interrupt ();

  /**
    Determine if an interruption is requested.

    After the function returns \c true, the interrupt status is cleared.
    Subsequent calls will return \c false until another interrupt is requested.

    May only be called by the thread of execution.

    @return \c true if an interrupt was requested.
  */
  bool interruptionPoint ();

  /**
    Get the ID of the associated thread.

    @return The ID of the thread.
  */
  id getId () const;

  /**
    Determine if this is the thread of execution.

    @note The return value is undefined if the thread is not running.

    @return \c true if the caller is this thread of execution.
  */
  bool isTheCurrentThread () const;

  /**
    Adjust the thread priority.

    @note This only affects some platforms.

    @param priority A number from 0..10
  */
  void setPriority (int priority);

private:
  void run ();

  Function <void (void)> m_function;
  WaitableEvent m_runEvent;
  id m_threadId;

  enum
  {
    stateRun,
    stateInterrupt,
    stateReturn,
    stateWait
  };

  AtomicState m_state;
};

//------------------------------------------------------------------------------

namespace CurrentInterruptibleThread
{

extern bool interruptionPoint ();

}

#endif
