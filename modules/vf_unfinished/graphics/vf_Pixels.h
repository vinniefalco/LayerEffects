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

#ifndef VF_PIXELS_VFHEADER
#define VF_PIXELS_VFHEADER

enum BlendMode
{
  normal = 1,
  lighten,
  darken,
  multiply,
  average,
  add,
  subtract,
  difference,
  negation,
  screen,
  exclusion,
  overlay,
  softLight,
  hardLight,
  colorDodge,
  colorBurn,
  linearDodge,
  linearBurn,
  linearLight,
  vividLight,
  pinLight,
  hardMix,
  reflect,
  glow,
  phoenix,
};

/** Fill an image with colour.
*/
extern void fillImage (Image dest,
                       Point <int> destTopLeft,
                       Image mask,
                       Rectangle <int> maskBounds,
                       BlendMode mode,
                       double opacity,
                       Colour colour);

extern void copyImage (Image dest,
                       Point <int> destTopLeft,
                       Image source,
                       Rectangle <int> sourceBounds,
                       BlendMode mode,
                       double opacity);

/** Wrapper for @ref BitmapData.

    This wrapper facilitates operations on one or more images.

    @ingroup vf_gui
*/
class Pixels : public Image::BitmapData
{
public:
  /** Blending modes.

      These are suitable for use with the pixel operations.
      These replicate the Photoshop layer blending modes.

      See: http://inlandstudios.com/en/?p=851

      @ingroup vf_gui
  */

  struct Mode
  {
    // f = front, b = back

    struct normal
    {
      inline int operator () (int f, int) const
      {
        return f;
      }
    };

    struct lighten
    {
      inline int operator () (int f, int b) const
      {
        return (f > b) ? f : b;
      }
    };

    struct darken
    {
      inline int operator () (int f, int b) const
      {
        return (f < b) ? f : b;
      }
    };

    struct multiply
    {
      inline int operator () (int f, int b) const
      {
        return f * b / 255;
      }
    };

    struct average
    {
      inline int operator () (int f, int b) const
      {
        return (f + b) / 2;
      }
    };

    struct add
    {
      inline int operator () (int f, int b) const
      {
        return std::min (255, f + b);
      }
    };

    struct subtract
    {
      inline int operator () (int f, int b) const
      {
        return (f > b) ? 0 : (b - f);
      }
    };

    struct difference
    {
      inline int operator () (int f, int b) const
      {
        return std::abs (f - b);
      }
    };

    struct negation
    {
      inline int operator () (int f, int b) const
      {
        return 255 - std::abs (255 - f - b);
      }
    };

    struct screen
    {
      inline int operator () (int f, int b) const
      {
        return 255 - (((255 - f) * (255 - b)) / 255);
      }
    };

    struct exclusion
    {
      inline int operator () (int f, int b) const
      {
        return (f + b - 2 * f * b / 255);
      }
    };

    struct overlay
    {
      inline int operator () (int f, int b) const
      {
        return (b < 128) ? (2 * f * b / 255) : (255 - 2 * (255 - f) * (255 - b) / 255);
      }
    };

    struct softLight
    {
      inline int operator () (int f, int b) const
      {
        return int ((b < 128) ?
          (2 * ((f >> 1) + 64)) * ((float)b / 255) :
          (255 - (2 * (255 - ((f >> 1) + 64)) * (float)(255 - b) / 255)));
      }
    };

    struct hardLight
    {
      inline int operator () (int f, int b) const
      {
        return overlay () (f, b);
      }
    };

    struct colorDodge
    {
      inline int operator () (int f, int b) const
      {
        return (f == 255) ? f : std::min (255, (b << 8) / (255 - f));
      }
    };

    struct colorBurn
    {
      inline int operator () (int f, int b) const
      {
        return (b == 0) ? 0 : std::max (0, (255 - ((255 - f) << 8) / b));
      }
    };

    struct linearDodge
    {
      inline int operator () (int f, int b) const
      {
        return add () (f, b);
      }
    };

    struct linearBurn
    {
      inline int operator () (int f, int b) const
      {
        return subtract () (f, b);
      }
    };

