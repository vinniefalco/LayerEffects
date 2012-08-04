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

void unPremultiplyImage (Image dest)
{
  Pixels::Iterate1 (Pixels (dest)) (BlendProc::ARGB::Unpremultiply ());
}

//------------------------------------------------------------------------------

void fillImage (Image dest,
                Point <int> destTopLeft,
                Image mask,
                Rectangle <int> maskBounds,
                BlendMode::Type mode,
                double opacity,
                Colour colour)
{
  jassert (mask.getFormat () == Image::SingleChannel);
  jassert (mask.getBounds ().contains (maskBounds));

  Rectangle <int> const destBounds = dest.getBounds ().getIntersection (
    Rectangle <int> (destTopLeft.getX (), destTopLeft.getY (),
                     maskBounds.getWidth (), maskBounds.getHeight ()));

  maskBounds.setSize (destBounds.getWidth (), destBounds.getHeight ());

  Pixels destPixels (dest, destBounds);
  Pixels maskPixels (mask, maskBounds);

  switch (dest.getFormat ())
  {
  case Image::RGB:
    BlendMode::apply (
      mode,
      Pixels::Iterate2 (destPixels, maskPixels),
      BlendProc::RGB::Fill (colour, opacity));
    break;

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
                BlendMode::Type mode,
                double opacity)
{
  jassert (source.getBounds ().contains (sourceBounds));
  jassert (dest.getBounds ().contains (destTopLeft));

  Rectangle <int> const destBounds = dest.getBounds ().getIntersection (
    Rectangle <int> (destTopLeft.getX (), destTopLeft.getY (),
                     sourceBounds.getWidth (), sourceBounds.getHeight ()));

  sourceBounds.setSize (destBounds.getWidth (), destBounds.getHeight ());

  Pixels destPixels (dest, destBounds);
  Pixels sourcePixels (source, sourceBounds);

  switch (dest.getFormat ())
  {
  case Image::SingleChannel:
    switch (source.getFormat ())
    {
    case Image::SingleChannel:
      BlendMode::apply (
        mode,
        Pixels::Iterate2 (destPixels, sourcePixels),
        BlendProc::Gray::Copy (opacity));
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
      BlendMode::apply (
        mode,
        Pixels::Iterate2 (destPixels, sourcePixels),
        BlendProc::RGB::Copy (opacity));
      break;

    case Image::ARGB:
      BlendMode::apply (
        mode,
        Pixels::Iterate2 (destPixels, sourcePixels),
        BlendProc::RGB::CopyARGB (opacity));
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
