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

/** Pixel compositing functors.

    @ingroup vf_gui
*/
namespace BlendProc
{
  struct Gray
  {
    template <class ModeType>
    struct CopyMode
    {
      explicit CopyMode (ModeType mode = ModeType ())
        : m_mode (mode)
      {
      }

      inline void operator () (uint8* dest, uint8 const* src) noexcept
      {
        *dest = uint8 (m_mode (*src, *dest));
      }

    private:
      ModeType m_mode;
    };

    //----------------------------------------------------------------------------

    struct Copy
    {
      Copy (double opacity)
        : m_alpha (int (256 * opacity + 0.5))
      {
      }

      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest, uint8 const* src) const noexcept
      {
        *dest = uint8 (int (*dest) + (((m_alpha * (mode (*src, *dest) - *dest)) + 128) >> 8));
      }

    private:
      Copy& operator= (Copy const&);

      int const m_alpha;
    };
  };

  //----------------------------------------------------------------------------

  struct RGB
  {
    struct MaskFill
    {
      MaskFill (Colour const& colour, double opacity)
        : m_alpha (int (257 * opacity + 0.5))
      {
        m_src [0] = colour.getRed ();
        m_src [1] = colour.getGreen ();
        m_src [2] = colour.getBlue ();
      }
      
      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest, uint8 const* mask) const noexcept
      {
        int const m = *mask;
        PixelRGB& d (*((PixelRGB*)dest));

        d.getRed ()   = uint8 (d.getRed ()   + ((m * m_alpha * (mode (m_src [0], d.getRed ())   - d.getRed ())   + 32769) >> 16));
        d.getGreen () = uint8 (d.getGreen () + ((m * m_alpha * (mode (m_src [1], d.getGreen ()) - d.getGreen ()) + 32769) >> 16));
        d.getBlue ()  = uint8 (d.getBlue ()  + ((m * m_alpha * (mode (m_src [2], d.getBlue ())  - d.getBlue ())  + 32769) >> 16));
      }

    private:
      int m_alpha;
      uint8 m_src[3];
    };

    //---

    struct Fill
    {
      Fill (Colour const& colour, double opacity)
        : m_alpha (int (256 * opacity + 0.5))
      {
        m_src [0] = colour.getRed ();
        m_src [1] = colour.getGreen ();
        m_src [2] = colour.getBlue ();
      }

      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest) const noexcept
      {
        PixelRGB& d (*((PixelRGB*)dest));

        d.getRed ()   = uint8 (d.getRed ()   + ((m_alpha * (mode (m_src [0], d.getRed ())   - d.getRed ())   + 128) >> 8));
        d.getGreen () = uint8 (d.getGreen () + ((m_alpha * (mode (m_src [1], d.getGreen ()) - d.getGreen ()) + 128) >> 8));
        d.getBlue ()  = uint8 (d.getBlue ()  + ((m_alpha * (mode (m_src [2], d.getBlue ())  - d.getBlue ())  + 128) >> 8));
      }

    private:
      int m_alpha;
      uint8 m_src[3];
    };

    //---

    struct Copy
    {
      explicit Copy (double opacity)
        : m_alpha (int (256 * opacity + 0.5))
      {
      }
      
      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest, uint8 const* src) const noexcept
      {
        PixelRGB& d (*((PixelRGB*)dest));
        PixelRGB const& s (*((PixelRGB*)src));

        d.getRed ()   = uint8 (d.getRed ()   + ((m_alpha * (mode (s.getRed (),   d.getRed ())   - d.getRed ())   + 128) >> 8));
        d.getGreen () = uint8 (d.getGreen () + ((m_alpha * (mode (s.getGreen (), d.getGreen ()) - d.getGreen ()) + 128) >> 8));
        d.getBlue ()  = uint8 (d.getBlue ()  + ((m_alpha * (mode (s.getBlue (),  d.getBlue ())  - d.getBlue ())  + 128) >> 8));
      }

    private:
      Copy& operator= (Copy const&);

      int const m_alpha;
    };

    //---

    struct CopyGray
    {
      void operator () (uint8* dest, uint8 const* src) const
      {
        PixelRGB* d ((PixelRGB*)dest);
        d->getRed ()   = *src;
        d->getGreen () = *src;
        d->getBlue ()  = *src;
      }
    };
    
    //---

    struct CopyARGB
    {
      explicit CopyARGB (double opacity)
        : m_alpha (int (257 * opacity + 0.5))
      {
      }
      
      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest, uint8 const* src) const noexcept
      {
        PixelRGB& d (*((PixelRGB*)dest));
        PixelARGB s (*((PixelARGB*)src));
        int const m = s.getAlpha ();

        d.getRed ()   = uint8 (d.getRed ()   + ((m * m_alpha * (mode (s.getRed (),   d.getRed ())   - d.getRed ())   + 32769) >> 16));
        d.getGreen () = uint8 (d.getGreen () + ((m * m_alpha * (mode (s.getGreen (), d.getGreen ()) - d.getGreen ()) + 32769) >> 16));
        d.getBlue ()  = uint8 (d.getBlue ()  + ((m * m_alpha * (mode (s.getBlue (),  d.getBlue ())  - d.getBlue ())  + 32769) >> 16));
      }

    private:
      CopyARGB& operator= (CopyARGB const&);

      int const m_alpha;
    };

    //---

    // premultiplied
    struct CopyARGB_Pre
    {
      explicit CopyARGB_Pre (double opacity)
        : m_alpha (int (257 * opacity + 0.5))
      {
      }
      
      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest, uint8 const* src) const noexcept
      {
        PixelRGB& d (*((PixelRGB*)dest));
        PixelARGB s (*((PixelARGB*)src));
        int const m = s.getAlpha ();

        s.unpremultiply ();
        d.getRed ()   = uint8 (d.getRed ()   + ((m * m_alpha * (mode (s.getRed (),   d.getRed ())   - d.getRed ())   + 32769) >> 16));
        d.getGreen () = uint8 (d.getGreen () + ((m * m_alpha * (mode (s.getGreen (), d.getGreen ()) - d.getGreen ()) + 32769) >> 16));
        d.getBlue ()  = uint8 (d.getBlue ()  + ((m * m_alpha * (mode (s.getBlue (),  d.getBlue ())  - d.getBlue ())  + 32769) >> 16));
      }

    private:
      CopyARGB_Pre& operator= (CopyARGB_Pre const&);

      int const m_alpha;
    };
  };

  //----------------------------------------------------------------------------

  struct ARGB
  {
    struct Unpremultiply
    {
      inline void operator () (uint8* dest) const noexcept
      {
        ((PixelARGB*)dest)->unpremultiply ();
      }
    };

    /** Blend a colour table entry into a premultiplied ARGB pixel.
    */
    struct CopyTable
    {
      explicit CopyTable (SharedTable <Colour> table)
        : m_table (table)
      {
      }

      // v = v0 + t * (v1 - v0)
      static inline int div255 (int v) noexcept
      {
        v += 128;
        return (v + (v >> 8)) >> 8;
      }

      template <class ModeType>
      inline void operator () (ModeType mode, uint8* dest, int value) const
      {
        Colour const& c = m_table [value];
        PixelARGB& d (*((PixelARGB*)dest));
        int const alpha = c.getAlpha ();
      
        d.getRed ()   += uint8 (div255 (alpha * (mode (c.getRed (),   d.getRed ())   - d.getRed ())   + 128));
        d.getGreen () += uint8 (div255 (alpha * (mode (c.getGreen (), d.getGreen ()) - d.getGreen ()) + 128));
        d.getBlue ()  += uint8 (div255 (alpha * (mode (c.getBlue (),  d.getBlue ())  - d.getBlue ())  + 128));
      }

    private:
      SharedTable <Colour> m_table;
    };
  };
}

