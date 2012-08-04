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

class GradientColours::Data : public ReferenceCountedObject
{
public:
  typedef ReferenceCountedObjectPtr <Data> Ptr;

  Data (int numColourStops, int numAlphaStops)
    : m_numAlphaStops (numAlphaStops)
    , m_numColourStops (numColourStops)
    , m_alphaStops (numAlphaStops)
    , m_colourStops (numColourStops)
  {
    jassert (numColourStops > 1 && numAlphaStops > 1);
  }

  ~Data ()
  {
  }

  Data* clone () const
  {
    Data* data = new Data (m_numColourStops, m_numAlphaStops);

    memcpy (
      data->m_alphaStops.getData (),
      m_alphaStops.getData (),
      m_numAlphaStops * sizeof (*m_alphaStops.getData ()));

    memcpy (
      data->m_colourStops.getData (),
      m_colourStops.getData (),
      m_numColourStops * sizeof (*m_colourStops.getData ()));

    return data;
  }

  inline int getNumAlphaStops () const noexcept
  {
    return m_numAlphaStops;
  }

  inline int getNumColourStops () const noexcept
  {
    return m_numColourStops;
  }

  inline AlphaStop& getAlphaStop (int index) const noexcept
  {
    jassert (index >= 0 && index < m_numAlphaStops);
    return m_alphaStops [index];
  }

  inline ColourStop& getColourStop (int index) const noexcept
  {
    jassert (index >= 0 && index < m_numColourStops);
    return m_colourStops [index];
  }

private:
  int const m_numAlphaStops;
  int const m_numColourStops;
  HeapBlock <AlphaStop> const m_alphaStops;
  HeapBlock <ColourStop> const m_colourStops;
};

//------------------------------------------------------------------------------

GradientColours const GradientColours::null;

GradientColours::GradientColours ()
{
}

GradientColours::GradientColours (int numColourStops, int numAlphaStops)
  : m_data (new Data (numColourStops, numAlphaStops))
{
}

GradientColours::GradientColours (Colour startColour, Colour endColour)
  : m_data (new Data (2, 2))
{
  m_data->getAlphaStop (0) = AlphaStop (1.f, 0.f, .5f);
  m_data->getAlphaStop (1) = AlphaStop (1.f, 1.f, .5f);
  m_data->getColourStop (0) = ColourStop (startColour, 0.f, .5f);
  m_data->getColourStop (1) = ColourStop (endColour, 1.f, .5f);
}

GradientColours::GradientColours (GradientColours const& other)
  : m_data (other.m_data)
{
}

GradientColours& GradientColours::operator= (GradientColours const& other)
{
  m_data = other.m_data;
  return *this;
}

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
GradientColours::GradientColours (GradientColours&& other) noexcept
    : m_data (static_cast <Data::Ptr&&> (other.m_data))
{
}

GradientColours& GradientColours::operator= (GradientColours&& other) noexcept
{
    m_data = static_cast <Data::Ptr&&> (other.m_data);
    return *this;
}
#endif

GradientColours::GradientColours (Data* data)
  : m_data (data)
{
}

GradientColours::~GradientColours ()
{
}

GradientColours GradientColours::withMultipliedAlpha (float alpha) const noexcept
{
  GradientColours result = createCopy ();

  for (int i = 0; i < result.getNumAlphaStops (); ++i)
    result.getAlphaStop (i).alpha = jlimit (0.f, 1.f, result.getAlphaStop (i).alpha * alpha);

  return result;
}

int GradientColours::getReferenceCount () const noexcept
{
  return m_data == nullptr ? 0 : m_data->getReferenceCount ();
}

GradientColours GradientColours::createCopy () const
{
   return GradientColours (m_data != nullptr ? m_data->clone() : nullptr);
}

void GradientColours::duplicateIfShared ()
{
  if (m_data != nullptr && m_data->getReferenceCount() > 1)
    m_data = m_data->clone ();
}

int GradientColours::getNumAlphaStops () const noexcept
{
  return m_data->getNumAlphaStops ();
}

int GradientColours::getNumColourStops () const noexcept
{
  return m_data->getNumColourStops ();
}

GradientColours::AlphaStop& GradientColours::getAlphaStop (int index) const noexcept
{
  return m_data->getAlphaStop (index);
}

GradientColours::ColourStop& GradientColours::getColourStop (int index) const noexcept
{
  return m_data->getColourStop (index);
}

