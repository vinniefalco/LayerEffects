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

CStrokeTab::CStrokeTab ()
  : COptionsTab ("Stroke")
{
  m_options.active = false;
  m_options.pos = vf::StrokeStyle::posOuter;
  m_options.size = 1;
  m_options.mode = vf::BlendMode::modeNormal;
  m_options.opacity = 1;
  m_options.type = vf::StrokeStyle::typeColour;
  m_options.colour = Colours::blue;

  m_activeButton = createToggleButton ("Active", m_options.active);

  m_posComboBox = createEmptyComboBox ("Pos");
  m_posComboBox->addItem ("Outside", vf::StrokeStyle::posOuter);
  m_posComboBox->addItem ("Inside",  vf::StrokeStyle::posInner);
  m_posComboBox->addItem ("Center",  vf::StrokeStyle::posCentre);
  m_posComboBox->setSelectedId (m_options.pos);

  m_sizeSlider = createIntegerSlider ("Size", 1, 250, m_options.size);

  m_modeComboBox = createModeComboBox ("Mode", m_options.mode);

  m_opacitySlider = createPercentSlider ("Opacity", m_options.opacity);

  m_typeComboBox = createEmptyComboBox ("Type");
  m_typeComboBox->addItem ("Colour", vf::StrokeStyle::typeColour);
  m_typeComboBox->addItem ("Gradient",  vf::StrokeStyle::typeGradient);
  m_typeComboBox->addItem ("Pattern",  vf::StrokeStyle::typePattern);
  m_typeComboBox->setSelectedId (m_options.type);
}

CStrokeTab::~CStrokeTab ()
{
  deleteAllChildren ();
}

void CStrokeTab::buttonClicked (Button* button)
{
  if (button == m_activeButton)
  {
    m_options.active = button->getToggleState ();
  }

  vf::componentNotifyParent (this, &Options::Listener::onOptionsStroke, m_options);
}

void CStrokeTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == m_posComboBox)
  {
    m_options.pos = vf::StrokeStyle::Pos (comboBoxThatHasChanged->getSelectedId ());
  }
  else if (comboBoxThatHasChanged == m_modeComboBox)
  {
    m_options.mode = vf::BlendMode::Type (comboBoxThatHasChanged->getSelectedId ());
  }
  else if (comboBoxThatHasChanged == m_typeComboBox)
  {
    m_options.type = vf::StrokeStyle::Type (comboBoxThatHasChanged->getSelectedId ());
  }

  vf::componentNotifyParent (this, &Options::Listener::onOptionsStroke, m_options);
}

void CStrokeTab::sliderValueChanged (Slider* slider)
{
  if (slider == m_sizeSlider)
  {
    m_options.size = int (slider->getValue ());
  }
  else if (slider == m_opacitySlider)
  {
    m_options.opacity = slider->getValue () / 100.;
  }

  vf::componentNotifyParent (this, &Options::Listener::onOptionsStroke, m_options);
}
