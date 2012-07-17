//------------------------------------------------------------------------------
/*
  LayerEffects for JUCE

  Official project location:
  https://github.com/vinniefalco/LayerEffects

  ------------------------------------------------------------------------------

  License: MIT License (http://www.opensource.org/licenses/mit-license.php)
  Copyright (c) 2012 by Vinnie Falco

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
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
//------------------------------------------------------------------------------

CBlendModeResult::CBlendModeResult ()
  : m_mode (-1)
{
  m_comboBox = new ComboBox ("Mode");
  m_comboBox->addItem ("Normal"       , 1);
  m_comboBox->addItem ("Lighten"      , 2);
  m_comboBox->addItem ("Darken"       , 3);
  m_comboBox->addItem ("Multiply"     , 4);
  m_comboBox->addItem ("Average"      , 5);
  m_comboBox->addItem ("Add"          , 6);
  m_comboBox->addItem ("Subtract"     , 7);
  m_comboBox->addItem ("Difference"   , 8);
  m_comboBox->addItem ("Negation"     , 9);
  m_comboBox->addItem ("Screen"       , 10);
  m_comboBox->addItem ("Exclusion"    , 11);
  m_comboBox->addItem ("Overlay"      , 12);
  m_comboBox->addItem ("Soft Light"   , 13);
  m_comboBox->addItem ("Hard Light"   , 14);
  m_comboBox->addItem ("Color Dodge"  , 15);
  m_comboBox->addItem ("Color Burn"   , 16);
  m_comboBox->addItem ("Linear Dodge" , 17);
  m_comboBox->addItem ("Linear Burn"  , 18);
  m_comboBox->addItem ("Linear Light" , 19);
  m_comboBox->addItem ("Vivid Light"  , 20);
  m_comboBox->addItem ("Pin Light"    , 21);
  m_comboBox->addItem ("Hard Mix"     , 22);
  m_comboBox->addItem ("Reflect"      , 23);
  m_comboBox->addItem ("Glow"         , 24);
  m_comboBox->addItem ("Phoenix"      , 25);

  addAndMakeVisible (m_comboBox);

  m_comboBox->addListener (this);

  m_comboBox->setSelectedId (1);
}

CBlendModeResult::~CBlendModeResult()
{
}

void CBlendModeResult::setSourceImage (int index, Image image)
{
  m_sourceImage [index] = image;
  repaint ();
}

void CBlendModeResult::resized ()
{
  Rectangle <int> const bounds = getLocalBounds ();

  m_comboBox->setBounds (bounds.getX (), bounds.getY (), bounds.getWidth () - 24, 24);
}

void CBlendModeResult::paint (Graphics& g)
{
  vf::BackgroundContext bc (g);

  

  switch (m_mode)
  {
  default:
    break;
  }
}

void CBlendModeResult::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  m_mode = m_comboBox->getSelectedId ();

  repaint ();
}


