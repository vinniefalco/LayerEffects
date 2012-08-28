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

#ifndef VF_GRADIENTOVERLAYSTYLE_VFHEADER
#define VF_GRADIENTOVERLAYSTYLE_VFHEADER

/** Computation of gradient blends.

    @ingroup vf_gui
*/
struct GradientOverlayStyle
{
  enum Kind
  {
    kindLinear = 1,
    kindRadial,
    kindAngle,
    kindReflected,
    kindDiamond
  };

  GradientOverlayStyle () : active (false)
  {
  }

  bool            active;
  BlendMode::Type mode;
  double          opacity;
  GradientColours colours;
  bool            reverse;
  Kind            kind;
  double          angle;
  double          scale;
  Point <int>     startPoint;
  Point <int>     endPoint;

  void operator() (Pixels destPixels);

  //----------------------------------------------------------------------------

  struct Render
  {
    explicit Render (Pixels dest) : m_dest (dest)
    {
    }

    inline void operator() (int const x, int const y, int const t) const noexcept
    {
      PixelARGB& dest (*((PixelARGB*)m_dest.getPixelPointer (x, y)));
      dest.getRed ()    = uint8 (t);
      dest.getGreen ()  = uint8 (t);
      dest.getBlue ()   = uint8 (t);
    }

  private:
    Pixels m_dest;
  };

  //----------------------------------------------------------------------------

  struct Linear
  {
    template <class Functor>
    void operator() (
      int rows,
      int cols,
      Point <int> p0,
      Point <int> p1,
      int const scale,
      Functor f)
    {
      // 1/m'
      float const m = float (p1.getY() - p0.getY()) / (p0.getX() - p1.getX());

      for (int y = 0; y < rows; ++y)
      {
        int const x0 = int (m * (y - p0.getY()) + p0.getX());
        int const x1 = int (m * (y - p1.getY()) + p1.getX());

        for (int x = 0; x < x0; ++x)
          f (x, y, 0);

        int const mod = x1 - x0;
        int const skip = scale / mod;
        int const step = scale;
        int value = 0;
        int accum = 0;

        for (int x = x0; x < x1; ++x)
        {
          f (x, y, value);

          value += skip;
          accum += step;

          if (accum >= mod)
          {
            accum -= mod;
            ++value;
          }
        }

        for (int x = x1; x < cols; ++x)
          f (x, y, scale);
      }
    }
  };

  //----------------------------------------------------------------------------

  struct Linearf
  {
    template <class Functor>
    void operator() (
      int rows,
      int cols,
      Point <int> p0,
      Point <int> p1,
      int const scale,
      Functor f)
    {
      // 1/m'
      float const m = float (p1.getY() - p0.getY()) / (p0.getX() - p1.getX());

      for (int y = 0; y < rows; ++y)
      {
        float const x0 = m * (y - p0.getY()) + p0.getX();
        float const x1 = m * (y - p1.getY()) + p1.getX();

        for (int x = 0; x < cols; ++x)
        {
          float t;
          if (x < x0)
            t = 0;
          else if (x >= x1)
            t = 1;
          else
            t = (x-x0)/(x1-x0);

          f (x, y, 255 * t);
        }
      }
    }
  };

  //----------------------------------------------------------------------------

  static inline float piFloat ()
  {
    return 3.14159265f;
  }

  static inline float piBy2Float ()
  {
    return 1.570796325f;
  }
  
  // |error| < 0.005
  static inline float fast_atan2f (float y, float x)
  {
    if ( x == 0.0f )
    {
      if ( y > 0.0f ) return piBy2Float ();
      if ( y == 0.0f ) return 0.0f;
      return -piBy2Float ();
    }
    float atan;
    float z = y/x;
    if ( fabsf( z ) < 1.0f )
    {
      atan = z/(1.0f + 0.28f*z*z);
      if ( x < 0.0f )
      {
        if ( y < 0.0f ) return atan - piFloat ();
        return atan + piFloat ();
      }
    }
    else
    {
      atan = piBy2Float () - z/(z*z + 0.28f);
      if ( y < 0.0f ) return atan - piFloat ();
    }
    return atan;
  }

  //----------------------------------------------------------------------------
  
  /** Angle gradient generator.
  */
  struct AngleGradientIterator
  {
    /** Create an angle gradient iterator.

        @param maxValue Multiplier to put value in the range [0, maxValue]
    */
    AngleGradientIterator (
      Pixels destPixels,
      Point <int> const& centerPoint,
      int maxValue)
      : m_destPixels (destPixels)
      , m_centerPoint (centerPoint)
      , m_maxValue (maxValue)
    {
    }

    /** Call functor for each pixel.
    */
    template <class Functor>
    void operator () (Functor f)
    {
      float inv = float (m_maxValue) / (2.f * piFloat ());

      for (int y = 0; y < m_destPixels.getRows (); ++y)
      {
        float const dy = float (m_centerPoint.getY () - y);

        uint8* dest = m_destPixels.getLinePointer (y);

        for (int x = 0; x < m_destPixels.getCols (); ++x)
        {
          float const rad = fast_atan2f (dy, float (m_centerPoint.getX () - x)) + piFloat ();
          int const value = static_cast <int> (inv * rad + 0.5);

          f (dest, value);

          dest = addBytesToPointer (dest, m_destPixels.getColBytes ());
        }
      }
    }

  private:
    AngleGradientIterator& operator= (AngleGradientIterator const&);

    Pixels m_destPixels;
    Point <int> const m_centerPoint;
    int const m_maxValue;
  };

  //----------------------------------------------------------------------------
  
  /** Diamond gradient generator.
  */
  struct DiamondGradientIterator
  {
    /** Create a diamond gradient iterator.

        @param maxValue Multiplier to put value in the range [0, maxValue]
    */
    DiamondGradientIterator (
      Pixels destPixels,
      Point <int> const& centerPoint,
      int maxValue)
      : m_destPixels (destPixels)
      , m_centerPoint (centerPoint)
      , m_maxValue (maxValue)
    {
    }

    /** Call functor for each pixel.
    */
    template <class Functor>
    void operator () (Functor f)
    {
      for (int y = 0; y < m_destPixels.getRows (); ++y)
      {
        float const dy = abs (float (m_centerPoint.getY () - y));

        uint8* dest = m_destPixels.getLinePointer (y);

        for (int x = 0; x < m_destPixels.getCols (); ++x)
        {
          float dist = dy + abs (m_centerPoint.getX () - x);

          int value = static_cast <int> (dist);

          if (value > m_maxValue)
            value = m_maxValue;

          f (dest, value);

          dest = addBytesToPointer (dest, m_destPixels.getColBytes ());
        }
      }
    }

  private:
    DiamondGradientIterator& operator= (DiamondGradientIterator const&);

    Pixels m_destPixels;
    Point <int> const m_centerPoint;
    int const m_maxValue;
  };
};

#endif
