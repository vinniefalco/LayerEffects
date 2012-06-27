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
