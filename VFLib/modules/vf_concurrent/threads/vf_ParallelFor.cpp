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

class ParallelFor::LoopState
  : public AllocatedBy <ThreadGroup::AllocatorType>
  , Uncopyable
{
private:
  Iteration& m_iteration;
  WaitableEvent& m_finishedEvent;
  int const m_numberOfIterations;
  Atomic <int> m_loopIndex;
  Atomic <int> m_iterationsRemaining;
  Atomic <int> m_numberOfParallelInstances;

public:
  LoopState (Iteration& iteration,
             WaitableEvent& finishedEvent,
             int numberOfIterations,
             int numberOfParallelInstances)
    : m_iteration (iteration)
    , m_finishedEvent (finishedEvent)
    , m_numberOfIterations (numberOfIterations)
    , m_loopIndex (-1)
    , m_iterationsRemaining (numberOfIterations)
    , m_numberOfParallelInstances (numberOfParallelInstances)
  {
  }

  ~LoopState ()
  {
  }

  void forLoopBody ()
  {
    for (;;)
    {
      // Request a loop index to process.
      int const loopIndex = ++m_loopIndex;

      // Is it in range?
      if (loopIndex < m_numberOfIterations)
      {
        // Yes, so process it.
        m_iteration (loopIndex);

        // Was this the last work item to complete?
        if (--m_iterationsRemaining == 0)
        {
          // Yes, signal.
          m_finishedEvent.signal ();
          break;
        }
      }
      else
      {
        // Out of range, all work is complete or assigned.
        break;
      }
    }

    release ();
  }

  void release ()
  {
    if (--m_numberOfParallelInstances == 0)
      delete this;
  }
};

//==============================================================================

ParallelFor::ParallelFor (ThreadGroup& pool)
  : m_pool (pool)
  , m_finishedEvent (false) // auto-reset
{
}

void ParallelFor::doLoop (int numberOfIterations, Iteration& iteration)
{
  if (numberOfIterations > 1)
  {
    int const numberOfThreads = m_pool.getNumberOfThreads ();

    // The largest number of pool threads we need is one less than the number
    // of iterations, because we also run the loop body on the caller's thread.
    //
    int const maxThreads = numberOfIterations - 1;

    // Calculate the number of parallel instances as the smaller of the number
    // of threads available (including the caller's) and the number of iterations.
    //
    int const numberOfParallelInstances = std::min (
      numberOfThreads + 1, numberOfIterations);

    LoopState* loopState (new (m_pool.getAllocator ()) LoopState (
      iteration, m_finishedEvent, numberOfIterations, numberOfParallelInstances));

    m_pool.call (maxThreads, &LoopState::forLoopBody, loopState);

    // Also use the caller's thread to run the loop body.
    loopState->forLoopBody ();

    m_finishedEvent.wait ();
  }
  else if (numberOfIterations == 1)
  {
    // Just one iteration, so do it.
    iteration (0);
  }
}
