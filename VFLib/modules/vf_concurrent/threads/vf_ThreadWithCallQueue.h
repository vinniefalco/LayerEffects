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

#ifndef VF_THREADWITHCALLQUEUE_VFHEADER
#define VF_THREADWITHCALLQUEUE_VFHEADER

/*============================================================================*/
/** 
    An InterruptibleThread with a CallQueue.

    This combines an InterruptibleThread with a CallQueue, allowing functors to
    be queued for asynchronous execution on the thread.

    The thread runs an optional user-defined idle function, which must regularly
    check for an interruption using the InterruptibleThread interface. When an
    interruption is signaled, the idle function returns and the CallQueue is
    synchronized. Then, the idle function is resumed.

    When the ThreadWithCallQueue first starts up, an optional user-defined
    initialization function is executed on the thread. When the thread exits,
    a user-defined exit function may be executed on the thread.

    @ingroup vf_concurrent
*/
class ThreadWithCallQueue : public CallQueue
{
public:
  typedef Function <bool (void)> idle_t;
  typedef Function <void (void)> init_t;
  typedef Function <void (void)> exit_t;

  /** Create a thread.

      @param name The name of the InterruptibleThread and CallQueue, used
                  for diagnostics when debugging.
  */
  explicit ThreadWithCallQueue (String name);

  /** Destroy a ThreadWithCallQueue.

      If the thread is still running it is stopped. The destructor blocks
      until the thread exits cleanly.
  */
  ~ThreadWithCallQueue ();

  /** Start the thread.

      All thread functions are invoked from the thread:

      @param thread_idle The function to call when the thread is idle.

      @param thread_init The function to call when the thread starts.

      @param thread_exit The function to call when the thread stops.
  */
  void start (idle_t thread_idle = idle_t::None(),
              init_t thread_init = init_t::None(),
              exit_t thread_exit = exit_t::None());

  /* Stop the thread.

     Stops the thread and optionally wait until it exits. It is safe to call
     this function at any time and as many times as desired.
     
     After a call to stop () the CallQueue is closed, and attempts to queue new
     functors will throw a runtime exception. Existing functors will still
     execute.

     Any listeners registered on the CallQueue need to be removed
     before stop is called

     @invariant The caller is not on the associated thread.

     @param wait `true` if the function should wait until the thread exits
                 before returning.
  */
     
  void stop (bool const wait);

  /**
    Determine if the thread needs interruption.
    
    Should be called periodically by the idle function. If interruptionPoint
    returns true or throws, it must not be called again until the idle function
    returns and is re-entered.

    @invariant No previous calls to interruptionPoint() made after the idle
               function entry point returned `true`.

    @return `false` if the idle function may continue, or `true` if the
            idle function must return as soon as possible.
  */
  bool interruptionPoint ();

  /* Interrupts the idle function.
  */
  void interrupt ();

private:
  void signal ();
  void reset ();

  void do_stop ();
  void run ();

private:
  bool m_calledStart;
  bool m_calledStop;
  bool m_shouldStop;
  CriticalSection m_mutex;
  InterruptibleThread m_thread;
  idle_t m_idle;
  init_t m_init;
  exit_t m_exit;
};

#endif
