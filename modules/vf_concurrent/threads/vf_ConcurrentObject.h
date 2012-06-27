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

#ifndef VF_CONCURRENTOBJECT_VFHEADER
#define VF_CONCURRENTOBJECT_VFHEADER

/*============================================================================*/
/** 
    A reference counted object, deleted on a separate thread.

    This is a reference counted object compatible with
    ReferenceCountedObjectPtr. When the last reference is removed, the
    object is queued for deletion on a separate, provided thread. On
    program exit the thread will clean itself up - no other action is
    required.

    This class is useful for offloading the deletion work of "deep" objects
    shared by multiple threads: objects containing complex members, or a
    hierarchy of allocated structures. For example, a ValueTree. The problem
    of performing heavyweight memory or cleanup operations from either an
    AudioIODeviceCallback or the message thread is avoided.

    The deletion behavior can be overriden by providing a replacement
    for destroyConcurrentObject().

    @ingroup vf_concurrent
*/
class ConcurrentObject : Uncopyable
{
public:
  inline void incReferenceCount() noexcept
  {
    m_refs.addref ();
  }

  inline void decReferenceCount() noexcept
  {
    if (m_refs.release ())
      destroyConcurrentObject ();
  }

  /** Determine if the object is still being referenced.

      This is not thread safe, so the caller must synchronize.

      @return true if the object has one or more references.

      @internal
  */
  inline bool isBeingReferenced () const
  {
    return m_refs.isSignaled ();
  }

protected:
  ConcurrentObject();

  virtual ~ConcurrentObject();

  /** Delete the object.

      This function is called when the reference count drops to zero. The
      default implementation performs the delete on a separate, provided thread
      that cleans up after itself on exit.
  */
  virtual void destroyConcurrentObject ();

protected:
  class Deleter;

private:
  AtomicCounter m_refs;
};

#endif

