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

/** Calculate Chamfer-5-7-11 distance transform.

    The returned values have 8 bits of fixed-point precision.

    Original version by Brian Fiete.

    This algorithm is described in:

      G. Borgefors, "Distance Transforms in Digital Images"
        Computer Vision, Graphics, and Image Processing #34, 344-371 (1986)
*/
struct ChamferDistance
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

  struct MaskInit
  {
    template <class T, class U>
    inline U operator() (T v, U inf)
    {
      if (v == 0)
        return inf;
      else
        return 255 - v;
    }
  };

  struct InverseMaskInit
  {
    template <class T, class U>
    inline U operator() (T v, U inf)
    {
      if (v == 255)
        return inf;
      else
        return v;
    }
  };

  template <class In, class Out, class Init>
  void operator () (
    In in,
    int const inRows,
    int const inCols,
    Out out,
    int const outRows,
    int const outCols,
    int const outX,
    int const outY,
    Init init = MaskInit ())
  {
    assert (outRows >= inRows && outCols >= inCols);

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
    static int const d1 = 253; // 252.6 = 256 * 0.9866
    static int const d2 = 362; // 362.0 = 256 * 1.4142
    static int const d3 = 566; // 565.8 = 256 * 2.2062

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

    static int const n = sizeof (fv) / sizeof (fv [0]);

    int const inf = (outCols + outRows) * d3;

    Map2D <int> d (outCols, outRows);

    //
    // Initialize distance map
    //

    for (int y = 0; y < outY; ++y)
    {
      for (int x = 0; x < outCols; ++x)
        d (x, y) = inf;
    }

    for (int y = outY + inRows; --y >= outY;)
    {
      for (int x = 0; x < inCols; ++x)
        d (x, y) = inf;

      for (int x = outX + inCols; x < outCols; ++x)
        d (x, y) = inf;
    }

    for (int y = outY + inRows; y < outRows; ++y)
    {
      for (int x = 0; x < outCols; ++x)
        d (x, y) = inf;
    }

    for (int y = 0; y < inRows; ++y)
    {
      for (int x = 0; x < inCols; ++x)
        d (x + outX, y + outY) = init (in (x, y), inf);
    }

    // forward pass
    for (int y = 0; y < outRows; ++y)
    {
      for (int x = 0; x < outCols; ++x)
      {
        for (int i = n-1; --i >= 0;)
        {
          int cx = clamp (x + fk [i][0], 0, outCols);
          int cy = clamp (y + fk [i][1], 0, outRows);
          int v = d (cx, cy) + fv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }
      }
    }

    // backward pass
    for (int y = outRows; --y >= 0;)
    {
      for (int x = outCols; --x >= 0;)
      {
        for (int i = n; --i >= 1;)
        {
          int cx = clamp (x + bk [i][0], 0, outCols);
          int cy = clamp (y + bk [i][1], 0, outRows);
          int v = d (cx, cy) + bv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }

        out (x, y, d (x, y));
      }
    }
  }
};

//------------------------------------------------------------------------------

/** Optimized Chamfer distance transform.
*/
struct FastChamferDistance
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
    // Muhammad Akmal Butt and Petros Maragos
    //  "Optimum Design of Chamfer Distance Transforms"
    //
    // Optimal values for 5x5 neighborhood:
    //  0.9866, sqrt(2), 2.2062
    //
    // The kernel is designed to also convert to fixed point.
    //
    static int const d1 = 253; // 252.6 = 256 * 0.9866
    static int const d2 = 362; // 362.0 = 256 * 1.4142
    static int const d3 = 566; // 565.8 = 256 * 2.2062

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

    static int const n = sizeof (fv) / sizeof (fv [0]);

    int const inf = (width + height) * d3;
    Map2D <int> d (width, height);

    int y;

    // initialize
    for (y = 0; y < height; ++y)
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

    int const y0 = std::min (2, height);
    int const y1 = height - 2;
    int const x0 = std::min (2, width);
    int const x1 = width - 2;

    //
    // forward pass
    //

    y = 0;

    for (;y < y0; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        for (int i = n-1; --i >= 0;)
        {
          int cx = clamp (x + fk [i][0], 0, width);
          int cy = clamp (y + fk [i][1], 0, height);
          int v = d (cx, cy) + fv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }
      }
    }

    for (;y < y1; ++y)
    {
      int x = 0;

      for (;x < x0; ++x)
      {
        for (int i = n-1; --i >= 0;)
        {
          int cx = clamp (x + fk [i][0], 0, width);
          int cy = clamp (y + fk [i][1], 0, height);
          int v = d (cx, cy) + fv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }
      }

      for (;x < x1; ++x)
      {
        int v;
        v = d (x-1, y-2) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x+1, y-2) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x-2, y-1) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x-1, y-1) + d2; if (v < d(x,y)) d(x,y) = v;
        v = d (x+0, y-1) + d1; if (v < d(x,y)) d(x,y) = v;
        v = d (x+1, y-1) + d2; if (v < d(x,y)) d(x,y) = v;
        v = d (x+2, y-1) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x-1, y-0) + d1; if (v < d(x,y)) d(x,y) = v;
      }

      for (;x < width; ++x)
      {
        for (int i = n-1; --i >= 0;)
        {
          int cx = clamp (x + fk [i][0], 0, width);
          int cy = clamp (y + fk [i][1], 0, height);
          int v = d (cx, cy) + fv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }
      }
    }

    for (;y < y0; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        for (int i = n-1; --i >= 0;)
        {
          int cx = clamp (x + fk [i][0], 0, width);
          int cy = clamp (y + fk [i][1], 0, height);
          int v = d (cx, cy) + fv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }
      }
    }

    //
    // backward pass
    //

    y = height;

    for (;--y >= y1;)
    {
      for (int x = width; --x >= 0;)
      {
        for (int i = n; --i >= 1;)
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

    for (;--y >= y0;)
    {
      int x = width;

      for (;--x >= x1;)
      {
        for (int i = n; --i >= 1;)
        {
          int cx = clamp (x + bk [i][0], 0, width);
          int cy = clamp (y + bk [i][1], 0, height);
          int v = d (cx, cy) + bv [i];
          if (v < d (x, y))
            d (x, y) = v;
        }

        out (x, y, d (x, y));
      }

      for (;--x >= x0;)
      {
        int v;
        v = d (x+1, y+0) + d1; if (v < d(x,y)) d(x,y) = v;
        v = d (x-2, y+1) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x-1, y+1) + d2; if (v < d(x,y)) d(x,y) = v;
        v = d (x+0, y+1) + d1; if (v < d(x,y)) d(x,y) = v;
        v = d (x+1, y+1) + d2; if (v < d(x,y)) d(x,y) = v;
        v = d (x+2, y+1) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x-1, y+2) + d3; if (v < d(x,y)) d(x,y) = v;
        v = d (x+1, y+2) + d3; if (v < d(x,y)) d(x,y) = v;

        out (x, y, d (x, y));
      }

      for (;--x >= 0;)
      {
        for (int i = n; --i >= 1;)
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

    for (;--y >= 0;)
    {
      for (int x = width; --x >= 0;)
      {
        for (int i = n; --i >= 1;)
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