    struct linearLight
    {
      inline int operator () (int f, int b) const
      {
         return (f < 128) ?
           linearBurn () (256 - b, 2 * f) :
           linearDodge () (b, 2 * (f - 128));
      }
    };

    struct vividLight
    {
      inline int operator () (int f, int b) const
      {
        return (b < 128) ?
          colorBurn () (f, 2 * b) :
          colorDodge () (f, 2 * (b - 128));
      }
    };

    struct pinLight
    {
      inline int operator () (int f, int b) const
      {
        return (f < 128) ?
          darken () (b, 2 * f) :
          lighten () (b, 2 * (f - 128));
      }
    };

    struct hardMix
    {
      inline int operator () (int f, int b) const
      {
        return (vividLight () (f, b) < 128) ? 0 : 255;
      }
    };

    struct reflect
    {
      inline int operator () (int f, int b) const
      {
        return (b == 255) ? 255 : std::min (255, f * f / (255 - b));
      }
    };

    struct glow
    {
      inline int operator () (int f, int b) const
      {
        return reflect () (b, f);
      }
    };

    struct phoenix
    {
      inline int operator () (int f, int b) const
      {
        return std::min (f, b) - std::max (f, b) + 255;
      }
    };
  };

  //=============================================================================

  /** Pixel operations

      These are suitable for use with iterate ()
  */

  /** Blend a colour into RGB using a mask.
  */
  template <class ModeType>
  struct FillRGB_Mask
  {
    explicit FillRGB_Mask (Colour const& colour, ModeType mode = ModeType ())
      : m_mode (mode)
      , m_src (colour.getARGB ())
    {
    }

    void operator () (uint8* dest, uint8 const* mask) const
    {
      int const m = *mask;
      PixelRGB& d (*((PixelRGB*)dest));
      PixelRGB s;

      s.getRed ()   = m_mode (m_src.getRed   (), d.getRed ());
      s.getGreen () = m_mode (m_src.getGreen (), d.getGreen ());
      s.getBlue ()  = m_mode (m_src.getBlue  (), d.getBlue ());

      d.blend (s, *mask);
    }

  private:
    FillRGB_Mask <ModeType>& operator= (FillRGB_Mask <ModeType> const&);

    ModeType const m_mode;
    PixelRGB const m_src;
  };

  //------------------------------------------------------------------------------

  /** Blend a colour into RGB using a mask and specified opacity.
  */
  template <class ModeType>
  struct FillRGB_MaskOpacity
  {
    explicit FillRGB_MaskOpacity (Colour const& colour, double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
      , m_src (colour.getARGB ())
    {
    }

    void operator () (uint8* dest, uint8 const* mask) const
    {
      int const m = *mask;
      PixelRGB& d (*((PixelRGB*)dest));

      d.getRed ()   = uint8 (d.getRed ()    + (m_mode (m_src.getRed (),   d.getRed ()) -   d.getRed ())    * m * m_alpha / 65025);
      d.getGreen () = uint8 (d.getGreen ()  + (m_mode (m_src.getGreen (), d.getGreen ()) - d.getGreen ())  * m * m_alpha / 65025);
      d.getBlue ()  = uint8 (d.getBlue ()   + (m_mode (m_src.getBlue (),  d.getBlue ()) -  d.getBlue ())   * m * m_alpha / 65025);
    }

  private:
    FillRGB_MaskOpacity <ModeType>& operator= (FillRGB_MaskOpacity <ModeType> const&);

    int const m_alpha;
    ModeType const m_mode;
    PixelRGB const m_src;
  };

  //------------------------------------------------------------------------------

  /** Blend two grayscale pixels.
  */
  template <class ModeType>
  struct BlendGray_Opacity
  {
    explicit BlendGray_Opacity (double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
    {
    }

    void operator () (uint8* dest, uint8 const* src) const
    {
      dest[0] = uint8 (dest[0] + ((m_mode (src[0], dest[0]) - dest[0]) * m_alpha + 128) / 255);
    }

  private:
    BlendGray_Opacity <ModeType>& operator= (BlendGray_Opacity <ModeType> const&);

    int const m_alpha;
    ModeType const m_mode;
  };

