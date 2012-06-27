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

