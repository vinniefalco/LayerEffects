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

#ifndef VF_SERIALFOR_VFHEADER
#define VF_SERIALFOR_VFHEADER

/*============================================================================*/

/** Serial for loop.

    Iterates a for loop sequentially. This is a drop in replacement for
    ParallelFor.

    @see ParallelFor

    @ingroup vf_core
*/
class SerialFor : Uncopyable
{
public:
  /** Create a serial for loop.

      Any passed argument is ignored.
  */
  template <class T>
  explicit SerialFor (T)
  {
  }

  /** Create a serial for loop.
  */
  SerialFor ()
  {
  }

  /** Determine the number of threads used to process loops.

      @return Always 1.
  */
  inline int getNumberOfThreads () const
  {
    return 1;
  }

  template <class Functor>
  inline void loop (int numberOfIterations, Functor f)
  {
    for (int i = 0; i < numberOfIterations; ++i)
      f (i);
  }

  /** @{ */
  template <class Fn>
  void operator () (int n, Fn f)
  { loop (n, vf::bind (f, vf::_1)); }

  template <class Fn, class T1>
  void operator() (int n, Fn f, T1 t1)
  { loop (n, vf::bind (f, t1, vf::_1)); }

  template <class Fn, class T1, class T2>
  void operator() (int n, Fn f, T1 t1, T2 t2)
  { loop (n, vf::bind (f, t1, t2, vf::_1)); }

  template <class Fn, class T1, class T2, class T3>
  void operator() (int n, Fn f, T1 t1, T2 t2, T3 t3)
  { loop (n, vf::bind (f, t1, t2, t3, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4>
  void operator() (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4)
  { loop (n, vf::bind (f, t1, t2, t3, t4, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5>
  void operator() (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
  { loop (n, vf::bind (f, t1, t2, t3, t4, t5, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5, class T6>
  void operator() (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
  { loop (n, vf::bind (f, t1, t2, t3, t4, t5, t6, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
  void operator() (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
  { loop (n, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, vf::_1)); }

  template <class Fn, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
  void operator() (int n, Fn f, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
  { loop (n, vf::bind (f, t1, t2, t3, t4, t5, t6, t7, t8, vf::_1)); }
  /** @} */
};

#endif
