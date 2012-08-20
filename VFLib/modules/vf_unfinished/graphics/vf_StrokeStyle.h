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

#ifndef VF_STROKESTYLE_VFHEADER
#define VF_STROKESTYLE_VFHEADER

/** Provides the Stroke layer style.

    @ingroup vf_gui
*/
struct StrokeStyle
{
  enum Pos
  {
    posOuter = 1,
    posInner,
    posCentre
  };

  enum Type
  {
    typeColour = 1,
    typeGradient,
    typePattern
  };

  StrokeStyle () : active (false)
  {
  }

  bool            active;
  Pos             pos;
  int             size;           // [0, 250]
  BlendMode::Type mode;
  double          opacity;
  Type            type;
  Colour          colour;
  GradientFill    gradient;
  PatternFill     pattern;

  void operator () (Pixels destPixels, Pixels maskPixels);

  //----------------------------------------------------------------------------

  struct Outside
  {
    explicit Outside (Pixels mask) : m_mask (mask)
    {
    }

    int operator() (int x, int y) const noexcept
    {
      return 255 - *m_mask.getPixelPointer (x, y);
    }

  public:
    Pixels m_mask;
  };

  //----------------------------------------------------------------------------

  struct Inside
  {
    explicit Inside (Pixels mask) : m_mask (mask)
    {
    }

    int operator() (int x, int y) const noexcept
    {
      return *m_mask.getPixelPointer (x, y);
    }

  public:
    Pixels m_mask;
  };

  //----------------------------------------------------------------------------

  struct RenderMask
  {
    RenderMask (Pixels::Map2D dest, int radius)
      : m_dest (dest)
      , m_radius (radius)
      , m_radiusSquared (radius * radius * 65536)
      , m_radiusPlusOneSquared ((radius + 1) * (radius + 1) * 65536)
    {
    }

    template <class T>
    void operator() (int const x, int const y, T const distanceSquared)
    {
      uint8 alpha;

      if (distanceSquared <= 0)
      {
        alpha = 0;
      }
      else if (distanceSquared < m_radiusSquared)
      {
        alpha = 255;
      }
      else if (distanceSquared < m_radiusPlusOneSquared)
      {
        double const distance = sqrt (double (distanceSquared) / 65536.) - m_radius;

        alpha = 255 - uint8 (255 * distance + 0.5);
      }
      else
      {
        alpha = 0;
      }

      m_dest (x, y) = alpha;
    }

  private:
    Pixels::Map2D m_dest;
    int m_radius;
    int64 m_radiusSquared;
    int64 m_radiusPlusOneSquared;
  };

  //----------------------------------------------------------------------------

  struct RenderPixel
  {
    RenderPixel (Pixels::Map2D dest, Colour colour, int radius)
      : m_dest (dest)
      , m_src (colour.getPixelARGB ())
      , m_radius (radius)
      , m_radiusSquared (radius * radius)
      , m_radiusMinusOneSquared ((radius - 1) * (radius - 1))
    {
    }

    template <class T>
    void operator() (int const x, int const y, T const distanceSquared)
    {
      if (distanceSquared > 0)
      {
        PixelRGB& dest = *((PixelRGB *)&m_dest (x, y));
  
        double distance = sqrt (double (distanceSquared) / 65536.);

        if (distance < m_radius)
        {
          dest.blend (m_src);
        }
        else
        {
          distance -= m_radius;

          if (distance < 1)
          {
            uint8 const alpha = 255 - uint8 (255 * distance + 0.5);
            dest.blend (m_src, alpha);
          }
        }
      }
    }

  private:
    Pixels::Map2D m_dest;
    PixelARGB m_src;
    int m_radius;
    int m_radiusSquared;
    int m_radiusMinusOneSquared;
  };
};

#endif
