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

#ifndef VF_GUICALLQUEUE_VFHEADER
#define VF_GUICALLQUEUE_VFHEADER

/*============================================================================*/
/** 
  A CallQueue handled by the Juce message thread (gui).

  A singleton instance of GuiCallQueue is provided as MessageThread. Or
  you can use this one. To use this, put an instance of the class in your
  application object or other central location. Calls placed in the queue will
  automatically get processed by the Juce message loop, no further action is
  required to make it work.

  @see MessageThread

  @ingroup vf_concurrent
*/
class GuiCallQueue
  : public CallQueue
  , private AsyncUpdater
{
public:
  /** Create a GuiCallQueue */
  GuiCallQueue ();

  /** Close the GuiCallQueue.

      This function is for diagnostics, to detect improper usage where calls
      are placed in the queue that can never be processed (since the
      application is exiting).
  */
  void close ();

  /** Synchronize the queue.

      This can be called manually if needed.

      @return \c true if any functors were called.
  */
  bool synchronize ();

private:
  void signal ();
  void reset ();
  void handleAsyncUpdate ();

  ThreadWithCallQueue m_thread;
};

#endif
