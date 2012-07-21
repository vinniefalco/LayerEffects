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

/** Include this to get the @ref vf_audio module.

    @file vf_audio.h
    @ingroup vf_audio
*/

#ifndef VF_AUDIO_VFHEADER
#define VF_AUDIO_VFHEADER

/*============================================================================*/
/**
    Audio signal processing utilities.

    This is a small collection of classes for performing audio signal
    processing.

    @defgroup vf_audio vf_audio
*/

#include "modules/juce_audio_basics/juce_audio_basics.h"
#include "modules/juce_audio_devices/juce_audio_devices.h"

#include "../vf_core/vf_core.h"
#include "../vf_concurrent/vf_concurrent.h"

namespace vf
{

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4100)
#endif

#include "buffers/vf_AudioBufferPool.h"
#include "buffers/vf_AudioSampleBufferArray.h"
#include "buffers/vf_ScopedAudioSampleBuffer.h"

#include "midi/vf_MidiInput.h"
#include "midi/vf_MidiDevices.h"

#include "sources/vf_Metronome.h"
#include "sources/vf_NoiseAudioSource.h"
#include "sources/vf_SampleSource.h"
#include "sources/vf_SeekingSampleSource.h"
#include "sources/vf_SeekingAudioSource.h"

#ifdef _MSC_VER
#pragma warning (pop)
#endif

}

#endif
