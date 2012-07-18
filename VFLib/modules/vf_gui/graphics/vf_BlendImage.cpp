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

/** Image composition functions.

    These replicate the Photoshop layer blending modes.

    See: http://inlandstudios.com/en/?p=851

    @ingroup vf_gui
*/
struct BlendOperator
{
  // f = front, b = back

  static inline int normal (int f, int)
  {
    return f;
  }

  static inline int lighten (int f, int b)
  {
    return (f > b) ? f : b;
  }

  static inline int darken (int f, int b)
  {
    return (f < b) ? f : b;
  }

  static inline int multiply (int f, int b)
  {
    return f * b / 255;
  }

  static inline int average (int f, int b)
  {
    return (f + b) / 2;
  }

  static inline int add (int f, int b)
  {
    return std::min (255, f + b);
  }

  static inline int subtract (int f, int b)
  {
    return (f > b) ? 0 : (b - f);
  }

  static inline int difference (int f, int b)
  {
    return std::abs (f - b);
  }

  static inline int negation (int f, int b)
  {
    return 255 - std::abs (255 - f - b);
  }

  static inline int screen (int f, int b)
  {
    return 255 - (((255 - f) * (255 - b)) / 255);
  }

  static inline int exclusion (int f, int b)
  {
    return (f + b - 2 * f * b / 255);
  }

  static inline int overlay (int f, int b)
  {
    return (b < 128) ? (2 * f * b / 255) : (255 - 2 * (255 - f) * (255 - b) / 255);
  }

  static inline int softLight (int f, int b)
  {
    return int ((b < 128) ? (2 * ((f >> 1) + 64)) * ((float)b / 255)
                          : (255 - (2 * (255 - ((f >> 1) + 64)) * (float)(255 - b) / 255)));
  }

  static inline int hardLight (int f, int b)
  {
    return overlay (b, f);
  }

  static inline int colorDodge (int f, int b)
  {
    return (f == 255) ? f : std::min (255, (b << 8) / (255 - f));
  }

  static inline int colorBurn (int f, int b)
  {
    return (b == 0) ? 0 : std::max (0, (255 - ((255 - f) << 8) / b));
  }

  static inline int linearDodge (int f, int b)
  {
    return add (f, b);
  }

  static inline int linearBurn (int f, int b)
  {
    return subtract (f, b);
  }

  static inline int linearLight (int f, int b)
  {
    return (f < 128) ? linearBurn (256 - b, 2 * f)
                     : linearDodge (b, 2 * (f - 128));
  }

  static inline int vividLight (int f, int b)
  {
    return (b < 128) ? colorBurn (f, 2 * b)
                     : colorDodge (f, 2 * (b - 128));
  }

  static inline int pinLight (int f, int b)
  {
    return (f < 128) ? darken (b, 2 * f)
                     : lighten (b, 2 * (f - 128));
  }

  static inline int hardMix (int f, int b)
  {
    return (vividLight (f, b) < 128) ? 0 : 255;
  }

  static inline int reflect (int f, int b)
  {
    return (b == 255) ? 255 : std::min (255, f * f / (255 - b));
  }

  static inline int glow (int f, int b)
  {
    return reflect (b, f);
  }

  static inline int phoenix (int f, int b)
  {
    return std::min (f, b) - std::max (f, b) + 255;
  }
};

//------------------------------------------------------------------------------

struct BlendOperands
{
  int            rows;
  int            cols;

  uint8*         dest;
  int            destRowBytes;
  int            destColBytes;

  uint8*         destAlpha;
  int            destAlphaRowBytes;
  int            destAlphaColBytes;

  uint8 const*   src;
  int            srcRowBytes;
  int            srcColBytes;

  uint8 const*   srcAlpha;
  int            srcAlphaRowBytes;
  int            srcAlphaColBytes;

  double         opacity;

  //----------------------------------------------------------------------------

  template <class Operator>
  void blend0 (Operator const& op)
  {
    uint8 const alpha = static_cast <uint8> (jlimit (0, 255,
      static_cast <int> (255 * opacity + 0.5)));

    destRowBytes     -= cols * destColBytes;
    srcRowBytes      -= cols * srcColBytes;

    while (rows--)
    {
      for (int x = cols; x--;)
      {
        int const f = *src;
        int const b = *dest;
        int const v = op (f, b);

        *dest = static_cast <uint8> (b + (alpha * (v - b)) / 255);

        dest     += destColBytes;
        src      += srcColBytes;
      }

      dest     += destRowBytes;
      src      += srcRowBytes;
    }
  }

