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