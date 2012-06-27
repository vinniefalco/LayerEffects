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

namespace Facade {

SolidColour::SolidColour ()
  : m_colour (Colours::black)
{
}

void SolidColour::setSolidColour (Colour const& colour)
{
  m_colour = colour;
}

void SolidColour::paint (Graphics& g, Rectangle <int> const& bounds)
{
  g.setColour (m_colour);
  g.fillRect (bounds);
}

}

//------------------------------------------------------------------------------

namespace Control {

Static::Static ()
  : ResizableLayout (this)
  , m_connectedEdgeFlags (0)
{
}

void Static::setConnectedEdges (int flags)
{
  if (m_connectedEdgeFlags != flags)
  {
    m_connectedEdgeFlags = flags;
    repaint ();
  }
}

void Static::paint (Graphics& g)
{
  vf::Facade::Static* facade = dynamic_cast <vf::Facade::Static*> (this);

  if (facade != nullptr)
  {
    updateFacade ();

    facade->paint (g, getLocalBounds ());
  }
}

void Static::paintOverChildren (Graphics& g)
{
  vf::Facade::Static* facade = dynamic_cast <vf::Facade::Static*> (this);

  if (facade != nullptr)
  {
    facade->paintOverChildren (g, getLocalBounds ());
  }
}

void Static::updateFacade ()
{
  vf::Facade::Static* facade = dynamic_cast <vf::Facade::Static*> (this);

  if (facade != nullptr)
    facade->setConnectedEdgeFlags (m_connectedEdgeFlags);
}

}
