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

void ThreadGroup::QuitType::operator() (Worker* worker)
{
  worker->setShouldExit ();
}

//==============================================================================

ThreadGroup::Worker::Worker (String name, ThreadGroup& group)
  : Thread (name)
  , m_group (group)
  , m_shouldExit (false)
{
  startThread ();
}

ThreadGroup::Worker::~Worker ()
{
  // Make sure the thread is stopped.
  stopThread (-1);
}

void ThreadGroup::Worker::setShouldExit ()
{
  m_shouldExit = true;
}

void ThreadGroup::Worker::run ()
{
  do
  {
    m_group.m_semaphore.wait ();

    Work* work = m_group.m_queue.pop_front ();

    jassert (work != nullptr);

    work->operator() (this);

    delete work;
  }
  while (!m_shouldExit);
}

//==============================================================================

ThreadGroup::ThreadGroup (int numberOfThreads)
  : m_numberOfThreads (numberOfThreads)
  , m_semaphore (0)
{
  for (int i = 0; i++ < numberOfThreads; )
  {
    String s;
    s << "ThreadGroup (" << i << ")";

    m_threads.push_front (new Worker (s, *this));
  }
}

ThreadGroup::~ThreadGroup ()
{
  // Put one quit item in the queue for each worker to stop.
  for (int i = 0; i < m_numberOfThreads; ++i)
  {
    m_queue.push_front (new (getAllocator ()) QuitType);

    m_semaphore.signal ();
  }

  for (;;)
  {
    Worker* worker = m_threads.pop_front ();

    if (worker != nullptr)
      delete worker;
    else
      break;
  }

  // There must not be pending work!
  jassert (m_queue.pop_front () == nullptr);
}

int ThreadGroup::getNumberOfThreads () const
{
  return m_numberOfThreads;
}
