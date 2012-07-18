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
    return 255 - (((255 - f) * (255 - b)) >> 8);
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

/** Blend a color plane.
*/
template <class BlendOp>
void blendChannel (int            rows,
                   int            cols,
                   uint8*         dest,
                   int            destRowBytes,
                   int            destColBytes,
                   uint8 const*   src,
                   int            srcRowBytes,
                   int            srcColBytes,
                   uint8 const*   mask,
                   int            maskRowBytes,
                   int            maskColBytes,
                   BlendOp const& blendOp)
{
  srcRowBytes  -= cols * srcColBytes;
  maskRowBytes -= cols * maskColBytes;
  destRowBytes -= cols * destColBytes;

  while (rows--)
  {
    for (int x = cols; x--;)
    {
      int const result = static_cast <uint8> (blendOp (*src, *dest));

      // v = v0 + (v1 - v0) * t
      *dest = static_cast <uint8> (*dest + ((result - *dest) * *mask) / 255);

      src  += srcColBytes;
      mask += maskColBytes;
      dest += destColBytes;
    }

    src  += srcRowBytes;
    mask += maskRowBytes;
    dest += destRowBytes;
  }
}

//------------------------------------------------------------------------------

void BlendImage (
  Image destImage,
  Point <int> const& destTopLeft,
  Image srcImage,
  Rectangle <int> const& srcBounds,
  BlendMode blendMode,
  float opacity)
{
  jassert (srcImage.getBounds ().contains (srcBounds));

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
          switch (blendMode)
          {
            default:
              jassertfalse
            case normal:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::normal); break;
            
            case lighten:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::lighten); break;
            
            case darken:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::darken); break;
            
            case multiply:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::multiply); break;
            
            case average:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::average); break;
            
            case add:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::add); break;
            
            case subtract:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::subtract); break;
            
            case difference:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::difference); break;
            
            case negation:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::negation); break;
            
            case screen:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::screen); break;
            
            case exclusion:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::exclusion); break;
            
            case overlay:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::overlay); break;
            
            case softLight:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::softLight); break;
            
            case hardLight:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::hardLight); break;
            
            case colorDodge:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::colorDodge); break;
            
            case colorBurn:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::colorBurn); break;
            
            case linearDodge:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::linearDodge); break;
            
            case linearBurn:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::linearBurn); break;
            
            case linearLight:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::linearLight); break;
            
            case vividLight:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::vividLight); break;
            
            case pinLight:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::pinLight); break;
            
            case hardMix:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::hardMix); break;
            
            case reflect:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::reflect); break;
            
            case glow:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::glow); break;
            
            case phoenix:
              blendChannel (dest.height, dest.width, dest.getLinePointer (0) + i, dest.lineStride, 3, src.getLinePointer  (0) + i, src.lineStride,  4, src.getLinePointer  (0) + 3, src.lineStride,  4,
                &BlendOperator::phoenix); break;
              break;
          }
        }
        break;

      case Image::ARGB:
      case Image::SingleChannel:
      case Image::UnknownFormat:
      default:
        jassertfalse;
      }
      break;

    case Image::RGB:
    case Image::SingleChannel:
    case Image::UnknownFormat:
    default:
      jassertfalse;
      break;
    }
  }
}
