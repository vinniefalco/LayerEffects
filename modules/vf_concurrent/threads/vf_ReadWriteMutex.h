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

#ifndef VF_READWRITEMUTEX_VFHEADER
#define VF_READWRITEMUTEX_VFHEADER

/*============================================================================*/
/**
  Multiple consumer, single producer (MCSP) synchronization primitive.

  This is an optimized lock for the multiple reader, single writer
  scenario. It provides only a subset of features of the more general
  traditional read/write lock. Specifically, these rules apply:

  - A caller cannot hold a read lock while acquiring a write lock.

  - Write locks are only recursive with respect to write locks.

  - Read locks are only recursive with respect to read locks.

  - A write lock cannot be downgraded.

  - Writes are preferenced over reads.

  For real-time applications, these restrictions are often not an issue.

  The implementation is wait-free in the fast path: acquiring read access
  for a lock without contention - just one interlocked increment!

  @class ReadWriteMutex
  @ingroup vf_concurrent
*/

/*============================================================================*/
/**
  Scoped read lock for ReadWriteMutex.

  @ingroup vf_concurrent
*/
template <class LockType>
struct GenericScopedReadLock : Uncopyable
{
  inline explicit GenericScopedReadLock (LockType const& lock) noexcept
    : m_lock (lock)
  {
    m_lock.enterRead ();
  }

  inline ~GenericScopedReadLock () noexcept
  {
    m_lock.exitRead ();
  }

private:
  LockType const& m_lock;
};

/*============================================================================*/
/**
  Scoped write lock for ReadWriteMutex.

  @ingroup vf_concurrent
*/
template <class LockType>
struct GenericScopedWriteLock : Uncopyable
{
  inline explicit GenericScopedWriteLock (LockType const& lock) noexcept
    : m_lock (lock)
  {
    m_lock.enterWrite ();
  }

  inline ~GenericScopedWriteLock () noexcept
  {
    m_lock.exitWrite ();
  }

private:
  LockType const& m_lock;
};

class ReadWriteMutex
{
public:
  /** Provides the type of scoped read lock to use with a ReadWriteMutex. */
  typedef GenericScopedReadLock <ReadWriteMutex> ScopedReadLockType;

  /** Provides the type of scoped write lock to use with a ReadWriteMutex. */
  typedef GenericScopedWriteLock <ReadWriteMutex> ScopedWriteLockType;

  /** Create a ReadWriteMutex */
  ReadWriteMutex () noexcept;
  
  /** Destroy a ReadWriteMutex

      If the object is destroyed while a lock is held, the result is
      undefined behavior.
  */
  ~ReadWriteMutex () noexcept;

  /** Acquire a read lock.

      This is recursive with respect to other read locks. Calling this while
      holding a write lock is undefined.
  */
  void enterRead () const noexcept;

  /** Release a previously acquired read lock */
  void exitRead () const noexcept;

  /** Acquire a write lock.

      This is recursive with respect to other write locks. Calling this while
      holding a read lock is undefined.
  */
  void enterWrite () const noexcept;

  /** Release a previously acquired write lock */
  void exitWrite () const noexcept;

private:
  CriticalSection m_mutex;

  mutable CacheLine::Padded <AtomicCounter> m_writes;
  mutable CacheLine::Padded <AtomicCounter> m_readers;
};

#endif
