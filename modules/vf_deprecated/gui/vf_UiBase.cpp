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

namespace Model {

Base::Base ()
  : m_enabled (true)
{
}

void Base::addListener (Model::Listener* const listener)
{
  m_listeners.add (listener);
}

void Base::removeListener (Model::Listener* const listener)
{
  m_listeners.remove (listener);
}

bool Base::isEnabled ()
{
  return m_enabled;
}

void Base::setEnabled (bool enabled)
{
  if (m_enabled != enabled)
  {
    m_enabled = enabled;
    m_listeners.call (&Model::Listener::onModelEnablement, this);
  }
}

void Base::modelChanged ()
{
  m_listeners.call (&Model::Listener::onModelChanged, this);
}

Model::Listeners <ListenerBase> const& Base::getListeners ()
{
  return m_listeners;
}

}

//------------------------------------------------------------------------------

namespace Facade {

void Base::paint (Graphics& g, Rectangle <int> const& bounds)
{
}

void Base::paintOverChildren (Graphics& g, Rectangle <int> const& bounds)
{
}

//------------------------------------------------------------------------------

ConnectedEdges::ConnectedEdges ()
  : m_connectedEdgeFlags (0)
{
}

bool ConnectedEdges::isConnectedOnTop () const
{
  return (m_connectedEdgeFlags & juce::Button::ConnectedOnTop) != 0;
}

bool ConnectedEdges::isConnectedOnLeft () const
{
  return (m_connectedEdgeFlags & juce::Button::ConnectedOnLeft) != 0;
}

bool ConnectedEdges::isConnectedOnBottom () const
{
  return (m_connectedEdgeFlags & juce::Button::ConnectedOnBottom) != 0;
}

bool ConnectedEdges::isConnectedOnRight () const
{
  return (m_connectedEdgeFlags & juce::Button::ConnectedOnRight) != 0;
}

void ConnectedEdges::setConnectedEdgeFlags (int connectedEdgeFlags)
{
  m_connectedEdgeFlags = connectedEdgeFlags;
}

Path const ConnectedEdges::createConnectedFace (
  Rectangle <int> const& bounds,
  float frameThickness,
  float cornerRadius)
{
  Path path;
  Rectangle <float> const r = bounds.toFloat().reduced (frameThickness/2, frameThickness/2);

  float const x = r.getX();
  float const y = r.getY();
  float const w = r.getWidth();
  float const h = r.getHeight();
  float const csx = jmin (cornerRadius, w * 0.5f);
  float const csy = jmin (cornerRadius, h * 0.5f);
  float const cs45x = csx * 0.45f;
  float const cs45y = csy * 0.45f;
  float const x2 = x + w;
  float const y2 = y + h;

  // start

  if (isConnectedOnLeft () || isConnectedOnTop())
    path.startNewSubPath (x, y);
  else
    path.startNewSubPath (x + csx, y);

  // top

  if (isConnectedOnTop () || isConnectedOnRight ())
  {
    path.lineTo( x2, y );
  }
  else
  {
    path.lineTo (x2 - csx, y);
    path.cubicTo (x2 - cs45x, y, x2, y + cs45y, x2, y + csy);
  }

  // right

  if (isConnectedOnRight () || isConnectedOnBottom ())
  {
    path.lineTo( x2, y2 );
  }
  else
  {
    path.lineTo (x2, y2 - csy);
    path.cubicTo (x2, y2 - cs45y, x2 - cs45x, y2, x2 - csx, y2);
  }
    
  // bottom
    
  if (isConnectedOnBottom () || isConnectedOnLeft ())
  {
    path.lineTo( x, y2 );
  }
  else
  {
    path.lineTo (x + csx, y2);
    path.cubicTo (x + cs45x, y2, x, y2 - cs45y, x, y2 - csy);
  }

  // left

  if (!isConnectedOnLeft () && !isConnectedOnTop ())
  {
    path.lineTo (x, y + csy);
    path.cubicTo (x, y + cs45y, x + cs45x, y, x + csx, y);
  }

  path.closeSubPath();

  return path;
}

}

//------------------------------------------------------------------------------

namespace Control {

Base::Base (Model::Base::Ptr model)
  : m_model (model)
{
  if (m_model != nullptr)
  {
    m_model->addListener (this);

    triggerAsyncUpdate ();
  }
}

Base::~Base ()
{
  if (m_model != nullptr)
    m_model->removeListener (this);
}

Model::Base* Base::getModel ()
{
  return m_model;
}

void Base::onModelChanged (Model::Base* model)
{
  Component* component = dynamic_cast <Component*> (this);

  if (component != nullptr)
    component->repaint ();
}

void Base::onModelEnablement (Model::Base* model)
{
  Component* component = dynamic_cast <Component*> (this);

  if (component != nullptr)
  {
    component->setEnabled (model->isEnabled ());
  }
}

void Base::handleAsyncUpdate ()
{
  vfassert (m_model != nullptr);

  Component* component = dynamic_cast <Component*> (this);

  if (component != nullptr)
    component->setEnabled (m_model->isEnabled ());
}

}
