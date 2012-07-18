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

      double  opacity;                  // [0, 1] of fill
      bool    red;                      // true to copy these channels
      bool    green;
      bool    blue;
    };

    //----

    struct Fill
    {
      Fill ()
        : mode (normal)
        , opacity (1)
      {
      }

      BlendMode mode;                   // blend mode overall
      double opacity;                   // [0, 1] overall
    };

    //----

    struct DropShadow
    {
      DropShadow ()
        : active (false)
        , mode (normal)
        , opacity (1)
        , angle (0)
        , distance (1)
        , spread (0)
        , size (1)
        , knockout (true)
      {
      }

      bool      active;
      BlendMode mode;
      double    opacity;                // [0, 1]
      double    angle;                  // radians
      int       distance;               // [0, 30000]
      double    spread;                 // [0, 1]
      int       size;                   // in pixels
      bool      knockout;               // layer mask knocks out drop shadow
    };

    General       general;
    Fill          fill;
    DropShadow    dropShadow;
  };

public:
  LayerContext (BackgroundContext& destinationContext,
                Rectangle <int> const& drawBounds);

  ~LayerContext ();

  Options& getOptions ();

private:
  void applyDropShadow ();

  void applyFill ();

private:
  BackgroundContext& m_destinationContext;
  Options m_options;
};

#endif