/** Unpremultiply an ARGB image.
*/
extern void unPremultiplyImage (Image dest);

/** Fill an image with colour.
*/
extern void fillImage (Image dest,
                       Point <int> destTopLeft,
                       Image mask,
                       Rectangle <int> maskBounds,
                       BlendMode::Type mode,
                       double opacity,
                       Colour colour);

/** Copy one image over another.
*/
extern void copyImage (Image dest,
                       Point <int> destTopLeft,
                       Image source,
                       Rectangle <int> sourceBounds,
                       BlendMode::Type mode,
                       double opacity);

//------------------------------------------------------------------------------

struct PixelProcs
{
  template <class Functor>
  void copyGray (
    int rows,
    int cols,
    unsigned char const* src,
    int srcRowBytes,
    int srcColBytes,
    unsigned char* dest,
    int destRowBytes,
    int destColBytes,
    Functor blendFunc)
  {
    srcRowBytes -= cols * srcColBytes;
    destRowBytes -= cols * destColBytes;

    for (int y = rows; --y >= 0;)
    {
      for (int x = cols; --x >= 0;)
      {
        *dest = static_cast <unsigned char> (blendFunc (*src, *dest));

        src += srcColBytes;
        dest += destColBytes;
      }

      src += srcRowBytes;
      dest += destRowBytes;
    }
  }

