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

#ifndef VF_PARALLELFOR_VFHEADER
#define VF_PARALLELFOR_VFHEADER

/*============================================================================*/
/**
  @ingroup vf_concurrent

  @brief Parallel for loop.

  This uses a ThreadGroup to iterate through a for loop in parallel. The
  following two pieces of code perform identical operations:

  @code

  extern void function (int loopIndex);

  // Serial computation
  //
  for (int i = 0; i < numberOfIterations; ++i)
    function (i);

  // Parallel computation
  //
  ParallelFor().loop (numberOfIterations, &function);

  @endcode

  `function` is a caller provided functor. Convenience functions are provided
  for automatic binding to member or non member functions with up to 8
  arguments (not including the loop index).

  @note The last argument to function () is always the loop index.

  @see ThreadGroup
*/
class ParallelFor : Uncopyable
{
public:
  /** Create a parallel for loop.

      It is best to keep this object around instead of creating and destroying
      it every time you need to run a loop.

      @param pool The ThreadGroup to use. If this is ommitted then a singleton
                  ThreadGroup is used which contains one thread per CPU.
  */
  explicit ParallelFor (ThreadGroup& pool = *GlobalThreadGroup::getInstance ());

  /** Execute parallel for loop.

      Functor is called once for each value in the range
      [0, numberOfIterations), using the ThreadGroup.
  */
  template <class Functor>
  void loopf (int numberOfIterations, Functor const& f)
  {
    IterationType <Functor> iteration (f);

    doLoop (numberOfIterations, iteration);
  }

  template <class Fn>
  void loop (int n, Fn f)
  { loopf (n, vf::bind (f, vf::_1)); }

  template <class Fn,     typename  T1>
  void loop (int n, Fn f, const T1& t1)
  { loopf (n, vf::bind (f, t1, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2>
  void loop (int n, Fn f, const T1& t1, const T2& t2)
  { loopf (n, vf::bind (f, t1, t2, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2, typename  T3>
  void loop (int n, Fn f, const T1& t1, const T2& t2, const T3& t3)
  { loopf (n, vf::bind (f, t1, t2, t3, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2,
                          typename  T3, typename  T4>
  void loop (int n, Fn f, const T1& t1, const T2& t2,
                          const T3& t3, const T4& t4)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2, typename  T3,
                          typename  T4, typename  T5>
  void loop (int n, Fn f, const T1& t1, const T2& t2, const T3& t3,
                          const T4& t4, const T5& t5)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2, typename  T3,
                          typename  T4, typename  T5, typename  T6>
  void loop (int n, Fn f, const T1& t1, const T2& t2, const T3& t3,
                               const T4& t4, const T5& t5, const T6& t6)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, t6, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2, typename  T3, typename  T4,
                          typename  T5, typename  T6, typename  T7>
  void loop (int n, Fn f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                          const T5& t5, const T6& t6, const T7& t7)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, vf::_1)); }

  template <class Fn,     typename  T1, typename  T2, typename  T3, typename  T4,
                          typename  T5, typename  T6, typename  T7, typename  T8>
  void loop (int n, Fn f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
                          const T5& t5, const T6& t6, const T7& t7, const T8& t8)
  { loopf (n, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, t8, vf::_1)); }

private:
  class LoopState;

  class Iteration
  {
  public:
    virtual void operator () (int loopIndex) = 0;
  };

  template <class Functor>
  class IterationType : public Iteration, Uncopyable
  {
  public:
    explicit IterationType (Functor const& f) : m_f (f)
    {
    }

    void operator () (int loopIndex)
    {
      m_f (loopIndex);
    }

  private:
    Functor m_f;
  };

private:
  void doLoop (int numberOfIterations, Iteration& iteration);

private:
  ThreadGroup& m_pool;
  WaitableEvent m_finishedEvent;
  Atomic <int> m_currentIndex;
  Atomic <int> m_numberOfInstances;
  int m_numberOfIterations;
};

#endif