SharedTable <Colour> GradientColours::createLookupTable (int maxEntries) const
{
  int numEntries = jmax (m_data->getNumColourStops (), m_data->getNumAlphaStops ());

  //
  // Calc minimum number of entries required for accuracy
  //

  for (int i = 0; i < m_data->getNumColourStops () - 1; ++i)
  {
    ColourStop const& c0 = m_data->getColourStop (0);
    ColourStop const& c1 = m_data->getColourStop (1);

    int const delta = (jmax (
      abs (c0.colour.getRed () - c1.colour.getRed ()),
      abs (c0.colour.getGreen () - c1.colour.getGreen ()),
      abs (c0.colour.getBlue () - c1.colour.getBlue ())) + 1) / 2;

    {
      float const width = c0.center * (c1.position - c0.position);

      numEntries = jmax (numEntries, int ((1.f / width) * delta + 0.5));
    }

    {
      float const width = (1 - c0.center) * (c1.position - c0.position);

      numEntries = jmax (numEntries, int ((1.f / width) * delta + 0.5));
    }
  }

  for (int i = 0; i < m_data->getNumAlphaStops () - 1; ++i)
  {
    AlphaStop const& a0 = m_data->getAlphaStop (0);
    AlphaStop const& a1 = m_data->getAlphaStop (1);

    int const delta = (int (abs (a1.alpha - a0.alpha) * 255 + 0.5) + 1) / 2;

    {
      float const width = a0.center * (a1.position - a0.position);

      numEntries = jmax (numEntries, int ((1.f / width) * delta + 0.5));
    }

    {
      float const width = (1 - a0.center) * (a1.position - a0.position);

      numEntries = jmax (numEntries, int ((1.f / width) * delta + 0.5));
    }
  }

  if (maxEntries != -1 && numEntries > maxEntries)
    numEntries = maxEntries;

  SharedTable <Colour> table (numEntries);

  //
  // Write colours
  //

  {
    ColourStop pad;
    ColourStop const* thisStop;
    ColourStop const* nextStop;

    thisStop = &m_data->getColourStop (0);

    if (thisStop->position > 0)
    {
      nextStop = thisStop;
      thisStop = &pad;

      pad = ColourStop (nextStop->colour, 0, 0.5);
    }
    else
    {
      nextStop = &m_data->getColourStop (1);
    }

    jassert (nextStop->position > thisStop->position);

    float width;

    width = nextStop->position - thisStop->position;

    for (int i = 0; i < numEntries; ++i)
    {
      float const pos = float (i) / (numEntries - 1);

      if (pos >= nextStop->position)
      {
        do
        {
          thisStop = nextStop;

          if (thisStop != &m_data->getColourStop (m_data->getNumColourStops () - 1))
          {
            ++nextStop;
          }
          else
          {
            pad = ColourStop (thisStop->colour, 2, 0.5);
            nextStop = &pad;
          }

          jassert (nextStop->position > thisStop->position);
        }
        while (pos >= nextStop->position);

        width = nextStop->position - thisStop->position;
      }

      float const amount = (pos - thisStop->position) / width;

      table [i] = interpolatedColour (
        thisStop->colour,
        nextStop->colour,
        transfer (amount, thisStop->center));
    }
  }

  //
  // Write alphas
  //

  {
    AlphaStop pad;
    AlphaStop const* thisStop;
    AlphaStop const* nextStop;

    thisStop = &m_data->getAlphaStop (0);

    if (thisStop->position > 0)
    {
      nextStop = thisStop;
      thisStop = &pad;

      pad = AlphaStop (nextStop->alpha, 0, 0.5);
    }
    else
    {
      nextStop = &m_data->getAlphaStop (1);
    }

    jassert (nextStop->position > thisStop->position);

    float width;

    width = nextStop->position - thisStop->position;

    for (int i = 0; i < numEntries; ++i)
    {
      float const pos = float (i) / (numEntries - 1);

      if (pos >= nextStop->position)
      {
        do
        {
          thisStop = nextStop;

          if (thisStop != &m_data->getAlphaStop (m_data->getNumAlphaStops () - 1))
          {
            ++nextStop;
          }
          else
          {
            pad = AlphaStop (thisStop->alpha, 2, 0.5);
            nextStop = &pad;
          }

          jassert (nextStop->position > thisStop->position);
        }
        while (pos >= nextStop->position);

        width = nextStop->position - thisStop->position;
      }

      float const amount = (pos - thisStop->position) / width;

      table [i] = table [i].withAlpha (
        thisStop->alpha + transfer (amount, thisStop->center) * (nextStop->alpha - thisStop->alpha));
    }
  }

  return table;
}
