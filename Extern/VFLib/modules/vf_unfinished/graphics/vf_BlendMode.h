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

#ifndef VF_BLENDMODE_VFHEADER
#define VF_BLENDMODE_VFHEADER

namespace BlendMode
{
  enum Type
  {
    modeNormal = 1,   // Must come first, cannot be zero.
    modeLighten,
    modeDarken,
    modeMultiply,
    modeAverage,
    modeAdd,
    modeSubtract,
    modeDifference,
    modeNegation,
    modeScreen,
    modeExclusion,
    modeOverlay,
    modeSoftLight,
    modeHardLight,
    modeColorDodge,
    modeColorBurn,
    modeLinearDodge,
    modeLinearBurn,
    modeLinearLight,
    modeVividLight,
    modePinLight,
    modeHardMix,
    modeReflect,
    modeGlow,
    modePhoenix,


    modeLast      // Reserved, do not use.
  };

  /** Return the number of available blend modes.
  */
  inline int getNumModes ()
  {
    return modeLast - modeNormal;
  }

  /** Retrieve an indexed blend mode.
  */
  Type getMode (int index);

  /** Retrieve the localized display name of a blend mode.
  */
  String getName (Type);

  /** Blending mode functors.

      Each functor calculates the resulting colour component intensity from the
      foreground and background colour component intensities.
      
      These replicate the Photoshop layer blending modes.

      See: http://inlandstudios.com/en/?p=851

      @param f Foreground colour component intensity.
      @param b Background colour component intensity.

      @ingroup vf_gui
  */
  /** @{ */
  struct normal
  {
    inline int operator () (int f, int) const
    {
      return f;
    }
  };

  struct lighten
  {
    inline int operator () (int f, int b) const
    {
      return (f > b) ? f : b;
    }
  };

  struct darken
  {
    inline int operator () (int f, int b) const
    {
      return (f < b) ? f : b;
    }
  };

  struct multiply
  {
    inline int operator () (int f, int b) const
    {
      return f * b / 255;
    }
  };

  struct average
  {
    inline int operator () (int f, int b) const
    {
      return (f + b) / 2;
    }
  };

  struct add
  {
    inline int operator () (int f, int b) const
    {
      return std::min (255, f + b);
    }
  };

  struct subtract
  {
    inline int operator () (int f, int b) const
    {
      return (f > b) ? 0 : (b - f);
    }
  };

  struct difference
  {
    inline int operator () (int f, int b) const
    {
      return std::abs (f - b);
    }
  };

  struct negation
  {
    inline int operator () (int f, int b) const
    {
      return 255 - std::abs (255 - f - b);
    }
  };

  struct screen
  {
    inline int operator () (int f, int b) const
    {
      return 255 - (((255 - f) * (255 - b)) / 255);
    }
  };

  struct exclusion
  {
    inline int operator () (int f, int b) const
    {
      return (f + b - 2 * f * b / 255);
    }
  };

  struct overlay
  {
    inline int operator () (int f, int b) const
    {
      return (b < 128) ? (2 * f * b / 255) : (255 - 2 * (255 - f) * (255 - b) / 255);
    }
  };

  struct softLight
  {
    inline int operator () (int f, int b) const
    {
      return int ((b < 128) ?
        (2 * ((f >> 1) + 64)) * ((float)b / 255) :
        (255 - (2 * (255 - ((f >> 1) + 64)) * (float)(255 - b) / 255)));
    }
  };

  struct hardLight
  {
    inline int operator () (int f, int b) const
    {
      return overlay () (f, b);
    }
  };

  struct colorDodge
  {
    inline int operator () (int f, int b) const
    {
      return (f == 255) ? f : std::min (255, (b << 8) / (255 - f));
    }
  };

  struct colorBurn
  {
    inline int operator () (int f, int b) const
    {
      return (b == 0) ? 0 : std::max (0, (255 - ((255 - f) << 8) / b));
    }
  };

  struct linearDodge
  {
    inline int operator () (int f, int b) const
    {
      return add () (f, b);
    }
  };

  struct linearBurn
  {
    inline int operator () (int f, int b) const
    {
      return subtract () (f, b);
    }
  };

  struct linearLight
  {
    inline int operator () (int f, int b) const
    {
        return (f < 128) ?
          linearBurn () (256 - b, 2 * f) :
          linearDodge () (b, 2 * (f - 128));
    }
  };

