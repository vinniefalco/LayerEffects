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