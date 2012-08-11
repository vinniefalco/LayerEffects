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

#ifndef VF_INNERGLOWSTYLE_VFHEADER
#define VF_INNERGLOWSTYLE_VFHEADER

/** Provides the Inner Glow layer style.

    @ingroup vf_gui
*/
struct InnerGlowStyle
{
  bool            active;
  BlendMode::Type mode;
  double          opacity;    // [0, 1]
  GradientColours colours;
  bool            precise;
  bool            reverse;
  double          choke;      // [0, 1]
  int             size;       // [0, 250]
  double          range;      // [0, 1]

  InnerGlowStyle () : active (false)
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
      if (distanceSquared > 0)
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
};

#endif
