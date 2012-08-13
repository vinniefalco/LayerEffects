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

/** Add this to get the @ref vf_unfinished module.

    @file vf_unfinished.cpp
    @ingroup vf_unfinished
*/

#include "AppConfig.h"

#include "vf_unfinished.h"

#if JUCE_MSVC
#pragma warning (push)
//#pragma warning (disable: 4100) // unreferenced formal parmaeter
//#pragma warning (disable: 4355) // 'this' used in base member
#endif

namespace vf
{

#include "graphics/vf_BevelEmbossStyle.cpp"
#include "graphics/vf_BlendMode.cpp"
#include "graphics/vf_BlendProc.cpp"
#include "graphics/vf_DistanceTransform.cpp"
#include "graphics/vf_ColourOverlayStyle.cpp"
#include "graphics/vf_DropShadowStyle.cpp"
#include "graphics/vf_FillStyle.cpp"
#include "graphics/vf_GradientColours.cpp"
#include "graphics/vf_GradientOverlayStyle.cpp"
#include "graphics/vf_InnerGlowStyle.cpp"
#include "graphics/vf_InnerShadowStyle.cpp"
#include "graphics/vf_OuterGlowStyle.cpp"
#include "graphics/vf_PatternOverlayStyle.cpp"
#include "graphics/vf_StrokeStyle.cpp"
#include "graphics/vf_LayerGraphics.cpp"
#include "graphics/vf_Pixels.cpp"

#include "midi/vf_MidiDevices.cpp"
#include "midi/vf_MidiInput.cpp"

}

#if JUCE_MSVC
#pragma warning (pop)
#endif
