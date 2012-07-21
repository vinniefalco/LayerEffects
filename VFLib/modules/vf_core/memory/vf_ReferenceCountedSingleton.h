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
