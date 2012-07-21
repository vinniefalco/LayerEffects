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
