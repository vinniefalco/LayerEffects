//------------------------------------------------------------------------------
/*
  LayerEffects for JUCE

  Official project location:
  https://github.com/vinniefalco/LayerEffects

  ------------------------------------------------------------------------------

  License: MIT License (http://www.opensource.org/licenses/mit-license.php)
  Copyright (c) 2012 by Vinnie Falco

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
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
//------------------------------------------------------------------------------

BackgroundThread::BackgroundThread ()
  : m_thread ("BackgroundThread")
{
  m_thread.start (this);
}

BackgroundThread::~BackgroundThread ()
{
  m_thread.stop (true);
}

void BackgroundThread::addListener (Listener* listener, vf::CallQueue& thread)
{
  SharedState::ReadAccess state (m_state);

  m_listeners.add (listener, thread);

  m_listeners.queue1 (listener, &Listener::onImageReady, state->image);
}

void BackgroundThread::removeListener (Listener* listener)
{
  m_listeners.remove (listener);
}

void BackgroundThread::changeSettings (Settings settings)
{
  m_thread.call (&BackgroundThread::changeSettingsAsync, this, settings);
}

void BackgroundThread::changeSettingsAsync (Settings settings)
{
  m_settings = settings;
}

bool BackgroundThread::threadIdle ()
{
  bool interrupted = false;

  if (! m_settings.backgroundImage.isNull ())
  {
    Rectangle <int> const bounds (
      0,
      0,
      m_settings.backgroundImage.getWidth (), 
      m_settings.backgroundImage.getHeight ());

    Image result (Image::RGB, bounds.getWidth (), bounds.getHeight (), false);

    {
      Graphics g (result);

      g.drawImageAt (m_settings.backgroundImage, 0, 0);

      vf::LayerGraphics lc (g, bounds);

      lc.getOptions () = m_settings.options;

      lc.drawImageAt (m_settings.foregroundImage, 0, 0);
    }

    m_listeners.call (&Listener::onImageReady, result);
  }

  return interrupted;
}
