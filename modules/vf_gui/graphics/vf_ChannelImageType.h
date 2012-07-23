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

#ifndef VF_CHANNELIMAGETYPE_VFHEADER
#define VF_CHANNELIMAGETYPE_VFHEADER

/** Presents an Image channel as a separate Image.

    This creates a new @ref Image which references one channel in the
    specified @ref Image.

    @ingroup vf_gui
*/
class ChannelImageType : vf::Uncopyable
{
public:
  /** Create an Image that references a channel in the source image.

      The image type will be Image::SingleChannel, or Image::RGB if
      `channelNumber` is -1.

      @param sourceImage The image to retrieve a channel from.

      @param channelNumber 0 based channel number, -1 for all RGB channels.

      @return The resulting Image.
  */
  static Image fromImage (Image sourceImage, int channelNumber);

private:
  class ChannelPixelData : public ImagePixelData, vf::Uncopyable
  {
  public:
    ChannelPixelData (Image sourceImage, int channelNumber);

    ~ChannelPixelData ();

    LowLevelGraphicsContext* createLowLevelContext();

    ImagePixelData* clone ();

    ImageType* createType() const;

    void initialiseBitmapData (Image::BitmapData& bd,
                               int x,
                               int y,
                               Image::BitmapData::ReadWriteMode);

  private:
    Image::BitmapData m_bits;
    int const m_channelNumber;
  };
};

#endif
