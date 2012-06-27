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

#ifndef VF_MESSAGETHREAD_VFHEADER
#define VF_MESSAGETHREAD_VFHEADER

/*============================================================================*/
/**
  A GuiCallQueue singleton for the message thread.

  This convenient singleton lets you easily provide a CallQueue for
  synchronizing on the message thread (the thread of execution that operates
  the Graphical User Interface / GUI). The `getInstance()` member provides
  the a GuiCallQueue:

  @code

  void performedOnMessageThread ()
  {
  }

  MessageThread::getInstance().call (&performedOnMessageThread);

  @endcode

  When the JUCE application terminates, or when the JUCE GUI is shutdown,
  the MessageThread object will be automatically cleaned up, no further action
  is required.

  @ingroup vf_concurrent
*/
class MessageThread
  : public GuiCallQueue
  , private DeletedAtShutdown
  , LeakChecked <MessageThread>
{
public:
  /* This is not thread safe nor does it need to be, since by
     definition we are only operating on the message thread.
  */
  static MessageThread& getInstance ();

private:
  MessageThread ();
  ~MessageThread ();
};

#endif
