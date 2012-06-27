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
