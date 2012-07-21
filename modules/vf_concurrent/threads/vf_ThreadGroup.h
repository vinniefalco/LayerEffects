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

#ifndef VF_THREADGROUP_VFHEADER
#define VF_THREADGROUP_VFHEADER

/*============================================================================*/
/**
  @ingroup vf_concurrent

  @brief A group of threads for parallelizing tasks.

  @see ParallelFor
*/
class ThreadGroup
{
public:
  typedef FifoFreeStoreType AllocatorType;

  /** Creates the specified number of threads.

      @param numberOfThreads The number of threads in the group. This must be
                             greater than zero. If this parameter is omitted,
                             one thread is created per available CPU.
  */
  explicit ThreadGroup (int numberOfThreads = SystemStats::getNumCpus ());

  ~ThreadGroup ();

  /** Determine the number of threads in the group.

      @return The number of threads in the group.
  */
  int getNumberOfThreads () const;

  /** Calls a functor on multiple threads.

      The specified functor is executed on some or all available threads at once.
      A call is always guaranteed to execute.

      @param maxThreads The maximum number of threads to use, or -1 for all.
  */
  template <class Functor>
  void callf (int maxThreads, Functor const& f)
  {
    jassert (maxThreads > 0 || maxThreads == -1);

    int numberOfThreads = getNumberOfThreads ();

    if (maxThreads != -1 && maxThreads < numberOfThreads)
      numberOfThreads = maxThreads;

    while (numberOfThreads--)
    {
      m_queue.push_front (new (getAllocator ()) WorkType <Functor> (f));
      m_semaphore.signal ();
    }
  }

  /** Allocator access.
  */
  inline AllocatorType& getAllocator ()
  {
    return m_allocator;
  }

  template <class Fn>
  void call (int maxThreads, Fn f)
  { callf (maxThreads, vf::bind (f)); }

  template <class Fn,              typename  T1>
  void call (int maxThreads, Fn f, const T1& t1)
  { callf (maxThreads, vf::bind (f, t1)); }

  template <class Fn,              typename  T1, typename  T2>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2)
  { callf (maxThreads, vf::bind (f, t1, t2)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3)
  { callf (maxThreads, vf::bind (f, t1, t2, t3)); }

  template <class Fn,              typename  T1, typename  T2,
                                   typename  T3, typename  T4>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2,
                                   const T3& t3, const T4& t4)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3,
                                   typename  T4, typename  T5>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3,
                                   const T4& t4, const T5& t5)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3,
                                   typename  T4, typename  T5, typename  T6>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3,
                                   const T4& t4, const T5& t5, const T6& t6)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5, t6)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3, typename  T4,
                                   typename  T5, typename  T6, typename  T7>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                                   const T5& t5, const T6& t6, const T7& t7)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5, t6, t7)); }

  template <class Fn,              typename  T1, typename  T2, typename  T3, typename  T4,
                                   typename  T5, typename  T6, typename  T7, typename  T8>
  void call (int maxThreads, Fn f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                                   const T5& t5, const T6& t6, const T7& t7, const T8& t8)
  { callf (maxThreads, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, t8)); }

private:
  void stopThreads (int numberOfThreadsToStop);

  //============================================================================
private:
  /** A thread in the group.
  */
  class Worker
    : public LockFreeStack <Worker>::Node
    , public Thread
    , LeakChecked <Worker>
  {
  public:
    Worker (String name, ThreadGroup& group);
    ~Worker ();

    void setShouldExit ();

  private:
    void run ();

  private:
    ThreadGroup& m_group;
    bool m_shouldExit;
  };

  //============================================================================
private:
  /** Abstract work item.
  */
  class Work : public LockFreeStack <Work>::Node
             , public AllocatedBy <AllocatorType>
  {
  public:
    virtual ~Work () { }

    /* The worker is passed in so we can make it quit later.
    */
    virtual void operator() (Worker* worker) = 0;
  };

  template <class Functor>
  class WorkType : public Work, LeakChecked <WorkType <Functor> >
  {
  public:
    explicit WorkType (Functor const& f) : m_f (f) { }
    ~WorkType () { }
    void operator() (Worker*) { m_f (); }

  private:
    Functor m_f;
  };

  /** Used to make a Worker stop
  */
  class QuitType
    : public Work
    , LeakChecked <QuitType>
  {
  public:
    void operator() (Worker* worker);
  };

private:
  int const m_numberOfThreads;
  Semaphore m_semaphore;
  AllocatorType m_allocator;
  LockFreeStack <Work> m_queue;
  LockFreeStack <Worker> m_threads;
};

#endif
