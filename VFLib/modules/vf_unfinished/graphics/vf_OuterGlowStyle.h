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

#ifndef VF_OUTERGLOWSTYLE_VFHEADER
#define VF_OUTERGLOWSTYLE_VFHEADER

/** Provides the Outer Glow layer style.

    @ingroup vf_gui
*/
struct OuterGlowStyle
{
  bool            active;
  BlendMode::Type mode;
  double          opacity;  // [0, 1]
  GradientColours colours;
  bool            precise;
  double          spread;   // [0, 1]
  int             size;     // [0, 250]
  double          range;    // [0, 1]

  OuterGlowStyle () : active (false)
  {
  }

  void operator() (Pixels destPixels, Pixels maskPixels);

  struct RenderPixel
  {
    RenderPixel (Pixels dest,
                 double opacity,
                 double choke,
                 int size,
                 SharedTable <Colour> colourTable)
      : m_dest (dest)
      , m_alpha (uint8 (255 * opacity + 0.5))
      , m_choke (int (choke * size + 0.5))
      , m_size (size)
      , m_table (colourTable)
    {
      jassert (dest.isRGB ());
    }

    void operator () (int x, int y, int distanceSquared)
    {
      if (distanceSquared > 0 && distanceSquared <= m_size * m_size)
      {
        int index;

        double dist = sqrt (double (distanceSquared));

        if (dist < m_choke)
        {
          index = 0;
        }
        else
        {
          int const last = m_table.getNumEntries () - 1;

          if (dist >= m_size)
          {
            index = last;
          }
          else
          {
            index = int (last * (dist - m_choke) / (m_size - m_choke));
          }
        }

        PixelARGB const& src (m_table [index].getPixelARGB ());
        PixelRGB& dest (*((PixelRGB*)m_dest.getPixelPointer (x, y)));

        dest.blend (src, m_alpha);
      }
    }

  private:
    Pixels m_dest;
    uint8 m_alpha;
    int m_choke;
    int m_size;
    SharedTable <Colour> m_table;
  };

  //----------------------------------------------------------------------------

  struct DistanceMaskOutside
  {
    explicit DistanceMaskOutside (Pixels mask) : m_mask (mask)
    {
    }

    int operator() (int x, int y) const noexcept
    {
      return *m_mask.getPixelPointer (x, y);
    }

  public:
    Pixels m_mask;
  };

  struct RenderPixelAntiAliased
  {
    RenderPixelAntiAliased (Pixels dest,
                            double opacity,
                            double choke,
                            int size,
                            SharedTable <Colour> colourTable)
      : m_dest (dest)
      , m_alpha (uint8 (255 * opacity + 0.5))
      , m_choke (int (choke * size + 0.5))
      , m_size (size)
      , m_table (colourTable)
    {
      jassert (dest.isRGB ());
    }

    void operator () (int x, int y, int distanceSquared)
    {
      double dist = sqrt (double (distanceSquared) / 65536);

      if (dist > 0)
      {
        PixelRGB& dest (*((PixelRGB*)m_dest.getPixelPointer (x, y)));

        if (dist <= m_size)
        {
          dest.blend (m_table [0].getPixelARGB ());
        }
        else if (dist < m_size + 1)
        {
          uint8 a = uint8(255*((m_size+1)-dist)+0.5);
          dest.blend (m_table [0].getPixelARGB (), a);
        }
      }
    }

  private:
    Pixels m_dest;
    uint8 m_alpha;
    int m_choke;
    int m_size;
    SharedTable <Colour> m_table;
  };

};

#endif
