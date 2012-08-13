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

void DropShadowStyle::operator() (Pixels destPixels, Pixels maskPixels)
{
  if (!active)
    return;

#if 0
  Options::DropShadow& dropShadow = m_options.dropShadow;

  if (!dropShadow.active)
    return;

#if 0
  int const dx = static_cast <int> (
    - dropShadow.distance * std::cos (dropShadow.angle) + 0.5) - dropShadow.size;
  
  int const dy = static_cast <int> (
    dropShadow.distance * std::sin (dropShadow.angle) + 0.5) - dropShadow.size;
#endif

  // Get the layer mask as an individual channel.
  Image mask = ChannelImageType::fromImage (m_fill, PixelARGB::indexA);
  
  RadialImageConvolutionKernel k (dropShadow.size + 1);
  k.createGaussianBlur ();

  // Compute the shadow mask.
  Image shadow = k.createConvolvedImageFull (mask);

  // Optionally subtract layer mask from shadow mask.
  if (dropShadow.knockout)
    copyImage (
      shadow,
      //Point <int> (dropShadow.size + dx, dropShadow.size + dy),
      Point <int> (0, 0),
      mask,
      mask.getBounds (),
      BlendMode::modeSubtract,
      1);

  // Fill the shadow mask.
  fillImage (workImage,
             Point <int> (0, 0),
             shadow,
             shadow.getBounds (),
             dropShadow.mode,
             dropShadow.opacity,
             dropShadow.colour);
#endif
}
