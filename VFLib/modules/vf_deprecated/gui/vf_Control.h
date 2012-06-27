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

#ifndef VF_CONTROL_VFHEADER
#define VF_CONTROL_VFHEADER

#include "vf_Facade.h"
#include "vf_Model.h"

namespace Ui {

// A control is a Component that combines a Facade with an optional Model
// that displays the Model and allows the user to interact. Derived classes
// provide the actual Component
//

namespace Control {

class View
{
public:
  virtual void updateView () = 0;
};

//------------------------------------------------------------------------------

class Base
  : public View
  , public Model::Base::Listener
  , Uncopyable
{
public:
  Base (Component* component,
        Facade::Base* facade,
        ReferenceCountedObjectPtr <Model::Base> model);
  ~Base ();

  Model::Base& getModel ();
  Facade::Base& getFacade ();
  Component& getComponent ();

protected:
  void updateView ();

  void onModelEnablement (Model::Base* model);

private:
  Component& m_component;
  ScopedPointer <Facade::Base> m_facade;
  ReferenceCountedObjectPtr <Model::Base> m_model;
};

}

}

#endif
