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

class MetronomeImp : public Metronome
{
private:
  double m_sampleRate;
  double m_tempo;
  double m_phase;
  bool m_active;
  Synthesiser m_synth;
  MidiBuffer m_midi;

public:
  MetronomeImp (void const* audioData, int dataBytes)
    : m_sampleRate (44100)
    , m_tempo (120)
    , m_phase (0)
    , m_active (false)
  {
    m_synth.setNoteStealingEnabled (true);

    setTickSample (audioData, dataBytes);
  }

  ~MetronomeImp ()
  {
  }

  void setTickSample (void const* audioData, int dataBytes)
  {
    ScopedPointer <MemoryInputStream> mis (new MemoryInputStream (audioData, dataBytes, false));

    m_synth.clearVoices ();
    m_synth.clearSounds ();

    AudioFormatManager afm;
    afm.registerBasicFormats ();
    
    {
      ScopedPointer <AudioFormatReader> afr (afm.createReaderFor (mis));

      if (afr != nullptr)
      {
        mis.release ();

        BigInteger midiNotes;
        midiNotes.setRange (0, 127, true);

        SynthesiserSound::Ptr sound = new SamplerSound (
          "Tick",
          *afr,
          midiNotes,
          60,
          0,
          0,
          60./40.);

        m_synth.addSound (sound);
        m_synth.addVoice (new SamplerVoice);
      }
    }

  }

  void updateClock (double tempo, double phase, bool active)
  {
    m_tempo = tempo;
    m_phase = phase;
    m_active = active;
  }

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate)
  {
    m_sampleRate = sampleRate;

    m_synth.setCurrentPlaybackSampleRate (sampleRate);
  }

  void releaseResources ()
  {
  }

  void getNextAudioBlock (AudioSourceChannelInfo const& bufferToFill)
  {
    int const numSamples = bufferToFill.numSamples;

    // the synth always adds its output
    //bufferToFill.clearActiveBufferRegion();

    m_midi.clear ();

    if (m_active)
    {
      double const samplesPerBeat = m_sampleRate * 60 / m_tempo;

      // Adjust phase so the beat is on or after the beginning of the output
      double beat;
      if (m_phase > 0)
        beat = 1 - m_phase;
      else
        beat = 0 - m_phase;

      // Set notes in midi buffer
      for (;;beat += 1)
      {
        // Calc beat pos
        int pos = static_cast <int> (beat * samplesPerBeat);

        if (pos < numSamples)
        {
          m_midi.addEvent (MidiMessage::noteOn (1, 84, 1.f), pos);
        }
        else
        {
          break;
        }
      }
    }

    m_synth.renderNextBlock (*bufferToFill.buffer,
                            m_midi,
                            0,
                            bufferToFill.numSamples);
  }
};

Metronome* Metronome::New (void const* audioData, int dataBytes)
{
  return new MetronomeImp (audioData, dataBytes);
}
