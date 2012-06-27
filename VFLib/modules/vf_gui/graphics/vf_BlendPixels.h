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

#ifndef VF_BLENDIMAGE_VFHEADER
#define VF_BLENDIMAGE_VFHEADER

/*============================================================================*/
/**
    Image composition functions.

    These replicate the Photoshop layer blending modes.

    See: http://inlandstudios.com/en/?p=851

    @ingroup vf_gui
*/
struct BlendMode
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
    return (f + b < 255) ? 0 : (f + b - 255);
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

  static inline int softlight (int f, int b)
  {
    return int ((b < 128) ? (2 * ((f >> 1) + 64)) * ((float)b / 255)
                          : (255 - (2 * (255 - ((f >> 1) + 64)) * (float)(255 - b) / 255)));
  }

  static inline int hardlight (int f, int b)
  {
    return overlay (b, f);
  }

  static inline int colordodge (int f, int b)
  {
    return (b == 255) ? b : std::min (255, (f << 8) / (255 - b));
  }

  static inline int colorburn (int f, int b)
  {
    return (b == 0) ? 0 : std::max (0, (255 - ((255 - f) << 8) / b));
  }

  static inline int lineardodge (int f, int b)
  {
    return add (f, b);
  }

  static inline int linearburn (int f, int b)
  {
    return subtract (f, b);
  }

  static inline int linearlight (int f, int b)
  {
    return (b < 128) ? linearburn (f, 2 * b)
                     : lineardodge (f, 2 * (b - 128));
  }

  static inline int vividlight (int f, int b)
  {
    return (b < 128) ? colorburn (f, 2 * b)
                     : colordodge (f, 2 * (b - 128));
  }

  static inline int pinlight (int f, int b)
  {
    return (b < 128) ? darken (f, 2 * b)
                     : lighten (f, 2 * (b - 128));
  }

  static inline int hardmix (int f, int b)
  {
    return (vividlight (f, b) < 128) ? 0 : 255;
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
template <int ColBytes, class BlendOp>
void blendChannel (int            rows,
                   int            cols,
                   uint8*         dest,
                   int            destRowBytes,
                   uint8 const*   front,
                   int            frontRowBytes,
                   uint8 const*   back,
                   int            backRowBytes,
                   uint8 const*   mask,
                   int            maskRowBytes,
                   BlendOp const& blendOp)
{
  frontRowBytes -= cols * ColBytes;
  backRowBytes  -= cols * ColBytes;
  maskRowBytes  -= cols * ColBytes;
  destRowBytes  -= cols * ColBytes;

  while (rows--)
  {
    for (int x = cols; x--;)
    {
      int const result = static_cast <uint8> (blendOp (*front, *back));

      // v = v0 + (v1 - v0) * t
      *dest = static_cast <uint8> (*dest + ((result - *dest) * *mask) / 255);

      front += ColBytes;
      back  += ColBytes;
      mask  += ColBytes;
      dest  += ColBytes;
    }

    front += frontRowBytes;
    back  += backRowBytes;
    mask  += maskRowBytes;
    dest  += destRowBytes;
  }
}

#endif
