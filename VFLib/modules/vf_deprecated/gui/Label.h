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