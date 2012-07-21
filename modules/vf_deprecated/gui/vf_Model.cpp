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

namespace Ui {

namespace Model {

/*
void Listener::onModelChanged (Base* model)
{
}

void Listener::onModelEnablement (Base* model, bool enabled)
{
}
*/

//------------------------------------------------------------------------------

Base::Base ()
  : m_enabled (true)
{
}

Base::~Base ()
{
  jassert (m_views.size()==0); // someone forgot to remove themselves?
}

void Base::addListener (ListenerBase* const listener)
{
  m_listeners.add (listener);
}

void Base::removeListener (ListenerBase* const listener)
{
  m_listeners.remove (listener);
}

bool Base::isEnabled ()
{
  return m_enabled;
}

const String Base::getName ()
{
  return String::empty;
}

void Base::addView (Control::View* view)
{
  if (!m_views.contains (view))
  {
    m_views.add (view);
    view->updateView();
  }
}

void Model::Base::removeView (Control::View* view)
{
  const int index = m_views.indexOf (view);
  if (index >= 0)
    m_views.remove (index);
}

void Model::Base::updateAllViews ()
{
  for (int i = m_views.size(); --i >= 0;)
  {
    m_views.getUnchecked (i)->updateView();
    i = jmin (i, m_views.size());
  }
}

void Model::Base::modelChanged ()
{
  m_listeners.call (&Listener::onModelChanged, (Model::Base*)this);
}

void Model::Base::setEnabled (bool enabled)
{
  if (m_enabled != enabled)
  {
    m_enabled = enabled;

    m_listeners.call (&Listener::onModelEnablement, this);
  }
}

}

}
