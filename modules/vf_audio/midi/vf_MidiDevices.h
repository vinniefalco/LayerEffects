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

#ifndef VF_MIDIDEVICES_VFHEADER
#define VF_MIDIDEVICES_VFHEADER

/**
  Midi input and output device manager.

  This wraps JUCE support for Midi devices, with the following features:

  - Add/remove notification.

  - Midi input and output devices identified by a permanent handle.

*/
class MidiDevices : public ReferenceCountedSingleton <MidiDevices>
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
  friend class ReferenceCountedSingleton <MidiDevices>;

  MidiDevices () : ReferenceCountedSingleton <MidiDevices> (
    SingletonLifetime::persistAfterCreation)
  {
  }

  static MidiDevices* createInstance ();
};

#endif
