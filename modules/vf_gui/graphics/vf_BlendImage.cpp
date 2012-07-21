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

void fillImage (Image dest,
                Point <int> destTopLeft,
                Image mask,
                Rectangle <int> maskBounds,
                BlendMode mode,
                double opacity,
                Colour colour)
{
  jassert (mask.getFormat () == Image::SingleChannel);
  jassert (mask.getBounds ().contains (maskBounds));

  Rectangle <int> const bounds = maskBounds.getIntersection (
    dest.getBounds () + destTopLeft);

  Pixels destPixels (dest, bounds);
  Pixels maskPixels (mask, bounds);

  switch (dest.getFormat ())
  {
  case Image::RGB:
    switch (mode)
    {
    case normal:      destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::normal> (colour, opacity)); break;
    case lighten:     destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::lighten> (colour, opacity)); break;
    case darken:      destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::darken> (colour, opacity)); break;
    case multiply:    destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::multiply> (colour, opacity)); break;
    case average:     destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::average> (colour, opacity)); break;
    case add:         destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::add> (colour, opacity)); break;
    case subtract:    destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::subtract> (colour, opacity)); break;
    case difference:  destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::difference> (colour, opacity)); break;
    case negation:    destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::negation> (colour, opacity)); break;
    case screen:      destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::screen> (colour, opacity)); break;
    case exclusion:   destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::exclusion> (colour, opacity)); break;
    case overlay:     destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::overlay> (colour, opacity)); break;
    case softLight:   destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::softLight> (colour, opacity)); break;
    case hardLight:   destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::hardLight> (colour, opacity)); break;
    case colorDodge:  destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::colorDodge> (colour, opacity)); break;
    case colorBurn:   destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::colorBurn> (colour, opacity)); break;
    case linearDodge: destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::linearDodge> (colour, opacity)); break;
    case linearBurn:  destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::linearBurn> (colour, opacity)); break;
    case linearLight: destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::linearLight> (colour, opacity)); break;
    case vividLight:  destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::vividLight> (colour, opacity)); break;
    case pinLight:    destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::pinLight> (colour, opacity)); break;
    case hardMix:     destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::hardMix> (colour, opacity)); break;
    case reflect:     destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::reflect> (colour, opacity)); break;
    case glow:        destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::glow> (colour, opacity)); break;
    case phoenix:     destPixels.iterate (maskPixels, Pixels::FillMaskRGB <Pixels::Mode::phoenix> (colour, opacity)); break;
    default:
      jassertfalse;
    };
    break;

  case Image::SingleChannel:
  case Image::ARGB:
  default:
    jassertfalse;
    break;
  };
}

//------------------------------------------------------------------------------

