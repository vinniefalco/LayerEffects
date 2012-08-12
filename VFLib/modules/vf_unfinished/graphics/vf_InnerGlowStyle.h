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

  //----------------------------------------------------------------------------

  struct TestMask
  {
    explicit TestMask (Pixels src) : m_src (src)
    {
    }

    inline bool operator () (int const x, int const y) const noexcept
    {
      return *m_src.getPixelPointer (x, y) == 0;
    }

  private:
    Pixels m_src;
  };

  //----------------------------------------------------------------------------

  /** Fixed point square root function.

      @tparam count The number of fractional bits of precision.
  */
  template <int count>
  static unsigned int isqrtf (unsigned int x)
  {
    unsigned long root = 0;
    unsigned long remHi = 0;
    unsigned long remLo = x;
    unsigned long testDiv;

    for (int i = count; i--;)
    {
      remHi = (remHi<<2) | (remLo>>30); remLo <<= 2;
      root <<= 1;
      unsigned long testDiv = (root << 1) + 1;
    
      if (remHi >= testDiv)
      {
        remHi -= testDiv;
        root++;
      }
    }

    return root;
  }

  //----------------------------------------------------------------------------

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
      , m_size (size + 1)
      , m_table (colourTable)
    {
      jassert (dest.isRGB ());
    }

    inline void operator () (int const x, int const y, int const distanceSquared) const noexcept
    {
      if (distanceSquared > 0)
      {
        int index;

        double dist = sqrt (double (distanceSquared));
        //double dist = double (isqrtf <8> (distanceSquared)) / 256;

        if (dist < m_choke)
        {
          index = 0;
        }
        else if (dist < m_size)
        {
          index = int ((m_table.getNumEntries () - 1) * (dist - m_choke) / double (m_size - m_choke) + 0.5);
        }
        else
        {
          index = m_table.getNumEntries () - 1;
        }

        PixelRGB& dest (*((PixelRGB*)m_dest.getPixelPointer (x, y)));
        dest.blend (m_table [index].getPixelARGB (), m_alpha);
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

  struct GetMask
  {
    explicit GetMask (Pixels mask) : m_mask (mask)
    {
    }

    // Return distance from point of interest.
    //
    // 0      = point of interest
    // 1..254 = fractional distance to point of interest
    // 255    = not a point of interest
    //
    int operator() (int x, int y) const noexcept
    {
      return *m_mask.getPixelPointer (x, y);
    }

  public:
    Pixels m_mask;
  };

  //----------------------------------------------------------------------------

  struct RenderPixelAntiAliased
  {
    RenderPixelAntiAliased (Pixels dest,
                            double opacity,
                            double choke,
                            int size,
                            SharedTable <Colour> colourTable)
      : m_dest (dest)
      , m_alpha (uint8 (255 * opacity + 0.5))
      , m_choke (jmin (int (choke * size + 0.5), size))
      , m_size (size + 1)
      , m_table (colourTable)
    {
      jassert (dest.isRGB ());
    }

    template <class T>
    inline void operator () (int const x, int const y, T const distanceSquared) const noexcept
    {
      if (distanceSquared > 0)
      {
        int index;

        double dist = sqrt (double (distanceSquared) / 65536);

        if (dist < m_choke)
        {
          index = 0;
        }
        else if (dist <= m_size)
        {
          index = int((m_table.getNumEntries () - 1) * (dist - m_choke) / double (m_size - m_choke) + 0.5);
        }
        else
        {
          index = m_table.getNumEntries () - 1;
        }

        PixelRGB& dest (*((PixelRGB*)m_dest.getPixelPointer (x, y)));
        dest.blend (m_table [index].getPixelARGB (), m_alpha);
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
