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

#ifndef __VF_FACADE_VFHEADER__
#define __VF_FACADE_VFHEADER__

#include "vf_ConnectedEdges.h"
#include "vf_Model.h"

namespace Ui {

namespace Control {
  class Base;
}

//------------------------------------------------------------------------------

// A Facade encapsulates the drawable appearance of a control
//
namespace Facade {

class Base
  : public ConnectedEdges
  , public Model::Base::Listener
  , LeakChecked <Base>
  , Uncopyable
{
public:
  static const BorderSize <int> fullyOpaque;
  static const BorderSize <int> fullyTransparent;

public:
  Base();

  virtual ~Base ();

  Model::Base& getModel ();
  Control::Base& getControl ();
  Component& getComponent ();
  Rectangle <int> getLocalBounds ();

  void setAlpha (float alpha);

  // Controls call this.
  // Default behavior is to just call paint().
  // Subclasses can override for customization.
  //
  virtual void paintFacade (Graphics& g);

  virtual void paint (Graphics& g) /*= 0*/;
  virtual void paintOverChildren (Graphics& g);


  // legacy
  bool isEnabled ();
  void setEnabled (bool isEnabled);

  virtual BorderSize <int> getTransparency(); // fullyTransparent by default

  virtual void paint (Graphics& g, const Rectangle<int>& bounds);
  virtual void paintOverChildren (Graphics& g, const Rectangle<int>& bounds);

public:
  // utility
  static Path createFittedRoundRect (const Rectangle<int>& bounds,
                                     float frameThickness,
                                     float cornerRadius);

protected:

protected:
  friend class Control::Base;
  
  void attach (Model::Base* model, Control::Base* control);
  
  virtual void onAttach ();
  virtual void onModelChanged (Model::Base* model);

private:
  ReferenceCountedObjectPtr <Model::Base> m_model;
  Control::Base* m_control;
  bool m_isEnabled;
  TransparentBorder m_transparentBorder;
};

//------------------------------------------------------------------------------

#if 0
// An empty Facade for a container-type Component. Fully transparent.
class Empty : public Base
{
public:
  Empty();

  BorderSize<int> getTransparency();
  void paint (Graphics& g, const Rectangle<int>& bounds);
};
#endif

}

}

#endif