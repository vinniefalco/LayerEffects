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

/** Include this to get the @ref vf_unfinished module.

    @file vf_unfinished.h
    @ingroup vf_unfinished
*/

#ifndef VF_UNFINISHED_VFHEADER
#define VF_UNFINISHED_VFHEADER

/*============================================================================*/
/**
  Work in progress.

  This module contains unfinished code.

  @defgroup vf_unfinished vf_unfinished
*/

#include "modules/juce_audio_basics/juce_audio_basics.h"
#include "modules/juce_audio_devices/juce_audio_devices.h"
#include "modules/juce_gui_basics/juce_gui_basics.h"

#include "../vf_core/vf_core.h"
#include "../vf_concurrent/vf_concurrent.h"
#include "../vf_gui/vf_gui.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parameter
//#pragma warning (disable: 4355) // 'this' : used in base member initializer list
#endif

namespace vf
{

#include "graphics/vf_BlendMode.h"
#include "graphics/vf_BlendProc.h"
#include "graphics/vf_Pixels.h"
#include "graphics/vf_DistanceTransform.h"
#include "graphics/vf_LightingTransform.h"
#include "graphics/vf_GradientColours.h"
#include "graphics/vf_BevelEmbossStyle.h"
#include "graphics/vf_ColourOverlayStyle.h"
#include "graphics/vf_DropShadowStyle.h"
#include "graphics/vf_FillStyle.h"
#include "graphics/vf_GradientOverlayStyle.h"
#include "graphics/vf_InnerGlowStyle.h"
#include "graphics/vf_InnerShadowStyle.h"
#include "graphics/vf_OuterGlowStyle.h"
#include "graphics/vf_PatternOverlayStyle.h"
#include "graphics/vf_StrokeStyle.h"
#include "graphics/vf_LayerGraphics.h"

#include "midi/vf_MidiInput.h"
#include "midi/vf_MidiDevices.h"

}

#if JUCE_MSVC
#pragma warning (pop)
#endif

#endif
