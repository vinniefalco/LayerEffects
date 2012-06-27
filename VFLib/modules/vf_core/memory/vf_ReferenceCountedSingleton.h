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

#ifndef VF_REFERENCECOUNTEDSINGLETON_VFHEADER
#define VF_REFERENCECOUNTEDSINGLETON_VFHEADER

#include "../events/vf_PerformedAtExit.h"
#include "../memory/vf_StaticObject.h"

/**
  Construction options for ReferenceCountedSingleton

  @ingroup vf_core
*/

// "base classes dependent on a template parameter aren't part of lookup." - ville
class SingletonLifetime
{
public:
  enum Lifetime
  {
    /** Singleton is created on first use and destroyed when
        the last reference is removed.
    */
    createOnDemand,

    /** Like createOnDemand, but after the Singleton is destroyed an
        exception will be thrown if an attempt is made to create it again.
    */
    createOnDemandOnce,

    /* The singleton is created on first use and persists until program exit.
    */
    persistAfterCreation
  };
};

//------------------------------------------------------------------------------
/**
  Thread-safe singleton which comes into existence on first use. Use this
  instead of creating objects with static storage duration. These singletons
  are automatically reference counted, so if you hold a pointer to it in every
  object that depends on it, the order of destruction of objects is assured
  to be correct.

  class Object must provide the function `Object* Object::createInstance()`

  @ingroup vf_core
*/
template <class Object>
class ReferenceCountedSingleton : private PerformedAtExit
{
protected:
  typedef SpinLock LockType;

  explicit ReferenceCountedSingleton (SingletonLifetime::Lifetime const lifetime)
    : m_lifetime (lifetime)
  {
    vfassert (s_instance == nullptr);

    if (m_lifetime == SingletonLifetime::persistAfterCreation)
    {
      incReferenceCount ();
    }
    else if (m_lifetime == SingletonLifetime::createOnDemandOnce && *s_created)
    {
      Throw (Error().fail (__FILE__, __LINE__));
    }

    *s_created = true;
  }

  virtual ~ReferenceCountedSingleton ()
  {
    vfassert (s_instance == nullptr);
  }

public:
  typedef ReferenceCountedObjectPtr <Object> Ptr;

  static Ptr getInstance ()
  {
    Ptr instance;

    instance = s_instance;

    if (instance == nullptr)
    {
      LockType::ScopedLockType lock (*s_mutex);

      instance = s_instance;
  
      if (instance == nullptr)
      {
        s_instance = Object::createInstance ();

        instance = s_instance;
      }
    }

    return instance;
  }

  inline void incReferenceCount() noexcept
  {
    m_refs.addref ();
  }

  inline void decReferenceCount() noexcept
  {
    if (m_refs.release ())
      destroySingleton ();
  }

  // Caller must synchronize.
  inline bool isBeingReferenced () const
  {
    return m_refs.isSignaled ();
  }

private:
  void performAtExit ()
  {
    if (m_lifetime == SingletonLifetime::persistAfterCreation)
      decReferenceCount ();
  }

  void destroySingleton ()
  {
    bool destroy;

    {
      LockType::ScopedLockType lock (*s_mutex);

      if (isBeingReferenced ())
      {
        destroy = false;
      }
      else
      {
        destroy = true;
        s_instance = 0;
      }
    }

    if (destroy)
    {
      delete this;
    }
  }

private:
  SingletonLifetime::Lifetime const m_lifetime;
  AtomicCounter m_refs;

private:
  static Object* s_instance;
  static Static::Storage <LockType, ReferenceCountedSingleton <Object> > s_mutex;
  static Static::Storage <bool, ReferenceCountedSingleton <Object> > s_created;
};

template <class Object>
Object* ReferenceCountedSingleton <Object>::s_instance;

template <class Object>
Static::Storage <typename ReferenceCountedSingleton <Object>::LockType, ReferenceCountedSingleton <Object> >
  ReferenceCountedSingleton <Object>::s_mutex;

template <class Object>
Static::Storage <bool, ReferenceCountedSingleton <Object> >
  ReferenceCountedSingleton <Object>::s_created;

#endif
