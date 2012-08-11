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

#ifndef VF_GRADIENTCOLOURS_VFHEADER
#define VF_GRADIENTCOLOURS_VFHEADER

/** Specifies a gradient ramp with colour and transparency stops.

    @ingroup vf_gui
*/
class GradientColours
{
public:
  static GradientColours const null;

  /** Creates a null gradient.
  */
  GradientColours ();

  /** Creates a gradient with the specified numbers of stops.

      The colour and alpha stops are uninitialized.

      If numAlphaStops is -1 then two alpha stops will be set automatically.
  */
  GradientColours (int numColourStops, int numAlphaStops = -1);

  /** Create a simple two colour gradient.
  */
  GradientColours (Colour startColour, Colour endColour);

  /** Create a shared reference to another gradient.
  */
  GradientColours (GradientColours const& other);

  /** Make this gradient refer to another gradient.
  */
  GradientColours& operator= (GradientColours const& other);

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
  GradientColours (GradientColours&& other) noexcept;
  GradientColours& operator= (GradientColours&& other) noexcept;
#endif

  /** Destructor.
  */
  ~GradientColours ();

  /** Returns true if the two gradients share the same set of colours.
  */
  bool operator== (GradientColours const& other) const noexcept
  {
    return m_data == other.m_data;
  }

  /** Returns true if the two gradients do not share the same set of colours.
  */
  bool operator!= (GradientColours const& other) const noexcept
  {
    return m_data != other.m_data;
  }

  /** Returns true if the gradient is not null.
  */
  inline bool isValid () const noexcept
  {
    return m_data != nullptr;
  }

  /** Returns true if the gradient is null.
  */
  inline bool isNull () const noexcept
  {
    return m_data == nullptr;
  }

  /** Returns a new set of colours with all alpha values scaled.
  */
  GradientColours withMultipliedAlpha (float alpha) const noexcept;

  /** Returns the number of gradients referring to the same shared colours.
  */
  int getReferenceCount () const noexcept;

  /** Create a physical duplicate of the gradient colours.
  */
  GradientColours createCopy () const;

  /** Makes sure no other gradients share the same colours as this gradient.
  */
  void duplicateIfShared ();

  /** Create a lookup table of colours from the gradient.

      The number of entries will be calculated to be as small as possible
      while still representing each possible colour and transparency value,
      up to the limit specified by maxEntries.

      @param maxEntries The largest number of entries, or -1 for no limit.
  */
  SharedTable <Colour> createLookupTable (int maxEntries = -1) const;

  struct AlphaStop
  {
    AlphaStop ()
    {
    }

    AlphaStop (float alpha_, float position_, float center_ = 0.5f)
      : alpha (alpha_), position (position_), center (center_)
    {
    }

    float alpha;
    float position;
    float center;         // [0.05, 0.95], 0.5 = linear, ignored for last stop.
  };

  /** Return the number of alpha stops in this gradient.
  */
  int getNumAlphaStops () const noexcept;

  /** Get a reference to an alpha stop.
  */
  AlphaStop& getAlphaStop (int index) const noexcept;

  struct ColourStop
  {
    ColourStop ()
    {
    }

    ColourStop (Colour colour_, float position_, float center_ = 0.5f)
      : colour (colour_), position (position_), center (center_)
    {
    }

    Colour colour;        // Alpha is ignored
    float position;
    float center;         // [0.05, 0.95], 0.5 = linear, ignored for last stop.
  };

  /** Return the number of colour stops in this gradient.
  */
  int getNumColourStops () const noexcept;

  /** Get a reference to a colourstop.
  */
  ColourStop& getColourStop (int index) const noexcept;

  /** Accurately interpolate a colour.

      This is a replacement for the corresponding JUCE function,
      which is inaccurate.
  */
  static inline Colour interpolatedColour (
    Colour const& startColour,
    Colour const& endColour,
    float amount) noexcept
  {
    return Colour (
      startColour.getRed ()   + uint8 (amount * (endColour.getRed ()   - startColour.getRed ()) + 0.5),
      startColour.getGreen () + uint8 (amount * (endColour.getGreen () - startColour.getGreen ()) + 0.5),
      startColour.getBlue ()  + uint8 (amount * (endColour.getBlue ()  - startColour.getBlue ()) + 0.5));
  }

private:
  static inline float transfer (float amount, float center) noexcept
  {
    if (amount <= center)
      return (amount / center) * 0.5f;
    else
      return 0.5f + (amount - center) / (2 * (1 - center));
  }

  class Data;

  explicit GradientColours (Data* data);

  ReferenceCountedObjectPtr <Data> m_data;
};

/** A nice set of builtin gradient colours.
*/
struct GradientPresets
{
  GradientPresets ();

  GradientColours spectrum;
};

#endif
