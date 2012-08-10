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

#ifndef VF_MAP2D_VFHEADER
#define VF_MAP2D_VFHEADER

/** Two dimensional array.

    @ingroup vf_core
*/
template <class T>
class Map2D : Uncopyable
{
public:
  typedef typename T Type;

  /** Creates a null map.
  */
  Map2D ()
  {
  }

  /** Create a new 2D map with the specified size.
  */
  Map2D (int width, int height, bool fillMemoryWithZeros = false)
    : m_data (new Data (width, height, fillMemoryWithZeros))
  {
  }
  
  /** Creates a shared reference to another map's data.
  */
  Map2D (Map2D const& other)
    : m_data (other.m_data)
  {
  }

  /** Set this as a shared reference to another map's data.
  */
  Map2D& operator= (Map2D const& other)
  {
    m_data = other.m_data;
    return *this;
  }

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
  Map2D (Map2D&& other) noexcept
    : m_data (static_cast <Data::Ptr&&> (other.m_data))
  {
  }

  Map2D& operator= (Map2D&& other) noexcept
  {
      m_data = static_cast <Data::Ptr&&> (other.m_data);
      return *this;
  }
#endif

  /** Destructor.
  */
  ~Map2D ()
  {
  }

  /** Returns true if the map is null.
  */
  bool isNull () const noexcept
  {
    return m_data == nullptr;
  }

  /** Returns true if the map is not null.
  */
  bool isValid () const noexcept
  {
    return m_data != nullptr;
  }

  /** Initialize all elements with a value.
  */
  template <class U>
  void reset (U u = U ()) const noexcept
  {
     std::fill (data->getData (), data->getData () + rows * cols, u);
  }

  /** Get a pointer to the start of the data.
  */
  inline T* getData () const noexcept
  {
    return m_vec.getData ();
  }

  /** Conversion to T*.
  */
  inline operator T* () const noexcept
  {
    return m_data->getData ();
  }

  /** Get the number of rows.
  */
  inline int getRows () const noexcept
  {
    return m_data->getRows ();
  }

  /** Get the number of columns.
  */
  inline int getCols () const noexcept
  {
    return m_data->getCols ();
  }

  /** Access an element.
  */
  inline T& get (int x, int y) const noexcept
  {
    return m_data->get (x, y); 
  }

  /** Access an element.
  */
  inline T& operator() (int x, int y) const noexcept
  {
    return get (x, y);
  }

  /** Retrieve an entire row.
  */
  inline T* getRow (int y) const noexcept
  {
    return m_data->getRow ();
  }

private:
  class Data : public ReferenceCountedObject
  {
  public:
    typedef ReferenceCountedObjectPtr <Data> Ptr;

    Data (int width, int height, bool fillMemoryWithZeros = false)
      : m_rows (height)
      , m_cols (width)
      , m_vec (height * width, fillMemoryWithZeros)
    {
    }

    inline int getRows () const noexcept
    {
      return m_rows;
    }

    inline int getCols () const noexcept
    {
      return m_cols;
    }

    inline T* getData () const noexcept
    {
      return m_vec.getData ();
    }

    inline T& get (int x, int y) const noexcept
    {
      jassert (isPositiveAndBelow (x, m_cols) && isPositiveAndBelow (y, m_rows));
      return m_vec [y * m_cols + x];
    }

    inline T* getRow (int y) const noexcept
    {
      jassert (isPositiveAndBelow (y, m_rows));
    
      return m_vec + y * m_cols;
    }

  private:
    int const m_rows;
    int const m_cols;
    HeapBlock <T> m_vec;
  };

  typename Data::Ptr m_data;
};

#endif
