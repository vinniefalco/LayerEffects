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

#ifndef VF_LAYERCONTEXT_VFHEADER
#define VF_LAYERCONTEXT_VFHEADER

/** Graphics context for a compositing layer.

    This allows an Image to be composited into a BackgroundContext.

    @ingroup vf_gui
*/
class LayerContext : public ContextImageBase, public Graphics
{
public:
  struct Options
  {
    //----

    struct General
    {
      General ()
        : opacity (1)
        , red (true)
        , green (true)
        , blue (true)
      {
      }

      double    opacity;                // [0, 1] of fill
      bool      red;                    // true to copy these channels
      bool      green;
      bool      blue;
    };

    //----

    struct Fill
    {
      Fill ()
        : mode (normal)
        , opacity (1)
      {
      }

      BlendMode mode;
      double opacity;                   // [0, 1] overall
    };

    //----

    struct DropShadow
    {
      DropShadow ()
        : active (false)
        , mode (normal)
        , opacity (1)
        , colour (Colours::black)
        , angle (0)
        , distance (1)
        , spread (0)
        , size (1)
        , knockout (true)
      {
      }

      bool      active;
      BlendMode mode;
      double    opacity;
      Colour    colour;                 // can have alpha
      double    angle;                  // radians
      int       distance;               // [0, 30000]
      double    spread;                 // [0, 1]
      int       size;                   // in pixels
      bool      knockout;               // layer mask knocks out drop shadow
    };

    //----

    struct InnerShadow
    {
      InnerShadow ()
        : active (false)
        , mode (normal)
        , colour (Colours::black)
        , angle (0)
        , distance (1)
        , choke (0)
        , size (1)
      {
      }

      bool      active;
      BlendMode mode;
      double    opacity;
      Colour    colour;                 // can have alpha
      double    angle;                  // radians
      int       distance;               // [0, 30000]
      double    choke;                  // [0, 1]
      int       size;                   // in pixels
    };

    //----

    General       general;
    Fill          fill;
    DropShadow    dropShadow;
    InnerShadow   innerShadow;
  };

public:
  LayerContext (BackgroundContext& destinationContext,
                Rectangle <int> const& drawBounds);

  ~LayerContext ();

  Options& getOptions ();

private:
  void applyDropShadow (Image& destImage);

  void applyInnerShadow (Image& destImage);

  void applyFill (Image& destImage);

private:
  BackgroundContext& m_destinationContext;
  Options m_options;
};

#endif