  template <class Functor>
  void fillGray (
    int rows,
    int cols,
    unsigned char gray,
    double opacity,
    unsigned char const* mask,
    int maskRowBytes,
    int maskColBytes,
    unsigned char* dest,
    int destRowBytes,
    int destColBytes,
    Functor blendFunc)
  {
    int alpha = static_cast <int> (256 * opacity + 0.5);

    maskRowBytes -= cols * maskColBytes;
    destRowBytes -= cols * destColBytes;

    for (int y = rows; --y >= 0;)
    {
      for (int x = cols; --x >= 0;)
      {
        *dest = *dest + (alpha * (blendFunc (gray, *dest) - *dest) + 128) / 256;

        mask += maskColBytes;
        dest += destColBytes;
      }

      mask += maskRowBytes;
      dest += destRowBytes;
    }
  }

  template <class Functor>
  void fillRGB (
    int rows,
    int cols,
    unsigned char const* const rgb,
    double opacity,
    unsigned char const* mask,
    int maskRowBytes,
    int maskColBytes,
    unsigned char* dest,
    int destRowBytes,
    int destColBytes,
    Functor blendFunc)
  {
    int alpha = static_cast <int> (256 * opacity + 0.5);

    maskRowBytes -= cols * maskColBytes;
    destRowBytes -= cols * destColBytes;
    destColBytes -= 2;

    for (int y = rows; --y >= 0;)
    {
      for (int x = cols; --x >= 0;)
      {
        int t = alpha * *mask;

        *dest = static_cast <unsigned char> (*dest + (t * (blendFunc (rgb [0], *dest) - *dest) + 32768) / 65536);

        dest++;
        *dest = static_cast <unsigned char> (*dest + (t * (blendFunc (rgb [0], *dest) - *dest) + 32768) / 65536);

        dest++;
        *dest = static_cast <unsigned char> (*dest + (t * (blendFunc (rgb [0], *dest) - *dest) + 32768) / 65536);

        mask += maskColBytes;
        dest += destColBytes;
      }

      mask += maskRowBytes;
      dest += destRowBytes;
    }
  }

  void fillRGB (
    int rows,
    int cols,
    unsigned char const* const rgb,
    double opacity,
    unsigned char const* mask,
    int maskRowBytes,
    int maskColBytes,
    unsigned char* dest,
    int destRowBytes,
    int destColBytes,
    BlendMode::Type blendMode)
  {
  }
};