  //----------------------------------------------------------------------------

  template <class Operator>
  void blend1 (Operator const& op)
  {
    uint8 const alpha = static_cast <uint8> (jlimit (0, 255,
      static_cast <int> (255 * opacity + 0.5)));

    destRowBytes     -= cols * destColBytes;
    srcRowBytes      -= cols * srcColBytes;
    srcAlphaRowBytes -= cols * srcAlphaColBytes;

    while (rows--)
    {
      for (int x = cols; x--;)
      {
        int const fa = *srcAlpha;
        int const f  = fa ? jmin (255, (*src * 255) / fa) : 0;
        int const b  = *dest;
        int const v  = (op (f, b) * fa * alpha) / 65025;

        *dest = static_cast <uint8> (((v + b) * 65025 - fa * alpha * b) / 65025);

        dest     += destColBytes;
        src      += srcColBytes;
        srcAlpha += srcAlphaColBytes;
      }

      dest     += destRowBytes;
      src      += srcRowBytes;
      srcAlpha += srcAlphaRowBytes;
    }
  }

  //----------------------------------------------------------------------------

  template <class Operator>
  void blend2 (Operator const& op)
  {
    uint8 const alpha = static_cast <uint8> (jlimit (0, 255,
      static_cast <int> (255 * opacity + 0.5)));

    destRowBytes      -= cols * destColBytes;
    destAlphaRowBytes -= cols * destAlphaColBytes;
    srcRowBytes       -= cols * srcColBytes;
    srcAlphaRowBytes  -= cols * srcAlphaColBytes;

    while (rows--)
    {
      for (int x = cols; x--;)
      {
        int const fa = *srcAlpha;
        int const f  = fa ? jmin (255, (*src * 255) / fa) : 0;
        int const ba = *destAlpha;
        int const b  = ba ? jmin (255, (*dest * 255) / ba) : 0;
        int const v  = (op (f, b) * fa * alpha) / 65025;

        *dest = static_cast <uint8> (((v + *dest) * 65025 - ba * alpha * *dest) / 65025);

        dest      += destColBytes;
        destAlpha += destAlphaColBytes;
        src       += srcColBytes;
        srcAlpha  += srcAlphaColBytes;
      }

      dest      += destRowBytes;
      destAlpha += destAlphaRowBytes;
      src       += srcRowBytes;
      srcAlpha  += srcAlphaRowBytes;
    }
  }

  //----------------------------------------------------------------------------

  void blendmask ()
  {
    destRowBytes     -= cols * destColBytes;
    srcRowBytes      -= cols * srcColBytes;

    while (rows--)
    {
      for (int x = cols; x--;)
      {
        int f = *src;
        int b = *dest;
        
        *dest = static_cast <uint8> (((f + b) * 255 - (f * b)) / 255);

        dest     += destColBytes;
        src      += srcColBytes;
      }

      dest     += destRowBytes;
      src      += srcRowBytes;
    }
  }
};

//------------------------------------------------------------------------------

