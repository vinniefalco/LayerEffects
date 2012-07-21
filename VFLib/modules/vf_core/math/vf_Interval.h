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

#ifndef VF_INTERVAL_VFHEADER
#define VF_INTERVAL_VFHEADER

// Represents the half-open interval [m_begin, m_end)
template <class Ty>
class Interval
{
public:
  typedef Ty value_type;

  static const Interval none;

  Interval ()
  {
  }

  Interval (const Ty& begin, const Ty& end)
    : m_begin (begin)
    , m_end (end)
  {
  }

  Interval (const Interval& other)
    : m_begin (other.m_begin)
    , m_end (other.m_end)
  {
  }

  Interval& operator= (const Interval& other)
  {
    m_begin = other.m_begin;
    m_end = other.m_end;
    return *this;
  }

  bool operator== (Interval const& rhs) const
  {
    return (empty() && rhs.empty()) ||
           (m_begin == rhs.m_begin && m_end == rhs.m_end);
  }

  bool operator!= (Interval const& rhs ) const
  {
    return !this->operator== (rhs);
    /*
    return empty() ? (!rhs.empty()) :
                     (rhs.empty() || (m_begin != rhs.m_begin ||
                                      m_end != rhs.m_end));
    */
  }

  Ty const& begin () const { return m_begin; }
  Ty const& end () const { return m_end; }
  Ty count () const { return empty () ? 0 : (m_end-m_begin); } // Lebesque measure
  Ty length () const { return count (); }  // sugar
  Ty distance () const { return count (); } // sugar
  bool empty () const { return m_begin >= m_end; }
  bool notEmpty () const { return m_begin < m_end; }
  void setBegin (Ty const& v) { m_begin = v; }
  void setEnd (Ty const& v) { m_end = v; }
  void setLength (Ty const& v) { m_end = m_begin + v; }

  bool contains (Ty const& v ) const
  {
    return notEmpty () && v >= m_begin && v < m_end;
  }

  bool intersects (Interval const& interval) const
  {
    return notEmpty() && interval.notEmpty() &&
           m_end > interval.m_begin && m_begin < interval.m_end;
  }

  // true iff the union is a single non empty half-open interval
  bool adjoins (Interval const& interval) const
  {
    return (empty() != interval.empty()) ||
           (notEmpty() && m_end >= interval.m_begin
                       && m_begin <= interval.m_end);
  }

  bool disjoint (Interval const& interval) const
  {
    return !intersects (interval);
  }

  // A is a superset of B if B is empty or if A fully contains B
  bool superset_of (Interval const& interval) const
  {
    return interval.empty() ||
           (notEmpty() && m_begin <= interval.m_begin
                       && m_end >= interval.m_end);
  }

  // A is a proper superset of B iff:
  // - A is not empty,
  // - B is empty OR A contains B and A has more than B
  bool proper_superset_of (Interval const& interval) const
  {
    return notEmpty() &&
           (interval.empty() || (
             (m_begin <= interval.m_begin && m_end >  interval.m_end) ||
             (m_begin <  interval.m_begin && m_end >= interval.m_end) ));
  }

  bool subset_of (Interval const& interval) const
  {
    return interval.superset_of (*this);
  }

  bool proper_subset_of (Interval const& interval) const
  {
    return interval.proper_superset_of (*this);
  }

  Interval intersection (const Interval& interval) const
  {
    return Interval (std::max (m_begin, interval.m_begin),
                     std::min (m_end, interval.m_end));
  }

  // Returns the smallest interval that contains both intervals
  Interval simple_union (Interval const& interval ) const
  {
    return Interval(
             std::min (interval.normalized().m_begin, normalized().m_begin),
             std::max (interval.normalized().m_end, normalized().m_end));
  }

  // empty if the union cannot be represented as a single half-open interval
  Interval single_union (Interval const& interval) const
  {
    if (empty())
      return interval;

    else if (interval.empty())
      return *this;

    else if (m_end < interval.m_begin || m_begin > interval.m_end)
      return none;

    else
      return Interval (std::min (m_begin, interval.m_begin),
                       std::max (m_end, interval.m_end));
  }

  // Returns true if the Interval is correctly ordererd
  bool normal () const
  {
    return m_end >= m_begin;
  }

  // Returns a correctly ordered interval
  Interval normalized () const
  {
    if (normal ())
      return *this;
    else
      return Interval (m_end, m_begin);
  }

  // Clamp the value to lie within the interval
  template <typename Tv>
  const Ty clamp (Tv v) const
  {
    // These conditionals are carefully ordered so
    // that if m_begin == m_end, value is assigned m_begin.
    if (v > m_end)
      v = m_end - (std::numeric_limits <Tv>::is_integer ? 1 :
                   std::numeric_limits <Tv>::epsilon());

    if (v < m_begin)
      v = m_begin;

    return v;
  }

private:
  Ty m_begin;
  Ty m_end;
};

template <typename Ty>
const Interval<Ty> Interval<Ty>::none = Interval<Ty>(Ty(), Ty());

#endif