  struct vividLight
  {
    inline int operator () (int f, int b) const
    {
      return (b < 128) ?
        colorBurn () (f, 2 * b) :
        colorDodge () (f, 2 * (b - 128));
    }
  };

  struct pinLight
  {
    inline int operator () (int f, int b) const
    {
      return (f < 128) ?
        darken () (b, 2 * f) :
        lighten () (b, 2 * (f - 128));
    }
  };

  struct hardMix
  {
    inline int operator () (int f, int b) const
    {
      return (vividLight () (f, b) < 128) ? 0 : 255;
    }
  };

  struct reflect
  {
    inline int operator () (int f, int b) const
    {
      return (b == 255) ? 255 : std::min (255, f * f / (255 - b));
    }
  };

  struct glow
  {
    inline int operator () (int f, int b) const
    {
      return reflect () (b, f);
    }
  };

  struct phoenix
  {
    inline int operator () (int f, int b) const
    {
      return std::min (f, b) - std::max (f, b) + 255;
    }
  };

  struct dissolve
  {
    inline int operator () (int f, int) const
    {
      return f;
    }
  };

  /** @} */

  //----------------------------------------------------------------------------

  // convert 3 argument to 2 argument
  template <class Functor, class ModeType>
  struct Helper
  {
    explicit Helper (Functor f, ModeType mode = ModeType ())
      : m_f (f)
      , m_mode (mode)
    {
    }

    template <class T1>
    void operator () (T1 t1)
    {
      m_f (m_mode, t1);
    }

    template <class T1, class T2>
    void operator () (T1 t1, T2 t2)
    {
      m_f (m_mode, t1, t2);
    }

    template <class T1, class T2, class T3>
    void operator () (T1 t1, T2 t2, T3 t3)
    {
      m_f (m_mode, t1, t2, t3);
    }

  private:
    Functor m_f;
    ModeType m_mode;
  };

  /** Call a functor with a blend mode from the enumeration.
  */
  template <class Iterator, class Functor>
  void apply (Type mode, Iterator iter, Functor f)
  {
    switch (mode)
    {
    case modeNormal:      iter (Helper <Functor, normal> (f)); break;
    case modeLighten:     iter (Helper <Functor, lighten> (f)); break;
    case modeDarken:      iter (Helper <Functor, darken> (f)); break;
    case modeMultiply:    iter (Helper <Functor, multiply> (f)); break;
    case modeAverage:     iter (Helper <Functor, average> (f)); break;
    case modeAdd:         iter (Helper <Functor, add> (f)); break;
    case modeSubtract:    iter (Helper <Functor, subtract> (f)); break;
    case modeDifference:  iter (Helper <Functor, difference> (f)); break;
    case modeNegation:    iter (Helper <Functor, negation> (f)); break;
    case modeScreen:      iter (Helper <Functor, screen> (f)); break;
    case modeExclusion:   iter (Helper <Functor, exclusion> (f)); break;
    case modeOverlay:     iter (Helper <Functor, overlay> (f)); break;
    case modeSoftLight:   iter (Helper <Functor, softLight> (f)); break;
    case modeHardLight:   iter (Helper <Functor, hardLight> (f)); break;
    case modeColorDodge:  iter (Helper <Functor, colorDodge> (f)); break;
    case modeColorBurn:   iter (Helper <Functor, colorBurn> (f)); break;
    case modeLinearDodge: iter (Helper <Functor, linearDodge> (f)); break;
    case modeLinearBurn:  iter (Helper <Functor, linearBurn> (f)); break;
    case modeLinearLight: iter (Helper <Functor, linearLight> (f)); break;
    case modeVividLight:  iter (Helper <Functor, vividLight> (f)); break;
    case modePinLight:    iter (Helper <Functor, pinLight> (f)); break;
    case modeHardMix:     iter (Helper <Functor, hardMix> (f)); break;
    case modeReflect:     iter (Helper <Functor, reflect> (f)); break;
    case modeGlow:        iter (Helper <Functor, glow> (f)); break;
    case modePhoenix:     iter (Helper <Functor, phoenix> (f)); break;
    default:
      jassertfalse;
      break;
    }
  }
}

#endif
