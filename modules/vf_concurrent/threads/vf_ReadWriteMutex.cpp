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

ReadWriteMutex::ReadWriteMutex () noexcept
{
}

ReadWriteMutex::~ReadWriteMutex () noexcept
{
}

void ReadWriteMutex::enterRead () const noexcept
{
  for (;;)
  {
    // attempt the lock optimistically
    // THIS IS NOT CACHE-FRIENDLY!
    m_readers->addref ();

    // is there a writer?
    // THIS IS NOT CACHE-FRIENDLY!
    if (m_writes->isSignaled ())
    {
      // a writer exists, give up the read lock
      m_readers->release ();

      // block until the writer is done
      {
        CriticalSection::ScopedLockType lock (m_mutex);
      }

      // now try the loop again
    }
    else
    {
      break;
    }
  }
}

void ReadWriteMutex::exitRead () const noexcept
{
  m_readers->release ();
}

void ReadWriteMutex::enterWrite () const noexcept
{
  // Optimistically acquire the write lock.
  m_writes->addref ();

  // Go for the mutex.
  // Another writer might block us here.
  m_mutex.enter ();

  // Only one competing writer will get here,
  // but we don't know who, so we have to drain
  // readers no matter what. New readers will be
  // blocked by the mutex.
  //
  if (m_readers->isSignaled ())
  {
    SpinDelay delay; 
    do
    {
      delay.pause ();
    }
    while (m_readers->isSignaled ());
  }
}

void ReadWriteMutex::exitWrite () const noexcept
{
  // Releasing the mutex first and then decrementing the
  // writer count allows another waiting writer to atomically
  // acquire the lock, thus starving readers. This fulfills
  // the write-preferencing requirement.

  m_mutex.exit ();

  m_writes->release ();
}
