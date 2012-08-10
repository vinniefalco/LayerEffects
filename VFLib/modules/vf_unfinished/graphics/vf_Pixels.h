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

#ifndef VF_PIXELS_VFHEADER
#define VF_PIXELS_VFHEADER

/** Image pixel data.

    This convenient wrapper provides reference counting and efficient pass by
    value semantics to @ref Image::BitmapData objects, to facilitate its usage
    in generic programming.

    @ingroup vf_gui
*/
class Pixels
{
public:
  static Pixels const null;

  /** Creates a null pixel data.
  */
  Pixels ();

  /** Creates pixel data from an image.
  */
  explicit Pixels (
    Image image,
    Image::BitmapData::ReadWriteMode access = Image::BitmapData::readWrite);

  /** Creates pixel data from a portion of an image.
  */
  Pixels (
    Image,
    Rectangle <int> const& bounds,
    Image::BitmapData::ReadWriteMode access = Image::BitmapData::readWrite);

  /** Creates a shared reference to another pixel data.
  */
  Pixels (Pixels const& other);

  /** Make this pixel data refer to another pixel data.
  */
  Pixels& operator= (Pixels const& other);

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
  Pixels (Pixels&& other) noexcept;
  Pixels& operator= (Pixels&& other) noexcept;
#endif

  /** Destructor.
  */
  ~Pixels ();

  /** Returns true if this shares the same @ref Image::BitmapData.
  */
  inline bool operator== (Pixels const& other) const noexcept
  {
    return m_data == other.m_data;
  }

  /** Returns true if this does not share the same @ref Image::BitmapData.
  */
  inline bool operator!= (Pixels const& other) const noexcept
  {
    return m_data != other.m_data;
  }

  /** Returns true if the pixel data is not null.
  */
  inline bool isValid () const noexcept
  {
    return m_data != nullptr;
  }

  /** Returns true if the pixel data is null.
  */
  inline bool isNull () const noexcept
  {
    return m_data == nullptr;
  }

  /** Retrieve the pixel format.
  */
  inline Image::PixelFormat getFormat () const noexcept
  {
    return m_data->pixelFormat;
  }

  /** Return `true` if the format is RGB.
  */
  inline bool isRGB () const noexcept
  {
    return getFormat () == Image::RGB;
  }

  /** Return `true` if the format is ARGB.
  */
  inline bool isARGB () const noexcept
  {
    return getFormat () == Image::ARGB;
  }

  /** Return `true` if the format is single channel.
  */
  inline bool isSingleChannel () const noexcept
  {
    return getFormat () == Image::SingleChannel;
  }

  /** Retrieve a pointer to the start of the pixel data.
  */
  inline uint8* getData () const noexcept
  {
    return m_data->data;
  }

  /** Retrieve the bounding rectangle.
  */
  inline Rectangle <int> getBounds () const noexcept
  {
    return Rectangle <int> (0, 0, m_data->width, m_data->height);
  }

  /** Retrieve the width in pixels.
  */
  inline int getCols () const noexcept
  {
    return m_data->width;
  }

  inline int getWidth () const noexcept
  {
    return m_data->width;
  }

  /** Retrieve the height in pixels.
  */
  inline int getRows () const noexcept
  {
    return m_data->height;
  }

  inline int getHeight () const noexcept
  {
    return m_data->height;
  }

  /** Retrieve a pointer to the beginning of the specified line.
  */
  inline uint8* getLinePointer (int y) const noexcept
  {
    return m_data->getLinePointer (y);
  }

  /** Retrieve a pointer to the beginning of the specified pixel.
  */
  inline uint8* getPixelPointer (int x, int y) const noexcept
  {
    return m_data->getPixelPointer (x, y);
  }

  /** Retrieve the bytes per line.
  */
  inline int getRowBytes () const noexcept
  {
    return m_data->lineStride;
  }

  /** Retrieve the bytes per column.
  */
  inline int getColBytes () const noexcept
  {
    return m_data->pixelStride;
  }

public:
  class Map2D;
  class Iterate1;
  class Iterate2;

private:
  class Data : public Image::BitmapData, public ReferenceCountedObject
  {
  public:
    typedef ReferenceCountedObjectPtr <Data> Ptr;

