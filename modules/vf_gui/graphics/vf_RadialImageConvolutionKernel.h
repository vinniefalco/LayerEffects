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

#ifndef VF_RADIALIMAGECONVOLUTIONKERNEL_VFHEADER
#define VF_RADIALIMAGECONVOLUTIONKERNEL_VFHEADER

/*============================================================================*/
/**
    Fast Image convolution with radially symmetric kernels.

    Takes advantage of radial symmetry to implement an efficient image
    convolution.

    @ingroup vf_gui
*/
class RadialImageConvolutionKernel
{
public:
  // This includes the center sample
  explicit RadialImageConvolutionKernel (int radiusInSamples);
  ~RadialImageConvolutionKernel ();

  int getRadiusInSamples () { return m_radius; }

  // the gaussian radius will be (radiusInSamples-1)/2
  void createGaussianBlur ();

  void setOverallSum (float desiredTotalSum);

  void rescaleAllValues (float multiplier);
  
  // creates a convolved image with the same dimensions as the source
  Image createConvolvedImage (Image const& sourceImage) const;

  // creates a larger image that fully contains the result
  // of applying the convolution kernel to the source image.
  Image createConvolvedImageFull (Image const& sourceImage) const;

  //
  // copy a line of color components, performing edge
  // replication on either side. dest must have 2 * replicas
  // more components than src.
  //
  static void copy (int pixels,
                    uint8* dest,
                    int destSkip,
                    const uint8* src,
                    int srcSkip,
                    int replicas);

  //
  // copy a line of alpha values, inserting fully transparent
  // values (0) as replicas on either side
  //
  static void copy_alpha (int pixels,
                          uint8* dest,
                          int destSkip,
                          const uint8* src,
                          int srcSkip,
                          int replicas);

  //
  // convolve a line of color components.
  // src must have 2 * (radius - 1) more components than dest
  //
  static void convolve (int pixels,
                        uint8* dest,
                        int destSkip,
                        uint8 const* src,
                        int srcSkip,
                        int radius,
                        float const* kernel);

private:
  const int m_radius;
  HeapBlock <float> m_kernel;
};

#endif

