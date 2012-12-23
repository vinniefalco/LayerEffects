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

  /** Mask presence test functor.
  */
  struct AlphaTest
  {
    explicit AlphaTest (Pixels src) : m_src (src)
    {
    }

    inline bool operator () (int const x, int const y) const noexcept
    {
      return *m_src.getPixelPointer (x, y) != 0;
    }

  private:
    Pixels m_src;
  };

  //------------------------------------------------------------------------------

  /** Distance output to 8-bit unsigned.
  */
  struct OutputDistancePixels
  {
    OutputDistancePixels (Pixels dest, int radius)
      : m_dest (dest)
      , m_radius (radius)
      , m_radiusSquared (radius * radius)
    {
    }

    void operator () (int const x, int const y, double distance)
    {
      if (distance <= m_radiusSquared && distance > 0)
      {
        distance = sqrt (distance);

        *m_dest.getPixelPointer (x, y) = uint8 (255 * distance / m_radius + 0.5);
      }
      else
      {
        *m_dest.getPixelPointer (x, y) = 0;
      }
    }

  private:
    Pixels m_dest;
    int m_radius;
    int m_radiusSquared;
  };

  //----------------------------------------------------------------------------
  // 
  // "A General Algorithm for Computing Distance Transforms in Linear Time"
  //  - A. Meijster, 2003
  //
  struct Meijster
  {
    struct EuclideanMetric
    {
      template <class T>
      static inline T f (T x_i, T gi) noexcept
      {
        return (x_i*x_i)+gi*gi;
      }

      template <class T>
      static inline T sep (T i, T u, T gi, T gu, T) noexcept
      {
        return (u*u - i*i + gu*gu - gi*gi) / (2*(u-i));
      }
    };

    //--------------------------------------------------------------------------

    struct ManhattanMetric
    {
      template <class T>
      static inline T f (T x_i, T gi) noexcept
      {
        return abs (x_i) + gi;
      }

      template <class T>
      static inline int sep (T i, T u, T gi, T gu, T inf) noexcept
      {
        T const u_i = u - i;

        if (gu >= gi + u_i)
          return inf;
        else if (gi > gu + u_i)
          return -inf;
        else
          return (gu - gi + u + i) / 2;
      }
    };

    //--------------------------------------------------------------------------

    struct ChessMetric
    {
      template <class T>
      static inline T f (T x_i, T gi) noexcept
      {
        return jmax (abs (x_i), gi);
      }

      template <class T>
      static inline int sep (T i, T u, T gi, T gu, T) noexcept
      {
        if (gi <= gu)
          return jmax (i+gu, (i+u)/2);
        else
          return jmin (u-gi, (i+u)/2);
      }
    };

    //--------------------------------------------------------------------------

    template <class Functor, class BoolImage, class Metric>
    static void calculate (Functor f, BoolImage test, int const m, int const n, Metric metric)
    {
      std::vector <int> g (m * n);

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
        std::vector <int> s (jmax (m, n));
        std::vector <int> t (jmax (m, n));

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

    //--------------------------------------------------------------------------

    template <class T>
    static T floor_fixed8 (T x)
    {
      return x & (~T(0xff));
    }

    // Mask: 0 = point of interest
    //
    template <class Functor, class Mask, class Metric>
    static void calculateAntiAliased (Functor f, Mask mask, int const m, int const n, Metric metric)
    {
      int64 const scale = 256;

      std::vector <int64> g (m * n);

      int64 const inf = scale * (m + n);

      // phase 1
      {
        for (int x = 0; x < m; ++x)
        {
          int a;

          a = mask (x, 0);

          if (a == 0)
            g [x] = 0;
          else if (a == 255)
            g [x] = inf;
          else
            g [x] = a;

          // scan 1
          for (int y = 1; y < n; ++y)
          {
            int const idx = x+y*m;

            a = mask (x, y);
            if (a == 0)
              g [idx] = 0;
            else if (a == 255)
              g [idx] = scale + g [idx-m];
            else
              g [idx] = a;
          }

          // scan 2
          for (int y = n-2; y >=0; --y)
          {
            int const idx = x+y*m;
            int64 const d = scale + g [idx+m];
            if (g [idx] > d)
              g [idx] = d;
          }
        }
      }

      // phase 2
      {
        std::vector <int> s (jmax (m, n));
        std::vector <int64> t (jmax (m, n)); // scaled

        for (int y = 0; y < n; ++y)
        {
          int q = 0;
          s [0] = 0;
          t [0] = 0;

          int const ym = y*m;

          // scan 3
          for (int u = 1; u < m; ++u)
          {
            while (q >= 0 && metric.f (floor_fixed8(t[q]) - scale*s[q], g[s[q]+ym]) >
                             metric.f (floor_fixed8(t[q]) - scale*u, g[u+ym]))
            {
              q--;
            }

            if (q < 0)
            {
              q = 0;
              s [0] = u;
            }
            else
            {
              int64 const w = scale + metric.sep (scale*s[q], scale*u, g[s[q]+ym], g[u+ym], inf);

              if (w < scale * m)
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
            int64 const d = metric.f (scale*(u-s[q]), g[s[q]+ym]);
            f (u, y, d);
            if (u == t[q]/scale)
              --q;
          }
        }
      }
    }

    //--------------------------------------------------------------------------
    
    template <class Mask>
    struct Phase1
    {
      Phase1 (int m_, int n_, int64* g_, Mask mask_)
        : m (m_), n (n_), g (g_), mask (mask_)
      {
      }

      inline void operator() (int x) noexcept
      {
        int64 const inf = 256 * (m + n);
  
        int a;

        a = mask (x, 0);

        if (a == 0)
          g [x] = 0;
        else if (a == 255)
          g [x] = inf;
        else
          g [x] = a;

        // scan 1
        for (int y = 1; y < n; ++y)
        {
          int const idx = x+y*m;

          a = mask (x, y);
          if (a == 0)
            g [idx] = 0;
          else if (a == 255)
            g [idx] = 256 + g [idx-m];
          else
            g [idx] = a;
        }

        // scan 2
        for (int y = n-2; y >=0; --y)
        {
          int const idx = x+y*m;
          int64 const d = 256 + g [idx+m];
          if (g [idx] > d)
            g [idx] = d;
        }
      }
    
    private:
      int m;
      int n;
      int64* g;
      Mask mask;
    };

    template <class Functor, class Mask, class Metric>
    static void calculateAntiAliasedLoop (
      Functor f, Mask mask, int const m, int const n, Metric metric)
    {
      int64 const scale = 256;

      std::vector <int64> g (m * n);

      int64 const inf = scale * (m + n);

      // phase 1
      {
        Phase1 <Mask> p (m, n, &g[0], mask);
        for (int x = 0; x < m; ++x)
          p (x);
        //loop.operator() <Phase1 <Mask> > (m, m, n, &g[0], mask);

#if 0
        for (int x = 0; x < m; ++x)
        {
          int a;

          a = mask (x, 0);

          if (a == 0)
            g [x] = 0;
          else if (a == 255)
            g [x] = inf;
          else
            g [x] = a;

          // scan 1
          for (int y = 1; y < n; ++y)
          {
            int const idx = x+y*m;

            a = mask (x, y);
            if (a == 0)
              g [idx] = 0;
            else if (a == 255)
              g [idx] = scale + g [idx-m];
            else
              g [idx] = a;
          }

          // scan 2
          for (int y = n-2; y >=0; --y)
          {
            int const idx = x+y*m;
            int64 const d = scale + g [idx+m];
            if (g [idx] > d)
              g [idx] = d;
          }
        }
#endif
      }

      // phase 2
      {
        std::vector <int> s (jmax (m, n));
        std::vector <int64> t (jmax (m, n)); // scaled

        for (int y = 0; y < n; ++y)
        {
          int q = 0;
          s [0] = 0;
          t [0] = 0;

          int const ym = y*m;

          // scan 3
          for (int u = 1; u < m; ++u)
          {
            while (q >= 0 && metric.f (floor_fixed8(t[q]) - scale*s[q], g[s[q]+ym]) >
                             metric.f (floor_fixed8(t[q]) - scale*u, g[u+ym]))
            {
              q--;
            }

            if (q < 0)
            {
              q = 0;
              s [0] = u;
            }
            else
            {
              int64 const w = scale + metric.sep (scale*s[q], scale*u, g[s[q]+ym], g[u+ym], inf);

              if (w < scale * m)
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
            int64 const d = metric.f (scale*(u-s[q]), g[s[q]+ym]);
            f (u, y, d);
            if (u == t[q]/scale)
              --q;
          }
        }
      }
    }
  };

  //----------------------------------------------------------------------------
  // 
  // "The 'Dead Recoking' Signed Distance Transform"
  // - G. Grevera, 2004
  //
  template <class T>
  static T distsq (T x, T y)
  {
    return sqrt (x*x + y*y);
  }

  struct Grevera
  {
    template <class Functor, class BoolImage, class Metric>
    static void calculate (Functor f, BoolImage test, int const X, int const Y, Metric)
    {
      typedef double T;
      typedef Point <int> P;

      T const inf = (T(X)*T(X) + T(Y)*T(Y));
      T const d1 = 1;
      T const d2 = sqrt (2.);

      Map2D <T> d (X, Y);
      Map2D <P> p (X, Y);

      for (int y = 0; y < Y; ++y)
      {
        for (int x = 0; x < X; ++x)
        {
          d (x, y) = inf;
          p (x, y) = P (0, 0);
        }
      }

      for (int y = 1; y < Y-1; ++y)
      {
        for (int x = 1; x < X-1; ++x)
        {
          bool const v = test (x, y);
          if ( (test (x-1,y) != v) ||
               (test (x+1,y) != v) ||
               (test (x,y-1) != v) ||
               (test (x,y+1) != v))
          {
            d (x, y) = 0;
            p (x, y) = P (x, y);
          }
        }
      }

      for (int y = 1; y < Y-2; ++y)
      {
        for (int x = 1; x < X-2; ++x)
        {
          if (d(x-1,y-1)+d2 < d(x,y))
          {
            p(x,y) = p(x-1,y-1);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
          if (d(x,y-1)+d1 < d(x,y))
          {
            p(x,y) = p(x,y-1);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
          if (d(x+1,y-1)+d2 < d(x,y))
          {
            p(x,y) = p(x+1,y-1);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
          if (d(x-1,y)+d1 < d(x,y))
          {
            p(x,y) = p(x-1,y);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
        }
      }

      for (int y = Y-2; y >= 1; --y)
      {
        for (int x = X-2; x >= 1; --x)
        {
          if (d(x+1,y)+d1 < d(x,y))
          {
            p(x,y) = p(x+1,y);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
          if (d(x-1,y+1)+d2 < d(x,y))
          {
            p(x,y) = p(x-1,y+1);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
          if (d (x,y+1)+d1 < d(x,y))
          {
            p(x,y) = p(x,y+1);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }
          if (d(x+1,y+1)+d2 < d(x,y))
          {
            p(x,y) = p(x+1,y+1);
            d(x,y) = distsq (T(x-p(x,y).getX()), T(y-p(x,y).getY()));
          }

          T dist = d(x,y);
          if (test (x, y))
            f (x, y, -dist * dist);
          else
            f (x, y, dist * dist);
        }
      }
    }
  };

  //----------------------------------------------------------------------------
  // 
  // "Efficient Euclidean Distance Transform Using Perpendicular Bisector Segmentation"
  // - J. Wang, Y. Tan, ?
  //
  struct WangTan
  {
    template <class T>
    static T intersect (T ux, T vx, T du, T dv)
    {
      if (dv > du)
        return (dv - du) / (2 * (vx - ux));
      else
        return -2;
    }

    //--------------------------------------------------------------------------

    template <class T>
    static T distance (T ux, T vx, T dv)
    {
      return ux * (ux - vx * 2) + dv;
    }

    //--------------------------------------------------------------------------

    template <class Functor, class BoolImage, class Metric>
    static void calculate (Functor f, BoolImage test, int const n, int const m, Metric)
    {
      int const inf = 1+n*n+m*m;
      Map2D <int> I (n, m);

      // stage 1
      for (int c = 0; c < n; ++c)
      {
        int mid = -1;
        int const cc = c*c;

        for (int r = 0; r < m; ++r)
        {
          if (test (c,r))
          {
            if (mid > -1)
              mid = (r + mid) /2;
            for (int r_ = mid + 1; r_ <= r; ++r_)
              I (c, r_) = (r_-r)*(r_-r) + cc;
            mid = r;
          }
          else
          {
            if (mid == -1)
              I (c, r) = inf;
            else
              I (c, r) = (r-mid)*(r-mid) + cc;
          }
        }
      }

      // stage 2
      {
        std::vector <int> stack_c  (n);
        std::vector <int> stack_cx (n);
        std::vector <int> stack_g  (n);

        for (int r = 0; r < m; ++r)
        {
          int p = -1;

          for (int c = 0; c < n; ++c)
          {
            if (I (c, r) < inf)
            {
              for (;;)
              {
                int cx;

                if (p >= 0)
                {
                  cx = intersect (stack_c [p], c, stack_g [p], abs (I (c, r)));

                  if (cx == stack_cx [p])
                  {
                    --p;
                  }
                  else if (cx < stack_cx [p])
                  {
                    --p;
                    continue;
                  }
                  else if (cx >= (n - 1))
                  {
                    break;
                  }
                }
                else
                {
                  cx = -1;
                }

                ++p;
                stack_c  [p] = c;
                stack_cx [p] = cx;
                stack_g  [p] = I (c, r);
                break;
              }
            }
          }

          if (p < 0)
            return; // undefined!

          int c = 0;
          for (int k = 0; k <= p ; ++k)
          {
            int cx;
            if (k == p)
              cx = n-1;
            else
              cx = stack_cx [k+1];
            for (;c <= cx; ++c)
              I (c, r) = distance (c, stack_c [k], stack_g [k]);
          }
        }
      }

      // output
      for (int r = 0; r < m; ++r)
        for (int c = 0; c < n; ++c)
          f (c, r, I (c, r));
    }

    //--------------------------------------------------------------------------

    template <class Functor, class Map, class Metric>
    static void calculateAntiAliased (Functor f, Map map, int const n, int const m, Metric)
    {
      int64 const inf = 1+65536L*n*n+m*m;
      Map2D <int64> I (n, m);

      // stage 1
      for (int c = 0; c < n; ++c)
      {
        int mid = -1;
        int64 const cc = 65536L*c*c;

        for (int r = 0; r < m; ++r)
        {
          int const a = map (c, r);

          if (a == 0)
          {
            if (mid > -1)
              mid = (r + mid) /2;
            for (int r_ = mid + 1; r_ <= r; ++r_)
              I (c, r_) = 65536L*(r_-r)*(r_-r) + cc;
            mid = r;
          }
          else
          {
            if (mid == -1)
              I (c, r) = inf;
            else
              I (c, r) = 65536L*(r-mid)*(r-mid) + cc;
          }
        }
      }

      // stage 2
      {
        std::vector <int64> stack_c  (n);
        std::vector <int64> stack_cx (n);
        std::vector <int64> stack_g  (n);

        for (int r = 0; r < m; ++r)
        {
          int p = -1;

          for (int c = 0; c < n; ++c)
          {
            if (I (c, r) < inf)
            {
              for (;;)
              {
                int64 cx;

                if (p >= 0)
                {
                  cx = intersect <int64> (stack_c [p], 256 * c, stack_g [p], abs (I (c, r)));

                  if (cx == stack_cx [p])
                  {
                    --p;
                  }
                  else if (cx < stack_cx [p])
                  {
                    --p;
                    continue;
                  }
                  else if (cx >= 256 * (n - 1))
                  {
                    break;
                  }
                }
                else
                {
                  cx = -1;
                }

                ++p;
                stack_c  [p] = 256 * c;
                stack_cx [p] = cx;
                stack_g  [p] = I (c, r);
                break;
              }
            }
          }

          if (p < 0)
            return; // undefined!

          int c = 0;
          for (int k = 0; k <= p ; ++k)
          {
            int64 cx;
            if (k == p)
              cx = n-1;
            else
              cx = stack_cx [k+1];
            for (;c <= cx; ++c)
              I (c, r) = distance <int64> (256 * c, stack_c [k], stack_g [k]);
          }
        }
      }

      // output
      for (int r = 0; r < m; ++r)
        for (int c = 0; c < n; ++c)
          f (c, r, I (c, r));
    }
  };

  //----------------------------------------------------------------------------

  /** Calculate Chamfer-5-7-11 distance transform.

      The returned values have 8 bits of fixed-point precision.

      Original version by Brian Fiete.
  */
  struct Chamfer
  {
    /** Clamp v to the half-open interval [vmin, vmax)
    */
    template <class T>
    static inline T clamp (T v, T vmin, T vmax)
    {
      if (v < vmin)
        return vmin;
      else if (v >= vmax)
        return vmax - 1;
      else
        return v;
    }

    template <class In, class Out>
    void operator () (In in, Out out, int const width, int const height)
    {
      // Kernel values from
      //
      // "Optimum Design of Chamfer Distance Transforms"
      // - Muhammad Akmal Butt and Petros Maragos
      //
      // Optimal values for 5x5 neighborhood:
      //  0.9866, sqrt(2), 2.2062
      //
      // The kernel is designed to also convert to fixed point.
      //
#if 1
      static int const d1 = 253; // 252.6 = 256 * 0.9866
      static int const d2 = 362; // 362.0 = 256 * 1.4142
      static int const d3 = 566; // 565.8 = 256 * 2.2062
#else
      static int const d1 = 254;
      static int const d2 = 358;
      static int const d3 = 567;
#endif
      // forward kernel
      static int const fk [][2] = {
                  {-1, -2},          {1, -2}, 
        {-2, -1}, {-1, -1}, {0, -1}, {1, -1}, {2, -1},
                  {-1,  0}, {0,  0}
        };

      static int const fv  [] = {
            d3,     d3,
        d3, d2, d1, d2, d3,
            d1,  0
        };

      // backward kernel
      static int const bk [][2] = {
                            {0,  0}, {1,  0},
	{-2,  1}, {-1,  1}, {0,  1}, {1,  1}, {2,  1},
	          {-1,  2},          {1,  2}
        };

      static int const bv [] = {
                 0, d1,
        d3, d2, d1, d2, d3,
            d3,     d3
        };
/*
      static int const kd [][2] = {
                  {-1, -2},          {1, -2}, 
        {-2, -1}, {-1, -1}, {0, -1}, {1, -1}, {2, -1},
                  {-1,  0}, {0,  0}, {1,  0},
	{-2,  1}, {-1,  1}, {0,  1}, {1,  1}, {2,  1},
	          {-1,  2},          {1,  2}
        };

      static int const kv [] = {
             567,      567,
        567, 358, 254, 358, 567,
             254,  0,  254,
        567, 358, 254, 358, 567,
             567, 567
        };
*/

      static int const n = sizeof (fv) / sizeof (fv [0]);

      int const inf = (width + height) * 564;
      Map2D <int> d (width, height);

      // initialize
      for (int y = 0; y < height; ++y)
      {
        for (int x = 0; x < width; ++x)
        {
          int const v = in (x, y);
          if (v == 0)
            d (x, y) = inf;
          else
            d (x, y) = 255 - v;
        }
      }

      // forward pass
      for (int y = 0; y < height; ++y)
      {
        for (int x = 0; x < width; ++x)
        {
          for (int i = n; --i >= 0;)
          {
            int cx = clamp (x + fk [i][0], 0, width);
            int cy = clamp (y + fk [i][1], 0, height);
            int v = d (cx, cy) + fv [i];
            if (v < d (x, y))
              d (x, y) = v;
          }
        }
      }

      // backward pass
      for (int y = height; --y >= 0;)
      {
        for (int x = width; --x >= 0;)
        {
          for (int i = n; --i >= 0;)
          {
            int cx = clamp (x + bk [i][0], 0, width);
            int cy = clamp (y + bk [i][1], 0, height);
            int v = d (cx, cy) + bv [i];
            if (v < d (x, y))
              d (x, y) = v;
          }

          out (x, y, d (x, y));
        }
      }
    }
  };
};

#endif
