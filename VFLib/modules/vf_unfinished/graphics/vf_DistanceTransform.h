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

#ifndef VF_DISTANCETRANSFORM_VFHEADER
#define VF_DISTANCETRANSFORM_VFHEADER

/** Distance transform calculations.

    @ingroup vf_gui
*/
struct DistanceTransform
{
  static Image calculate (Pixels maskPixels, int radius);

  //----------------------------------------------------------------------------

  /** Mask inclusion test functor.
  */
  struct WhiteTest
  {
    explicit WhiteTest (Pixels src) : m_src (src)
    {
    }

    inline bool operator () (int const x, int const y) const noexcept
    {
      return *m_src.getPixelPointer (x, y) < 128;
    }

  private:
    Pixels m_src;
  };

  /** Mask exclusion test functor.
  */
  struct BlackTest
  {
    explicit BlackTest (Pixels src) : m_src (src)
    {
    }

    inline bool operator () (int const x, int const y) const noexcept
    {
      return *m_src.getPixelPointer (x, y) > 127;
    }

  private:
    Pixels m_src;
  };

  struct OutputDistance
  {
    explicit OutputDistance (Pixels dest) : m_dest (dest)
    {
    }

    inline void operator () (int const x, int const y, double distanceSquared) const noexcept
    {
      *m_dest.getPixelPointer (x, y) = uint8 (sqrt (distanceSquared) + 0.5);
    }

  private:
    Pixels m_dest;
  };

  //----------------------------------------------------------------------------
  // 
  // "A General Algorithm for Computing Distance Transforms in Linear Time"
  //  2003, A. Meijster
  //
  struct Meijster
  {
    struct EuclideanMetric
    {
      static inline int f (int x_i, int gi) noexcept
      {
        return (x_i*x_i)+gi*gi;
      }

      static inline int sep (int i, int u, int gi, int gu, int inf) noexcept
      {
        return (u*u - i*i + gu*gu - gi*gi) / (2*(u-i));
      }
    };

    struct ManhattanMetric
    {
      static inline int f (int x_i, int gi) noexcept
      {
        return abs (x_i) + gi;
      }

      static inline int sep (int i, int u, int gi, int gu, int inf) noexcept
      {
        if (gu >= gi + u - i)
          return inf;
        else if (gi > gu + u - i)
          return -inf;
        else
          return (gu - gi + u + i) / 2;
      }
    };

    template <class Functor, class BoolImage, class Metric>
    static void calculate (Functor f, BoolImage test, int const m, int n, Metric metric)
    {
      HeapBlock <int> g (m * n);

      int const inf = m + n;

      // phase 1
      {
        for (int x = 0; x < m; ++x)
        {
          g [x] = test (x, 0) ? 0 : inf;

          // scan 1
          for (int y = 1; y < n; ++y)
          {
            int const ym = y*m;
            g [x+ym] = test (x, y) ? 0 : 1 + g [x+ym-m];
          }

          // scan 2
          for (int y = n-2; y >=0; --y)
          {
            int const ym = y*m;

            if (g [x+ym+m] < g [x+ym])
              g [x+ym] = 1 + g[x+ym+m];
          }
        }
      }

      // phase 2
      {
        HeapBlock <int> s (jmax (m, n));
        HeapBlock <int> t (jmax (m, n));

        for (int y = 0; y < n; ++y)
        {
          int q = 0;
          s [0] = 0;
          t [0] = 0;

          int const ym = y*m;

          // scan 3
          for (int u = 1; u < m; ++u)
          {
            while (q >= 0 && metric.f (t[q]-s[q], g[s[q]+ym]) > metric.f (t[q]-u, g[u+ym]))
              q--;

            if (q < 0)
            {
              q = 0;
              s [0] = u;
            }
            else
            {
              int const w = 1 + metric.sep (s[q], u, g[s[q]+ym], g[u+ym], inf);

              if (w < m)
              {
                ++q;
                s[q] = u;
                t[q] = w;
              }
            }
          }

          // scan 4
          for (int u = m-1; u >= 0; --u)
          {
            int const d = metric.f (u-s[q], g[s[q]+ym]);
            f (u, y, d);
            if (u == t[q])
              --q;
          }
        }
      }
    }

    static void calculate (Pixels destPixels, Pixels maskPixels)
    {
      jassert (destPixels.isSingleChannel ());
      jassert (maskPixels.isSingleChannel ());
      jassert (destPixels.getBounds () == maskPixels.getBounds ());

      calculate (
        OutputDistance (destPixels),
        BlackTest (maskPixels),
        maskPixels.getWidth (),
        maskPixels.getHeight (),
        ManhattanMetric ());
    }
  };

private:
  static float calcDistancePixel (Pixels mask, int x, int y, int radius);
};

#endif
