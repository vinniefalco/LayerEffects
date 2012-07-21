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

namespace Ui {

namespace Model {

DummyLabel::DummyLabel (const String text)
  : m_text (text)
{
}

const String DummyLabel::getText ()
{
  return m_text;
}

}

//------------------------------------------------------------------------------

namespace Facade {

LabelBase::LabelBase()
{
}

void LabelBase::setText (const String text)
{
  m_text = text;
}

const String LabelBase::getText ()
{
  return m_text;
}

//------------------------------------------------------------------------------

Label::Label ()
: m_font (15)
, m_just (Justification::centred)
, m_colour (Colour(216, 216, 216))
{
}

void Label::setFont (Font font)
{
  m_font = font;
}

void Label::setColour (Colour colour)
{
  m_colour = colour;
}

void Label::setJustification (Justification just)
{
  m_just = just;
}

void Label::paint (Graphics& g, const Rectangle<int>& bounds)
{
  Colour cText (getColour());

  if (!isEnabled())
    cText = cText.withMultipliedAlpha (0.5f);

  g.setFont (getFont());
  g.setColour (cText);
  g.drawText (getText(), bounds.getX(), bounds.getY(),
    bounds.getWidth(), bounds.getHeight(), getJustification(), true);
}

Font Label::getFont ()
{
  return m_font;
}

Colour Label::getColour ()
{
  return m_colour;
}

Justification Label::getJustification ()
{
  return m_just;
}

}

//------------------------------------------------------------------------------

namespace Control {

Label::Label (Facade::Label *facade, Model::Label* model)
: Base (this, facade, model)
, m_facade (facade)
, m_model (model)
{
  m_model->addView (this);
}

Label::~Label()
{
  m_model->removeView (this);
}

Model::Label& Label::getModel ()
{
  return *m_model;
}

Facade::Label& Label::getFacade ()
{
  return *m_facade;
}

void Label::paint (Graphics& g)
{
  m_facade->paint (g, getLocalBounds());
}

void Label::paintOverChildren (Graphics& g)
{
  m_facade->paintOverChildren (g, getLocalBounds());
}

void Label::enablementChanged ()
{
  updateView ();
}

void Label::updateView ()
{
  getFacade().setEnabled (isEnabled());
  getFacade().setText (getModel().getText());
  repaint();
}

}

}
