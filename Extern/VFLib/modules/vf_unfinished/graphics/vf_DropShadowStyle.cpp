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
/*
Outline:

Enlarge stencil
Dilate
Blur

*/
static inline double cos_73s (double x) 
{ 
  const double c1= 0.999999953464; 
  const double c2=-0.4999999053455; 
  const double c3= 0.0416635846769; 
  const double c4=-0.0013853704264; 
  const double c5= 0.000023233 ;  // Note: this is a better coefficient than Hart's 
  //   submitted by Steven Perkins 2/22/07 
  double x2; 
  // The input argument squared 
  x2=x * x; 
  return (c1 + x2*(c2 + x2*(c3 + x2*(c4 + c5*x2)))); 
} 
double const pie=3.1415926535897932384626433;// pi 
double const twopi=2.0*pie; 
double const halfpi=pie/2.0;  // pi times 2 

// pi divided by 2 
// 
//  This is the main cosine approximation "driver" 
// It reduces the input argument's range to [0, pi/2], 
// and then calls the approximator.  
// 
template <class T>
T cos_32(T x){ 

  int quad; 
  // what quadrant are we in? 
  x=fmod (x, T (twopi)); 
  // Get rid of values > 2* pi 
  if(x<0)x=-x; 
  // cos(-x) = cos(x) 
  quad=int(x/halfpi); 
  // Get quadrant # (0 to 3) 
  switch (quad){ 
  case 0: return  cos_73s(x); 
  case 1: return -cos_73s(pie-x); 
  case 2: return -cos_73s(x-pie); 
  default:
  case 3: return  cos_73s(twopi-x); 
  } 
} 

// input range [0, 65536]
#if 0
static inline unsigned char contour (int input)
{
  return std::abs (cos_32 (float(input)/8192) * 255);
}
#else
static inline unsigned char contour (int input)
{
  return static_cast <unsigned char> (input / 257);
}
#endif

void DropShadowStyle::operator() (Pixels destPixels, Pixels stencilPixels)
{
  if (!active)
    return;

  // Calculate blur radius and dilate size from settings
  //
  LayerStyles::BoxBlurAndDilateSettings bd (size, spread);

  int const xExpand = bd.getEnlargePixels ();
  int const yExpand = bd.getEnlargePixels ();
  int const xOffset = - static_cast <int> (cos (angle) * distance + 0.5);
  int const yOffset = static_cast <int> (sin (angle) * distance + 0.5);
  int const width = stencilPixels.getWidth () + 2 * xExpand;
  int const height = stencilPixels.getHeight () + 2 * yExpand;

  // Intermediate storage
  //
  Map2D <int> distanceMap (width, height);
  Map2D <int> blurMap (width, height);
  Image mask (Image::SingleChannel, width, height, false);
  Pixels maskPixels (mask);

  // Calculate compositing rectangles
  //
  Rectangle <int> maskRect (maskPixels.getBounds ());
  Rectangle <int> destRect (destPixels.getBounds ());

  maskRect = mask.getBounds ();
  maskRect.translate (+(xOffset-xExpand), +(yOffset-yExpand));
  destRect = destPixels.getBounds ().getIntersection (maskRect);
  maskRect = destRect.translated (-(xOffset-xExpand), -(yOffset-yExpand));

  jassert (maskRect.getWidth () == destRect.getWidth ());
  jassert (maskRect.getHeight () == destRect.getHeight ());
  jassert (mask.getBounds ().contains (maskRect));
  jassert (destPixels.getBounds ().contains (destRect));

  // Dilate stencil mask
  //
  LayerStyles::GrayscaleDilation () (
    Pixels::Map2D (stencilPixels),
    stencilPixels.getRows (),
    stencilPixels.getCols (),
    distanceMap,
    height,
    width,
    xExpand,
    yExpand,
    bd.getDilatePixels ());

  // Blur 32-bit signed mask
  // Output is 32-bit signed with 8-bit fixed point.
  //

  BoxBlur () (distanceMap, blurMap, width, height, bd.getBoxBlurRadius ());

  // Transform fixed point mask to 8-bit unsigned mask using contour curve
  //
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      int const alpha = blurMap (x, y);

      jassert (alpha < 65536);

      *maskPixels.getPixelPointer (x, y) = contour (alpha);
    }
  }

  PixelProcs procs;

#if 0
  if (knockout)
  {
    procs.copyGray (
      maskRect.getHeight (),
      maskRect.getWidth (),
      stencilPixels.getPixelPointer (destRect.getX (), destRect.getY ()),
      stencilPixels.getRowBytes (),
      stencilPixels.getColBytes (),
      maskPixels.getPixelPointer (maskRect.getX (), maskRect.getY ()),
      maskPixels.getRowBytes (),
      maskPixels.getColBytes (),
      BlendMode::subtract ());
  }
#endif

  // Colorize destination using mask
  {
    unsigned char c [3];
    c [PixelRGB::indexR] = colour.getRed ();
    c [PixelRGB::indexG] = colour.getGreen ();
    c [PixelRGB::indexB] = colour.getBlue ();

    procs.fillRGB (
      maskRect.getHeight (),
      maskRect.getWidth (),
      c,
      opacity,
      maskPixels.getPixelPointer (maskRect.getX (), maskRect.getY ()),
      maskPixels.getRowBytes (),
      maskPixels.getColBytes (),
      destPixels.getPixelPointer (destRect.getX (), destRect.getY ()),
      destPixels.getRowBytes (),
      destPixels.getColBytes (),
      mode);
  }
}
