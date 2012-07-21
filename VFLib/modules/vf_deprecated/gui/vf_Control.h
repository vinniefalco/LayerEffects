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