    Data (Image image,
          Rectangle <int> const& bounds,
          Image::BitmapData::ReadWriteMode access)
      : BitmapData (
          image,
          bounds.getX (), bounds.getY (),
          bounds.getWidth (), bounds.getHeight (),
          access)
    {
      jassert (image.getBounds ().contains (bounds));
    }
  };

  Data::Ptr m_data;
};

//------------------------------------------------------------------------------

/** Present a Pixels object as a Map2D concept.
*/
class Pixels::Map2D
{
public:
  typedef uint8 Type;
  explicit Map2D (Pixels src) : m_src (src) { }
  inline int getRows () const noexcept { return m_src.getRows (); }
  inline int getCols () const noexcept { return m_src.getCols (); }
  
  inline Type& get (int x, int y) const noexcept
  {
    return *m_src.getPixelPointer (x, y);
  }

  inline Type& operator() (int x, int y) const noexcept
  {
    return get (x, y);
  }

private:
  Pixels m_src;
};

//------------------------------------------------------------------------------

/** Functor to apply a functor to one Pixels map.

    Prototype for `Functor`:

    @code

    void f (uint8* pixel);

    @endcode
*/
class Pixels::Iterate1
{
public:
  explicit Iterate1 (Pixels map) : m_map (map)
  {
  }

  template <class Functor>
  void operator () (Functor f)
  {
    int const colSkip = m_map.getColBytes ();
    int const rowSkip = m_map.getRowBytes () - m_map.getCols () * colSkip;

    uint8* pixel = m_map.getData ();

    for (int y = m_map.getRows (); y--;)
    {
      for (int x = m_map.getCols (); x--;)
      {
        f (pixel);

        pixel = addBytesToPointer (pixel, colSkip);
      }

      pixel = addBytesToPointer (pixel, rowSkip);
    }
  }

private:
  Pixels m_map;
};

//------------------------------------------------------------------------------

/** Functor to apply a functor to two Pixels maps.

    Prototype for `Functor`:

    @code

    void f (uint8* pixel1, uint8* pixel2);

    @endcode
*/
class Pixels::Iterate2
{
public:
  Iterate2 (Pixels map1, Pixels map2)
    : m_map1 (map1), m_map2 (map2)
  {
    jassert (m_map1.getBounds () == m_map2.getBounds ());
  }

  template <class Functor>
  void operator () (Functor f)
  {
    int const colSkip1 = m_map1.getColBytes ();
    int const rowSkip1 = m_map1.getRowBytes () - m_map1.getCols () * colSkip1;
    int const colSkip2 = m_map2.getColBytes ();
    int const rowSkip2 = m_map2.getRowBytes () - m_map2.getCols () * colSkip2;

    uint8* pixel1 = m_map1.getData ();
    uint8* pixel2 = m_map2.getData ();

    for (int y = m_map1.getRows (); y--;)
    {
      for (int x = m_map1.getCols (); x--;)
      {
        f (pixel1, pixel2);

        pixel1 = addBytesToPointer (pixel1, colSkip1);
        pixel2 = addBytesToPointer (pixel2, colSkip2);
      }

      pixel1 = addBytesToPointer (pixel1, rowSkip1);
      pixel2 = addBytesToPointer (pixel2, rowSkip2);
    }
  }

private:
  Pixels m_map1;
  Pixels m_map2;
};

//------------------------------------------------------------------------------

/** Fill an image with colour.
*/
extern void fillImage (Image dest,
                       Point <int> destTopLeft,
                       Image mask,
                       Rectangle <int> maskBounds,
                       BlendMode::Type mode,
                       double opacity,
                       Colour colour);

/** Copy one image over another.
*/
extern void copyImage (Image dest,
                       Point <int> destTopLeft,
                       Image source,
                       Rectangle <int> sourceBounds,
                       BlendMode::Type mode,
                       double opacity);

#endif
