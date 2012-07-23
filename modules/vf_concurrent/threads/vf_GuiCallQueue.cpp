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

GuiCallQueue::GuiCallQueue ()
  : CallQueue ("GuiCallQueue")
  , m_thread ("GuiCallQueue")
{
  // This object must be created from the Juce Message Thread.
  //
  jassert (MessageManager::getInstance()->isThisTheMessageThread());

  // Associate the CallQueue with the message thread right away.
  //
  synchronize ();

  m_thread.start ();
}

void GuiCallQueue::close ()
{
  m_thread.stop (true);

  CallQueue::close ();
}

bool GuiCallQueue::synchronize ()
{
  return CallQueue::synchronize ();
}

void GuiCallQueue::signal ()
{
  m_thread.call (&AsyncUpdater::triggerAsyncUpdate, (AsyncUpdater*)this);
}

void GuiCallQueue::reset ()
{
}

void GuiCallQueue::handleAsyncUpdate()
{
  synchronize ();

  //updateAllTopLevelWindows ();
}
