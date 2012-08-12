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

#ifndef VF_BEVELEMBOSSSTYLE_VFHEADER
#define VF_BEVELEMBOSSSTYLE_VFHEADER

/** Provides the Bevel and Emboss layer style.

    @ingroup vf_gui
*/
struct BevelEmbossStyle
{
  enum Kind
  {
    kindOuterBevel = 1,
    kindInnerBevel,
    kindEmboss,
    kindPillowEmboss,
    kindStrokeEmboss
  };

  enum Technique
  {
    techniqueSmooth = 1,
    techniqueChiselHard,
    techniqueChiselSoft
  };

  bool            active;
  Kind            kind;
  Technique       technique;
  double          depth;          // [0, 10], 1 = 100%
  int             size;           // [0, 250]
  int             soften;         // [0, 16]
  double          lightAngle;     // radians
  double          lightElevation; // radians
  BlendMode::Type hilightMode;
  double          hilightOpacity;
  Colour          hilightColour;
  BlendMode::Type shadowMode;
  double          shadowOpacity;
  Colour          shadowColour;

  BevelEmbossStyle () : active (false)
  {
  }

  void operator() (Pixels destPixels, Pixels maskPixels);

  //----------------------------------------------------------------------------

  struct Normal
  {
    struct GetInner
    {
      explicit GetInner (Pixels src) : m_src (src)
      {
      }

      inline bool operator () (int const x, int const y) const noexcept
      {
        return *m_src.getPixelPointer (x, y) == 0;
      }

    private:
      Pixels m_src;
    };

    //--------------------------------------------------------------------------

    struct GetOuter
    {
      explicit GetOuter (Pixels src) : m_src (src)
      {
      }

      inline bool operator () (int const x, int const y) const noexcept
      {
        return *m_src.getPixelPointer (x, y) != 0;
      }

    private:
      Pixels m_src;
    };

    //--------------------------------------------------------------------------

    template <class Map>
    struct OutputOuter
    {
      typedef typename Map::Type Type;

      OutputOuter (Map map, int radius)
        : m_map (map)
        , m_radius (radius)
        , m_radiusSquared (radius * radius)
      {
      }

      template <class T>
      void operator () (int const x, int const y, T distance)
      {
        if (distance > 0)
        {
          if (distance < m_radiusSquared)
            m_map (x, y) = Type (std::sqrt (double (distance)));
          else
            m_map (x, y) = Type (m_radius);
        }
        else
        {
          m_map (x, y) = 0;
        }
      }

    private:
      Map m_map;
      int m_radius;
      int m_radiusSquared;
    };

    //--------------------------------------------------------------------------

    template <class Map>
    struct OutputInner
    {
      typedef typename Map::Type Type;

      OutputInner (Map map, int radius)
        : m_map (map)
        , m_radius (radius)
        , m_radiusSquared (radius * radius)
      {
      }

      template <class T>
      void operator () (int const x, int const y, T distance)
      {
        if (distance <= m_radiusSquared && distance > 0)
          m_map (x, y) = m_radius - Type (std::sqrt (double (distance)));
        else
          m_map (x, y) = 0;
      }

    private:
      Map m_map;
      Type m_radius;
      Type m_radiusSquared;
    };
  };

  //----------------------------------------------------------------------------

  struct AntiAliased
  {
    struct GetMaskInner
    {
      explicit GetMaskInner (Pixels mask) : m_mask (mask)
      {
      }

      // Return distance from point of interest.
      //
      // 0      = point of interest
      // 1..254 = fractional distance to point of interest
      // 255    = not a point of interest
      //
      int operator() (int x, int y) const noexcept
      {
        return *m_mask.getPixelPointer (x, y);
      }

    public:
      Pixels m_mask;
    };

    //--------------------------------------------------------------------------

    struct GetMaskOuter
    {
      explicit GetMaskOuter (Pixels mask) : m_mask (mask)
      {
      }

      // Return distance from point of interest.
      //
      // 0      = point of interest
      // 1..254 = fractional distance to point of interest
      // 255    = not a point of interest
      //
      int operator() (int x, int y) const noexcept
      {
        return 255 - *m_mask.getPixelPointer (x, y);
      }

    public:
      Pixels m_mask;
    };

    //--------------------------------------------------------------------------

    template <class Map>
    struct OutputOuter
    {
      typedef typename Map::Type Type;

      OutputOuter (Map map, int radius)
        : m_map (map)
        , m_radius (radius)
        , m_radiusSquared (65536L * radius * radius)
      {
      }

      template <class T>
      void operator () (int const x, int const y, T distanceSquared)
      {
        if (distanceSquared > 0 && distanceSquared < m_radiusSquared)
        {
          double dist = std::sqrt (double (distanceSquared / 65536));
          m_map (x, y) = dist;
        }
        else
        {
          m_map (x, y) = 0;
        }
      }

    private:
      Map m_map;
      int m_radius;
      int64 m_radiusSquared;
    };

  };
};

#endif
