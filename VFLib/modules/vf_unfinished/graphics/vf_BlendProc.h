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

#ifndef VF_BLENDPROC_VFHEADER
#define VF_BLENDPROC_VFHEADER

/** Pixel compositing functors.

    @ingroup vf_gui
*/
namespace BlendProc
{
  struct Gray
  {
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
    struct Fill
    {
      Fill (Colour const& colour, double opacity)
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
      Fill& operator= (Fill const&);

      int const m_alpha;
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

#endif
