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

#ifndef VF_UI_METER_H
#define VF_UI_METER_H

namespace Ui {

// A Meter displays a single value from a Model, without user interaction

//------------------------------------------------------------------------------

namespace Model {

class Meter : virtual public Model::Base
{
public:
  virtual double getValue () = 0;
  virtual const String getValueAsText(); // default: empty
};

//------------------------------------------------------------------------------

class DummyMeter : public Meter
{
public:
  DummyMeter (double value = 0, const String name = String::empty);

  const String getName ();
  double getValue ();
  const String getValueAsText ();

private:
  String m_name;
  double m_value;
};

}

//------------------------------------------------------------------------------

namespace Facade {
  
class Meter : public Facade::Base
{
public:
  Meter();
  void setValue (double value);

  double getValue ();

private:
  double m_value;
};

}

//------------------------------------------------------------------------------

namespace Control {

class Meter
  : public Component
  , public Control::Base
{
public:
  explicit Meter (Facade::Meter* facade, Model::Meter* model);
  ~Meter();

  Model::Meter& getModel();
  Facade::Meter& getFacade();

  void paint (Graphics& g);
  void paintOverChildren (Graphics& g);

protected:
  void enablementChanged ();
  void updateView ();

private:
  Facade::Meter* m_facade;
  ReferenceCountedObjectPtr<Model::Meter> m_model;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Meter)
};

template<class FacadeType, class ModelType>
class MeterType : public Meter
{
public:
  MeterType (FacadeType* facade, ModelType* model)
    : Meter (facade, model)
    , m_facade (facade)
    , m_model (model)
  {
  }

  ModelType& getModel() { return *m_model; }
  FacadeType& getFacade() { return *m_facade; }

private:
  ModelType* m_model;
  FacadeType* m_facade;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterType)
};

}

}

#endif