void copyImage (Image dest,
                Point <int> destTopLeft,
                Image source,
                Rectangle <int> sourceBounds,
                BlendMode mode,
                double opacity)
{
  jassert (source.getBounds ().contains (sourceBounds));

  Rectangle <int> const bounds = sourceBounds.getIntersection (
    dest.getBounds () + destTopLeft);

  Pixels destPixels (dest, bounds);
  Pixels sourcePixels (source, bounds);

  switch (dest.getFormat ())
  {
  case Image::SingleChannel:
    switch (source.getFormat ())
    {
    case Image::SingleChannel:
      switch (mode)
      {
      case normal:      destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::normal> (opacity)); break;
      case lighten:     destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::lighten> (opacity)); break;
      case darken:      destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::darken> (opacity)); break;
      case multiply:    destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::multiply> (opacity)); break;
      case average:     destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::average> (opacity)); break;
      case add:         destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::add> (opacity)); break;
      case subtract:    destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::subtract> (opacity)); break;
      case difference:  destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::difference> (opacity)); break;
      case negation:    destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::negation> (opacity)); break;
      case screen:      destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::screen> (opacity)); break;
      case exclusion:   destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::exclusion> (opacity)); break;
      case overlay:     destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::overlay> (opacity)); break;
      case softLight:   destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::softLight> (opacity)); break;
      case hardLight:   destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::hardLight> (opacity)); break;
      case colorDodge:  destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::colorDodge> (opacity)); break;
      case colorBurn:   destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::colorBurn> (opacity)); break;
      case linearDodge: destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::linearDodge> (opacity)); break;
      case linearBurn:  destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::linearBurn> (opacity)); break;
      case linearLight: destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::linearLight> (opacity)); break;
      case vividLight:  destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::vividLight> (opacity)); break;
      case pinLight:    destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::pinLight> (opacity)); break;
      case hardMix:     destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::hardMix> (opacity)); break;
      case reflect:     destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::reflect> (opacity)); break;
      case glow:        destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::glow> (opacity)); break;
      case phoenix:     destPixels.iterate (sourcePixels, Pixels::BlendGray <Pixels::Mode::phoenix> (opacity)); break;
      default:
        jassertfalse;
      };
      break;

    default:
      jassertfalse;
      break;
    };
    break;

  case Image::RGB:
    switch (source.getFormat ())
    {
    case Image::RGB:
      switch (mode)
      {
      case normal:      destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::normal> (opacity)); break;
      case lighten:     destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::lighten> (opacity)); break;
      case darken:      destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::darken> (opacity)); break;
      case multiply:    destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::multiply> (opacity)); break;
      case average:     destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::average> (opacity)); break;
      case add:         destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::add> (opacity)); break;
      case subtract:    destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::subtract> (opacity)); break;
      case difference:  destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::difference> (opacity)); break;
      case negation:    destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::negation> (opacity)); break;
      case screen:      destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::screen> (opacity)); break;
      case exclusion:   destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::exclusion> (opacity)); break;
      case overlay:     destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::overlay> (opacity)); break;
      case softLight:   destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::softLight> (opacity)); break;
      case hardLight:   destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::hardLight> (opacity)); break;
      case colorDodge:  destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::colorDodge> (opacity)); break;
      case colorBurn:   destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::colorBurn> (opacity)); break;
      case linearDodge: destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::linearDodge> (opacity)); break;
      case linearBurn:  destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::linearBurn> (opacity)); break;
      case linearLight: destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::linearLight> (opacity)); break;
      case vividLight:  destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::vividLight> (opacity)); break;
      case pinLight:    destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::pinLight> (opacity)); break;
      case hardMix:     destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::hardMix> (opacity)); break;
      case reflect:     destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::reflect> (opacity)); break;
      case glow:        destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::glow> (opacity)); break;
      case phoenix:     destPixels.iterate (sourcePixels, Pixels::BlendRGB <Pixels::Mode::phoenix> (opacity)); break;
      default:
        jassertfalse;
      };
      break;

    case Image::ARGB:
      switch (mode)
      {
      case normal:      destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::normal> (opacity)); break;
      case lighten:     destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::lighten> (opacity)); break;
      case darken:      destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::darken> (opacity)); break;
      case multiply:    destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::multiply> (opacity)); break;
      case average:     destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::average> (opacity)); break;
      case add:         destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::add> (opacity)); break;
      case subtract:    destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::subtract> (opacity)); break;
      case difference:  destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::difference> (opacity)); break;
      case negation:    destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::negation> (opacity)); break;
      case screen:      destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::screen> (opacity)); break;
      case exclusion:   destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::exclusion> (opacity)); break;
      case overlay:     destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::overlay> (opacity)); break;
      case softLight:   destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::softLight> (opacity)); break;
      case hardLight:   destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::hardLight> (opacity)); break;
      case colorDodge:  destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::colorDodge> (opacity)); break;
      case colorBurn:   destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::colorBurn> (opacity)); break;
      case linearDodge: destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::linearDodge> (opacity)); break;
      case linearBurn:  destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::linearBurn> (opacity)); break;
      case linearLight: destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::linearLight> (opacity)); break;
      case vividLight:  destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::vividLight> (opacity)); break;
      case pinLight:    destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::pinLight> (opacity)); break;
      case hardMix:     destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::hardMix> (opacity)); break;
      case reflect:     destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::reflect> (opacity)); break;
      case glow:        destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::glow> (opacity)); break;
      case phoenix:     destPixels.iterate (sourcePixels, Pixels::BlendARGB <Pixels::Mode::phoenix> (opacity)); break;
      default:
        jassertfalse;
      };
      break;

    default:
      jassertfalse;
    };
    break;

  default:
    jassertfalse;
    break;
  };
}
