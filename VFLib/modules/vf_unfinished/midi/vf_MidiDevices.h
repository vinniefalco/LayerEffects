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

#ifndef VF_MIDIDEVICES_VFHEADER
#define VF_MIDIDEVICES_VFHEADER

/**
  Midi input and output device manager.

  This wraps JUCE support for Midi devices, with the following features:

  - Add/remove notification.

  - Midi input and output devices identified by a permanent handle.

*/
class MidiDevices : public RefCountedSingleton <MidiDevices>
{
public:
  /**
    Common Midi device characteristics.
  */
  class Device
  {
  public:
    virtual String getName () const = 0;
  };

  /**
    An input device.
  */
  class Input : public Device
  {
  public:
  };

  /**
    An output device.
  */
  class Output : public Device
  {
  public:
  };

public:
  struct Listener
  {
    /**
      Called when the connection status of a device changes.
    */
    virtual void onMidiDevicesStatus (Device* device, bool isConnected) { }

    /**
      Called when the connection status of any devices changes.

      This is usually a good opportunity to rebuild user interface lists.
    */
    virtual void onMidiDevicesChanged () { }
  };

  /**
    Add a device notification listener.
  */
  virtual void addListener (Listener* listener, CallQueue& thread) = 0;

  /**
    Remove a device notification listener.
  */
  virtual void removeListener (Listener* listener) = 0;

protected:
  friend class RefCountedSingleton <MidiDevices>;

  MidiDevices () : RefCountedSingleton <MidiDevices> (
    SingletonLifetime::persistAfterCreation)
  {
  }

  static MidiDevices* createInstance ();
};

#endif
