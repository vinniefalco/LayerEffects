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

#ifndef VF_UI_LABEL_H
#define VF_UI_LABEL_H

namespace Ui {

// A Label is simply a line of formatted text that comes from a Model

//------------------------------------------------------------------------------

namespace Model {

class Label : virtual public Model::Base
{
public:
  virtual const String getText () = 0;
};

//------------------------------------------------------------------------------

// This is for prototyping when you don't have a real Model

class DummyLabel : public Label
{
public:
  DummyLabel (const String text);
  const String getText ();

private:
  String m_text;

  JUCE_LEAK_DETECTOR(DummyLabel)
};

}

//------------------------------------------------------------------------------

namespace Facade {

class LabelBase : public Facade::Base
{
public:
  LabelBase();
  void setText (const String text);

protected:
  const String getText ();

private:
  String m_text;

  JUCE_LEAK_DETECTOR(LabelBase)
};

//------------------------------------------------------------------------------

// A simple implementation of a Label Facade that should satisfy most uses

class Label : public LabelBase
{
public:
  Label();
  
  void setFont (Font font);
  void setColour (Colour colour);
  void setJustification (Justification just);
  
  void paint (Graphics& g, const Rectangle<int>& bounds);

protected:
  Font getFont();
  Colour getColour();
  Justification getJustification();

private:
  Font m_font;
  Colour m_colour;
  Justification m_just;

  JUCE_LEAK_DETECTOR(Label)
};

}

//------------------------------------------------------------------------------

namespace Control {

class Label
  : public Component
  , public Base
{
public:
  Label (Facade::Label* facade, Model::Label* model);
  ~Label();

  Model::Label& getModel();
  Facade::Label& getFacade();

  void paint (Graphics& g);
  void paintOverChildren (Graphics& g);
  void enablementChanged ();
  void updateView();

private:
  Facade::Label* m_facade;
  ReferenceCountedObjectPtr<Model::Label> m_model;
};

  //  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Static)

}

}

#endif