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
