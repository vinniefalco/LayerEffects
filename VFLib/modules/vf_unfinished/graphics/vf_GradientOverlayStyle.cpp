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

namespace BlendProc
{
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
}

void GradientOverlayStyle::render (
  Pixels destPixels,
  Options const& options)
{
  jassert (destPixels.isARGB ());

  SharedTable <Colour> table = options.colours.withMultipliedAlpha (float (options.opacity)).createLookupTable ();

  switch (options.kind)
  {
  case kindLinear:
    jassertfalse;
    break;

  case kindRadial:
    jassertfalse;
    break;

  case kindAngle:
    BlendMode::apply (
      options.mode,
      AngleGradientIterator (destPixels, destPixels.getBounds().getCentre (), table.getNumEntries () - 1),
      BlendProc::CopyTable (table));
    break;

  case kindReflected:
    jassertfalse;
    break;

  case kindDiamond:
    BlendMode::apply (
      options.mode,
      DiamondGradientIterator (destPixels, destPixels.getBounds().getCentre (), table.getNumEntries () - 1),
      BlendProc::CopyTable (table));
    break;

  default:
    jassertfalse;
    break;
  }
}
