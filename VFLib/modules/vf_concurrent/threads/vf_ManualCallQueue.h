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

#ifndef VF_MANUALCALLQUEUE_VFHEADER
#define VF_MANUALCALLQUEUE_VFHEADER

/*============================================================================*/
/**
    A CallQueue that requires periodic manual synchronization.

    To use this, declare an instance and then place calls into it as usual.
    Every so often, you must call synchronize() from the thread you want to
    associate with the queue. Typically this is done within an
    AudioIODeviceCallback:

    @code

    class AudioIODeviceCallbackWithCallQueue
      : public AudioIODeviceCallback
      , public CallQueue
    {
    public:
      AudioIODeviceCallbackWithCallQueue () : m_fifo ("Audio CallQueue")
      {
      }

      void audioDeviceIOCallback (const float** inputChannelData,
							      int numInputChannels,
							      float** outputChannelData,
							      int numOutputChannels,
							      int numSamples)
      {
	    CallQueue::synchronize ();

	    // do audio i/o
      }

      void signal () { } // No action required
      void reset () { }  // No action required
    };

    @endcode

	The close() function is provided for diagnostics. Call it as early as
	possible based on the exit or shutdown logic of your application. If calls
    are put into the queue after it is closed, it will generate an exception so
    you can track it down.

    @see CallQueue

    @ingroup vf_concurrent
*/
class ManualCallQueue : public CallQueue
{
public:
  /** Create a ManualCallQueue.

	  @param name           A string used to help identify the associated
                            thread for debugging.
  */
  explicit ManualCallQueue (String name);

  /** Close the queue. If calls are placed into a closed queue, an exception
	  is thrown.
  */
  void close ();

  /** Synchronize the queue by calling all pending functors.
  
      @return \c true if any functors were called.
  */
  bool synchronize ();

private:
  void signal ();
  void reset ();
};

#endif