  //------------------------------------------------------------------------------

  /** Blend two RGB pixels.
  */
  template <class ModeType>
  struct BlendRGB_Opacity
  {
    explicit BlendRGB_Opacity (double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
    {
    }

    void operator () (uint8* dest, uint8 const* src) const
    {
      PixelRGB v;
      PixelRGB& d (*((PixelRGB*)dest));
      PixelRGB const& s (*((PixelRGB const*)src));

      v.getRed ()   = uint8 (m_mode (s.getRed (),   d.getRed ()));
      v.getGreen () = uint8 (m_mode (s.getGreen (), d.getGreen ()));
      v.getBlue ()  = uint8 (m_mode (s.getBlue (),  d.getBlue ()));

      d.blend (v, m_alpha);
    }

  private:
    BlendRGB_Opacity <ModeType>& operator= (BlendRGB_Opacity <ModeType> const&);

    ModeType const m_mode;
    int const m_alpha;
  };

 //------------------------------------------------------------------------------

  /** Blend a premultiplied ARGB pixel onto an RGB pixel.
  */
  template <class ModeType>
  struct BlendARGB_Opacity
  {
    explicit BlendARGB_Opacity (double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
    {
    }

    static inline int unpremultiply (int value, int alpha)
    {
      return alpha ? value * 255 / alpha : 0;
    }

    void operator () (uint8* dest, uint8 const* src) const
    {
      PixelARGB s (((PixelARGB const*)src)->getUnpremultipliedARGB ());
      PixelRGB& d (*((PixelRGB*)dest));
      int const mask = s.getAlpha ();

      d.getRed ()   = uint8 (d.getRed ()    + (m_mode (s.getRed (),   d.getRed ()) -   d.getRed ())    * mask * m_alpha / 65025);
      d.getGreen () = uint8 (d.getGreen ()  + (m_mode (s.getGreen (), d.getGreen ()) - d.getGreen ())  * mask * m_alpha / 65025);
      d.getBlue ()  = uint8 (d.getBlue ()   + (m_mode (s.getBlue (),  d.getBlue ()) -  d.getBlue ())   * mask * m_alpha / 65025);
    }

  private:
    BlendARGB_Opacity <ModeType> & operator= (BlendARGB_Opacity <ModeType> const&);

    int const m_alpha;
    ModeType const m_mode;
  };

public:
  //=============================================================================

  /** Construct from an image.

      The pixels will refer to the specified subset of the image.

      @param image  The image to get pixels from.
      @param bounds The area of interest.
      @param access The type of access desired.
  */
  Pixels (Image image,
          Rectangle <int> const& bounds,
          Image::BitmapData::ReadWriteMode access = Image::BitmapData::readWrite)
    : BitmapData (image,
                  bounds.getX (), bounds.getY (),
                  bounds.getWidth (), bounds.getHeight (),
                  access)
  {
    jassert (image.getBounds ().contains (bounds));
  }

  //-----------------------------------------------------------------------------

  /** Perform an operation on each pixel.

      The functor is applied to every pixel in the image.

      @param op A functor with signature `void (uint8* dest)`
  */
  template <class Operation>
  void iterate (Operation op)
  {
    int const     rows        = height;
    int const     cols        = width;
    uint8*        dest        = getLinePointer (0);
    int const     destColSkip = pixelStride;
    int const     destRowSkip = lineStride - cols * destColSkip;

    for (int y = rows; y--;)
    {
      for (int x = cols; x--;)
      {
        op (dest);

        dest = addBytesToPointer (dest, destColSkip);
      }

      dest = addBytesToPointer (dest, destRowSkip);
    }
  }

  //-----------------------------------------------------------------------------

