/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

#ifndef VF_PIXELS_VFHEADER
#define VF_PIXELS_VFHEADER

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
  struct FillMaskRGB
  {
    explicit FillMaskRGB (Colour const& colour, double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
    {
      m_src[0] = colour.getBlue ();
      m_src[1] = colour.getGreen ();
      m_src[2] = colour.getRed ();
    }

    void operator () (uint8* dest, uint8 const* mask) const
    {
      dest[0] = uint8 (dest[0] + (m_mode (m_src[0], dest[0]) - dest[0]) * *mask * m_alpha / 65025);
      dest[1] = uint8 (dest[1] + (m_mode (m_src[1], dest[1]) - dest[1]) * *mask * m_alpha / 65025);
      dest[2] = uint8 (dest[2] + (m_mode (m_src[2], dest[2]) - dest[2]) * *mask * m_alpha / 65025);
    }

  private:
    FillMaskRGB <ModeType>& operator= (FillMaskRGB <ModeType> const&);

    int const m_alpha;
    ModeType const m_mode;
    uint8 m_src [3];
  };

  //------------------------------------------------------------------------------

  /** Blend two grayscale pixels.
  */
  template <class ModeType>
  struct BlendGray
  {
    explicit BlendGray (double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
    {
    }

    void operator () (uint8* dest, uint8 const* src) const
    {
      dest[0] = uint8 (dest[0] + ((m_mode (src[0], dest[0]) - dest[0]) * m_alpha + 128) / 255);
    }

  private:
    BlendGray <ModeType>& operator= (BlendGray <ModeType> const&);

    int const m_alpha;
    ModeType const m_mode;
  };

  //------------------------------------------------------------------------------

  /** Blend two RGB pixels.
  */
  template <class ModeType>
  struct BlendRGB
  {
    explicit BlendRGB (double opacity, ModeType mode = ModeType ())
      : m_alpha (int (255 * opacity + 0.5))
      , m_mode (mode)
    {
    }

    void operator () (uint8* dest, uint8 const* src) const
    {
      uint8 result[3];

      result[0] = uint8 (m_mode (src[0], dest[0]));
      result[1] = uint8 (m_mode (src[1], dest[1]));
      result[2] = uint8 (m_mode (src[2], dest[2]));

      ((PixelRGB*)dest)->blend (*((PixelRGB*)result), m_alpha);
    }

  private:
    BlendRGB <ModeType>& operator= (BlendRGB <ModeType> const&);

    ModeType const m_mode;
    int const m_alpha;
  };

  /** Blend two RGB pixels using normal mode.

      This is an optimized specialization.
  */
  template <>
  struct BlendRGB <Mode::normal>
  {
    explicit BlendRGB (double opacity)
      : m_alpha (int (255 * opacity + 0.5))
    {
    }

    void operator () (uint8* dest, uint8 const* src) const
    {
      ((PixelRGB*)dest)->blend (*((PixelRGB*)src), m_alpha);
    }

  private:
    BlendRGB <Mode::normal> & operator= (BlendRGB <Mode::normal> const&);

    int const m_alpha;
  };
  
  //------------------------------------------------------------------------------

  /** Blend a premultiplied ARGB pixel onto an RGB pixel.
  */
  template <class ModeType>
  struct BlendARGB
  {
    explicit BlendARGB (double opacity, ModeType mode = ModeType ())
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
      int const mask = src[3];
      dest[0] = uint8 (dest[0] + (m_mode (unpremultiply (src[0], mask), dest[0]) - dest[0]) * mask * m_alpha / 65025);
      dest[1] = uint8 (dest[1] + (m_mode (unpremultiply (src[1], mask), dest[1]) - dest[1]) * mask * m_alpha / 65025);
      dest[2] = uint8 (dest[2] + (m_mode (unpremultiply (src[2], mask), dest[2]) - dest[2]) * mask * m_alpha / 65025);
    }

  private:
    BlendARGB <ModeType> & operator= (BlendARGB <ModeType> const&);

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

#endif
