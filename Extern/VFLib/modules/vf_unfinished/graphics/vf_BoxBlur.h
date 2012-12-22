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

/** A box blur filter.

    @ingroup vf_gui
*/
struct BoxBlur
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

  /** Single box blur pass.

      This transposes rows and columns.

      Original version by Brian Fiete
  */
  struct Pass
  {
    /** Apply box blur pass.
    */
    template <class In, class Out>
    void operator () (In in, Out out, int w, int h, float radius) const
    {
      int widthMinus1 = w-1;
      int r = (int)radius;
      //int tableSize = 2*r+1;
      float frac = radius - r;

      int a = (int) (frac * 256);
      int oma = 256 - a;

      int aDiv = (2*r+1)*256 + a*2;

      for ( int y = 0; y < h; y++ ) 
      {
        int ta = 0;

        for ( int i = -r; i <= r; i++ ) 
        {
          //int rgb = in[inIndex + clamp(i, 0, w)];
          int rgb = in (clamp(i, 0, w), y);
          ta += rgb * 256;
        }
        //ta += a * in[inIndex + clamp(-r-1, 0, w)];
        ta += a * in (clamp (-r-1, 0, w), y);
        //ta += a * in[inIndex + clamp(r+1, 0, w)];
        ta += a * in (clamp (r+1, 0, w), y);

        for ( int x = 0; x < w; x++ ) 
        {
          out (y, x) = ta / aDiv;

          int r1 = x+r+1;
          int r2 = r1+1;
          if (r2 > widthMinus1)
          {				
            r2 = widthMinus1;
            if (r1 > widthMinus1)
              r1 = widthMinus1;
          }

          int l1 = x-r-1;
          int l2 = l1+1;
          if (l1 < 0)
          {
            l1 = 0;
            if (l2 < 0)
              l2 = 0;
          }

          int rgbL = (in (l1, y) * a) + (in (l2, y) * oma);
          int rgbR = (in (r1, y) * oma) + (in (r2, y) * a);

          ta += rgbR;
          ta -= rgbL;
        }
      }
    }
  };

  template <class In, class Out>
  void operator () (In in, Out out, int w, int h, float radius) const
  {
    float halfRadius = radius / 2.f;

    Map2D <int> temp (h, w);

    Pass () (in,   temp, w, h, halfRadius);
    Pass () (temp, out,  h, w, halfRadius);
    Pass () (out,  temp, w, h, halfRadius);
    Pass () (temp, out,  h, w, halfRadius);
  }
};