void BlendImage (
  Image destImage,
  Point <int> destTopLeft,
  Image srcImage,
  Rectangle <int> srcBounds,
  BlendMode blendMode,
  double opacity)
{
  jassert (srcImage.getBounds ().contains (srcBounds));

  if (destTopLeft.getX () < 0 )
  {
    srcBounds.setLeft (srcBounds.getX () - destTopLeft.getX ());
    destTopLeft.setX (0);
  }

  if (destTopLeft.getY () < 0 )
  {
    srcBounds.setTop (srcBounds.getY () - destTopLeft.getY ());
    destTopLeft.setY (0);
  }

  Rectangle <int> bounds = srcBounds.getIntersection (Rectangle <int> (
    destTopLeft.getX (),
    destTopLeft.getY (),
    destImage.getWidth () - destTopLeft.getX (),
    destImage.getHeight () - destTopLeft.getY ()));

  if (!bounds.isEmpty ())
  {
    Image::BitmapData src (
      srcImage,
      srcBounds.getX (),
      srcBounds.getY (),
      srcBounds.getWidth (),
      srcBounds.getHeight (),
      Image::BitmapData::readOnly);

    Image::BitmapData dest (
      destImage,
      destTopLeft.getX (),
      destTopLeft.getY (),
      bounds.getWidth (),
      bounds.getHeight (),
      Image::BitmapData::readWrite);

    switch (srcImage.getFormat ())
    {
    case Image::ARGB:
      switch (destImage.getFormat ())
      {
      case Image::RGB:
        for (int i = 0; i < 3; ++i)
        {
          BlendOperands ops;
          
          ops.rows = dest.height;
          ops.cols = dest.width;
          
          ops.dest = dest.getLinePointer (0) + i;
          ops.destRowBytes = dest.lineStride;
          ops.destColBytes = dest.pixelStride;
          
          ops.src = src.getLinePointer (0) + i;
          ops.srcRowBytes = src.lineStride;
          ops.srcColBytes = src.pixelStride;

          ops.srcAlpha = src.getLinePointer (0) + 3;
          ops.srcAlphaRowBytes = src.lineStride;
          ops.srcAlphaColBytes = src.pixelStride;

          ops.opacity = opacity;

          switch (blendMode)
          {
            default:
              jassertfalse;

            case normal:      ops.blend1 (&BlendOperator::normal); break;
            case lighten:     ops.blend1 (&BlendOperator::lighten); break;
            case darken:      ops.blend1 (&BlendOperator::darken); break;
            case multiply:    ops.blend1 (&BlendOperator::multiply); break;
            case average:     ops.blend1 (&BlendOperator::average); break;
            case add:         ops.blend1 (&BlendOperator::add); break;
            case subtract:    ops.blend1 (&BlendOperator::subtract); break;
            case difference:  ops.blend1 (&BlendOperator::difference); break;
            case negation:    ops.blend1 (&BlendOperator::negation); break;
            case screen:      ops.blend1 (&BlendOperator::screen); break;
            case exclusion:   ops.blend1 (&BlendOperator::exclusion); break;
            case overlay:     ops.blend1 (&BlendOperator::overlay); break;
            case softLight:   ops.blend1 (&BlendOperator::softLight); break;
            case hardLight:   ops.blend1 (&BlendOperator::hardLight); break;
            case colorDodge:  ops.blend1 (&BlendOperator::colorDodge); break;
            case colorBurn:   ops.blend1 (&BlendOperator::colorBurn); break;
            case linearDodge: ops.blend1 (&BlendOperator::linearDodge); break;
            case linearBurn:  ops.blend1 (&BlendOperator::linearBurn); break;
            case linearLight: ops.blend1 (&BlendOperator::linearLight); break;
            case vividLight:  ops.blend1 (&BlendOperator::vividLight); break;
            case pinLight:    ops.blend1 (&BlendOperator::pinLight); break;
            case hardMix:     ops.blend1 (&BlendOperator::hardMix); break;
            case reflect:     ops.blend1 (&BlendOperator::reflect); break;
            case glow:        ops.blend1 (&BlendOperator::glow); break;
            case phoenix:     ops.blend1 (&BlendOperator::phoenix); break;
          }
        }
        break;

      case Image::ARGB:
        for (int i = 0; i < 3; ++i)
        {
          BlendOperands ops;
          
          ops.rows = dest.height;
          ops.cols = dest.width;
          
          ops.dest = dest.getLinePointer (0) + i;
          ops.destRowBytes = dest.lineStride;
          ops.destColBytes = dest.pixelStride;

          ops.destAlpha = dest.getLinePointer (0) + 3;
          ops.destAlphaRowBytes = dest.lineStride;
          ops.destAlphaColBytes = dest.pixelStride;

          ops.src = src.getLinePointer (0) + i;
          ops.srcRowBytes = src.lineStride;
          ops.srcColBytes = src.pixelStride;

          ops.srcAlpha = src.getLinePointer (0) + 3;
          ops.srcAlphaRowBytes = src.lineStride;
          ops.srcAlphaColBytes = src.pixelStride;

          ops.opacity = opacity;

          switch (blendMode)
          {
            default:
              jassertfalse;

            case normal:      ops.blend2 (&BlendOperator::normal); break;
            case lighten:     ops.blend2 (&BlendOperator::lighten); break;
            case darken:      ops.blend2 (&BlendOperator::darken); break;
            case multiply:    ops.blend2 (&BlendOperator::multiply); break;
            case average:     ops.blend2 (&BlendOperator::average); break;
            case add:         ops.blend2 (&BlendOperator::add); break;
            case subtract:    ops.blend2 (&BlendOperator::subtract); break;
            case difference:  ops.blend2 (&BlendOperator::difference); break;
            case negation:    ops.blend2 (&BlendOperator::negation); break;
            case screen:      ops.blend2 (&BlendOperator::screen); break;
            case exclusion:   ops.blend2 (&BlendOperator::exclusion); break;
            case overlay:     ops.blend2 (&BlendOperator::overlay); break;
            case softLight:   ops.blend2 (&BlendOperator::softLight); break;
            case hardLight:   ops.blend2 (&BlendOperator::hardLight); break;
            case colorDodge:  ops.blend2 (&BlendOperator::colorDodge); break;
            case colorBurn:   ops.blend2 (&BlendOperator::colorBurn); break;
            case linearDodge: ops.blend2 (&BlendOperator::linearDodge); break;
            case linearBurn:  ops.blend2 (&BlendOperator::linearBurn); break;
            case linearLight: ops.blend2 (&BlendOperator::linearLight); break;
            case vividLight:  ops.blend2 (&BlendOperator::vividLight); break;
            case pinLight:    ops.blend2 (&BlendOperator::pinLight); break;
            case hardMix:     ops.blend2 (&BlendOperator::hardMix); break;
            case reflect:     ops.blend2 (&BlendOperator::reflect); break;
            case glow:        ops.blend2 (&BlendOperator::glow); break;
            case phoenix:     ops.blend2 (&BlendOperator::phoenix); break;
          }
        }

        // combine alpha masks

        BlendOperands ops;
          
        ops.rows = dest.height;
        ops.cols = dest.width;
          
        ops.dest = dest.getLinePointer (0) + 3;
        ops.destRowBytes = dest.lineStride;
        ops.destColBytes = dest.pixelStride;

        ops.src = src.getLinePointer (0) + 3;
        ops.srcRowBytes = src.lineStride;
        ops.srcColBytes = src.pixelStride;

        ops.blendmask ();
        break;

      case Image::SingleChannel:
      case Image::UnknownFormat:
      default:
        jassertfalse;
      }
      break;

    case Image::SingleChannel:
      switch (destImage.getFormat ())
      {
      case Image::SingleChannel:
        {
          BlendOperands ops;
          
          ops.rows = dest.height;
          ops.cols = dest.width;
          
          ops.dest = dest.getLinePointer (0);
          ops.destRowBytes = dest.lineStride;
          ops.destColBytes = dest.pixelStride;
          
          ops.src = src.getLinePointer (0);
          ops.srcRowBytes = src.lineStride;
          ops.srcColBytes = src.pixelStride;

          ops.opacity = opacity;

          switch (blendMode)
          {
            default:
              jassertfalse;

            case normal:      ops.blend0 (&BlendOperator::normal); break;
            case lighten:     ops.blend0 (&BlendOperator::lighten); break;
            case darken:      ops.blend0 (&BlendOperator::darken); break;
            case multiply:    ops.blend0 (&BlendOperator::multiply); break;
            case average:     ops.blend0 (&BlendOperator::average); break;
            case add:         ops.blend0 (&BlendOperator::add); break;
            case subtract:    ops.blend0 (&BlendOperator::subtract); break;
            case difference:  ops.blend0 (&BlendOperator::difference); break;
            case negation:    ops.blend0 (&BlendOperator::negation); break;
            case screen:      ops.blend0 (&BlendOperator::screen); break;
            case exclusion:   ops.blend0 (&BlendOperator::exclusion); break;
            case overlay:     ops.blend0 (&BlendOperator::overlay); break;
            case softLight:   ops.blend0 (&BlendOperator::softLight); break;
            case hardLight:   ops.blend0 (&BlendOperator::hardLight); break;
            case colorDodge:  ops.blend0 (&BlendOperator::colorDodge); break;
            case colorBurn:   ops.blend0 (&BlendOperator::colorBurn); break;
            case linearDodge: ops.blend0 (&BlendOperator::linearDodge); break;
            case linearBurn:  ops.blend0 (&BlendOperator::linearBurn); break;
            case linearLight: ops.blend0 (&BlendOperator::linearLight); break;
            case vividLight:  ops.blend0 (&BlendOperator::vividLight); break;
            case pinLight:    ops.blend0 (&BlendOperator::pinLight); break;
            case hardMix:     ops.blend0 (&BlendOperator::hardMix); break;
            case reflect:     ops.blend0 (&BlendOperator::reflect); break;
            case glow:        ops.blend0 (&BlendOperator::glow); break;
            case phoenix:     ops.blend0 (&BlendOperator::phoenix); break;
          }
        }
        break;

      case Image::RGB:
      case Image::ARGB:
      case Image::UnknownFormat:
        jassertfalse;
        break;
      }
      break;

    case Image::RGB:
    case Image::UnknownFormat:
    default:
      jassertfalse;
      break;
    }
  }
}