  /** Perform an operation on each pixel.

      The functor is applied to every pixel in the image. The
      source pixel image is walked at the same time and passed to the functor.

      @param op A functor with signature `void (uint8* dest, uint8 const* src)`
  */
  template <class Operation>
  void iterate (Pixels const& srcPixels, Operation op)
  {
    int const     rows        = height;
    int const     cols        = width;
    uint8*        dest        = getLinePointer (0);
    int const     destColSkip = pixelStride;
    int const     destRowSkip = lineStride - cols * destColSkip;
    uint8 const*  src         = srcPixels.getLinePointer (0);
    int const     srcColSkip  = srcPixels.pixelStride;
    int const     srcRowSkip  = srcPixels.lineStride - cols * srcColSkip;

    for (int y = rows; y--;)
    {
      for (int x = cols; x--;)
      {
        op (dest, src);

        src  = addBytesToPointer (src, srcColSkip);
        dest = addBytesToPointer (dest, destColSkip);
      }

      src  = addBytesToPointer (src, srcRowSkip);
      dest = addBytesToPointer (dest, destRowSkip);
    }
  }
};

/** Blend two RGB pixels using normal mode.

    This is an optimized specialization.
*/
template <>
struct Pixels::BlendRGB_Opacity <Pixels::Mode::normal>
{
  explicit BlendRGB_Opacity (double opacity)
    : m_alpha (int (255 * opacity + 0.5))
  {
  }

  void operator () (uint8* dest, uint8 const* src) const
  {
    PixelRGB& d (*((PixelRGB*)dest));
    PixelRGB const& s (*((PixelRGB const*)src));

    d.blend (s, m_alpha);
  }

private:
  BlendRGB_Opacity <Pixels::Mode::normal> & operator= (BlendRGB_Opacity <Pixels::Mode::normal> const&);

  int const m_alpha;
};

 
/** Process an image.

    This wrapper is provided for convenience.

    @ingroup vf_gui
*/
template <class Operation>
void processImage (Image dest,
                   Point <int> destTopLeft,
                   Image source,
                   Rectangle <int> sourceBounds,
                   Operation op)
{
  jassert (source.getBounds ().contains (sourceBounds));

  Rectangle <int> const bounds = sourceBounds.getIntersection (
    dest.getBounds () + destTopLeft);

  Pixels destPixels (dest, bounds);
  Pixels sourcePixels (source, bounds);

  destPixels.iterate (sourcePixels, op);
}

/** Generic blend mode application.
*/
#if 0
template <class Functor>
void applyBlendMode (BlendMode mode, Functor functor = Functor ())
{
  switch (mode)
  {
  case normal:      destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::normal> (colour, opacity)); break;
  case lighten:     destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::lighten> (colour, opacity)); break;
  case darken:      destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::darken> (colour, opacity)); break;
  case multiply:    destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::multiply> (colour, opacity)); break;
  case average:     destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::average> (colour, opacity)); break;
  case add:         destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::add> (colour, opacity)); break;
  case subtract:    destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::subtract> (colour, opacity)); break;
  case difference:  destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::difference> (colour, opacity)); break;
  case negation:    destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::negation> (colour, opacity)); break;
  case screen:      destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::screen> (colour, opacity)); break;
  case exclusion:   destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::exclusion> (colour, opacity)); break;
  case overlay:     destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::overlay> (colour, opacity)); break;
  case softLight:   destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::softLight> (colour, opacity)); break;
  case hardLight:   destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::hardLight> (colour, opacity)); break;
  case colorDodge:  destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::colorDodge> (colour, opacity)); break;
  case colorBurn:   destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::colorBurn> (colour, opacity)); break;
  case linearDodge: destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::linearDodge> (colour, opacity)); break;
  case linearBurn:  destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::linearBurn> (colour, opacity)); break;
  case linearLight: destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::linearLight> (colour, opacity)); break;
  case vividLight:  destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::vividLight> (colour, opacity)); break;
  case pinLight:    destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::pinLight> (colour, opacity)); break;
  case hardMix:     destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::hardMix> (colour, opacity)); break;
  case reflect:     destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::reflect> (colour, opacity)); break;
  case glow:        destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::glow> (colour, opacity)); break;
  case phoenix:     destPixels.iterate (maskPixels, Pixels::FillRGB_MaskOpacity <Pixels::Mode::phoenix> (colour, opacity)); break;
  default:
    jassertfalse;
  };
  break;
}
#endif

#endif
