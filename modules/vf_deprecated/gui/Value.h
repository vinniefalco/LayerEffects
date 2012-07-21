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

#ifndef VF_UI_VALUE_H
#define VF_UI_VALUE_H

#include "Meter.h"

namespace Ui {

// A Value is a Meter which can be changed through user interaction

//------------------------------------------------------------------------------

namespace Model {

class Value : public Model::Meter
{
public:
  virtual double getDefaultValue () = 0;
  virtual void setValue (double newValue) = 0;
};

//------------------------------------------------------------------------------

class DummyValue : public Value
{
public:
  DummyValue (double value = 0, const String name = String::empty);
  const String getName ();
  double getValue ();
  const String getValueAsText ();
  double getDefaultValue ();
  void setValue (double newValue);

private:
  String m_name;
  double m_value;
};

}

//------------------------------------------------------------------------------

namespace Facade {

}

//------------------------------------------------------------------------------

namespace Control {

}

}

#endif