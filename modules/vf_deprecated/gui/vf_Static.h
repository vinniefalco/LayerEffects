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

#ifndef __VF_STATIC_VFHEADER__
#define __VF_STATIC_VFHEADER__

#include "vf_UiBase.h"

// A Static control has no interaction, just drawing.
// Child components can be added to the ResizableLayout.
//

namespace Facade {

class Static : public ConnectedEdges
{
public:
};

class SolidColour : public Static
{
public:
  SolidColour ();
  void setSolidColour (Colour const& colour);
  void paint (Graphics& g, Rectangle <int> const& bounds);

private:
  Colour m_colour;
};

}

namespace Control {

class Static
  : public Component
  , public ResizableLayout
  , public Base
{
public:
  Static ();

  int getConnectedEdgeFlags () const
    { return m_connectedEdgeFlags; }

  void setConnectedEdges (int flags);

  void setConnectedEdgeFlag (int flag, bool connected)
  {
    if (connected)
      setConnectedEdges (getConnectedEdgeFlags () | flag);
    else
      setConnectedEdges (getConnectedEdgeFlags () & ~flag);
  }

  void setConnectedOnLeft (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnLeft, connected); }

  void setConnectedOnRight (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnRight, connected); }

  void setConnectedOnTop (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnTop, connected); }

  void setConnectedOnBottom (bool connected)
    { setConnectedEdgeFlag (Button::ConnectedOnBottom, connected); }

  void paint (Graphics& g);
  void paintOverChildren (Graphics& g);

protected:
  virtual void updateFacade ();

private:
  int m_connectedEdgeFlags;
};

template <class FacadeType>
class StaticType : public Static, public FacadeType
{
public:
};

}

#endif
