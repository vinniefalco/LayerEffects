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

CBevelEmbossTab::CBevelEmbossTab ()
  : COptionsTab ("Bevel and Emboss")
{
  m_options.active = false;
  m_options.kind = vf::BevelEmbossStyle::kindOuterBevel;
  m_options.technique = vf::BevelEmbossStyle::techniqueSmooth;
  m_options.depth = 1.;
  m_options.reverse = false;
  m_options.size = 5;
  m_options.soften = 0;
  m_options.lightAngle = vf::degreesToRadians <double> (-45);
  m_options.lightElevation = vf::degreesToRadians <double> (30);
  m_options.hilightMode = vf::BlendMode::modeScreen;
  m_options.hilightOpacity = .75f;
  m_options.hilightColour = Colours::white;
  m_options.shadowMode = vf::BlendMode::modeMultiply;
  m_options.shadowOpacity = .75f;
  m_options.shadowColour = Colours::black;

  m_activeButton = createToggleButton ("Active", m_options.active);

  m_kindComboBox = createEmptyComboBox ("Kind");
  m_kindComboBox->addItem ("Outer Bevel",   vf::BevelEmbossStyle::kindOuterBevel);
  m_kindComboBox->addItem ("Inner Bevel",   vf::BevelEmbossStyle::kindInnerBevel);
  m_kindComboBox->addItem ("Emboss",        vf::BevelEmbossStyle::kindEmboss);
  m_kindComboBox->addItem ("Pillow Emboss", vf::BevelEmbossStyle::kindPillowEmboss);
  m_kindComboBox->addItem ("Stroke Emboss", vf::BevelEmbossStyle::kindStrokeEmboss);
  m_kindComboBox->setSelectedId (m_options.kind);

  m_techniqueComboBox = createEmptyComboBox ("How");
  m_techniqueComboBox->addItem ("Smooth",       vf::BevelEmbossStyle::techniqueSmooth);
  m_techniqueComboBox->addItem ("Chisel Hard",  vf::BevelEmbossStyle::techniqueChiselSoft);
  m_techniqueComboBox->addItem ("Chisel Soft",  vf::BevelEmbossStyle::techniqueChiselHard);
  m_techniqueComboBox->setSelectedId (m_options.technique);

  m_depthSlider = createPercentSlider ("Depth", m_options.depth, 1000);
  m_depthSlider->setRange (1, 1000, 1);
  m_reverseSlider = createToggleButton ("Reverse", m_options.reverse);
  m_sizeSlider = createIntegerSlider ("Size", 0, 250, m_options.size);
  m_softenSlider = createIntegerSlider ("Soften", 0, 16, m_options.soften);
  m_angleSlider = createIntegerSlider ("Angle", 0, 359, vf::radiansToDegrees <int> (m_options.lightAngle));
  m_elevationSlider = createIntegerSlider ("Elevation", 0, 90, vf::radiansToDegrees <int> (m_options.lightElevation));
  m_hiliteModeComboBox = createModeComboBox ("Mode (H)", m_options.hilightMode);
  m_hiliteOpacitySlider = createPercentSlider ("Hilite", m_options.hilightOpacity);
  m_shadowModeComboBox = createModeComboBox ("Mode (S)", m_options.shadowMode);
  m_shadowOpacitySlider = createPercentSlider ("Shadow", m_options.shadowOpacity);
}

CBevelEmbossTab::~CBevelEmbossTab ()
{
  deleteAllChildren ();
}


void CBevelEmbossTab::buttonClicked (Button* button)
{
  if (button == m_activeButton)
    m_options.active = button->getToggleState ();

  else if (button == m_reverseSlider)
    m_options.reverse = button->getToggleState ();

  vf::componentNotifyParent (this, &Options::Listener::onOptionsBevelEmboss, m_options);
}

void CBevelEmbossTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == m_kindComboBox)
    m_options.kind = vf::BevelEmbossStyle::Kind (comboBoxThatHasChanged->getSelectedId ());

  else if (comboBoxThatHasChanged == m_techniqueComboBox)
    m_options.technique = vf::BevelEmbossStyle::Technique (comboBoxThatHasChanged->getSelectedId ());

  else if (comboBoxThatHasChanged == m_hiliteModeComboBox)
    m_options.hilightMode = vf::BlendMode::Type (comboBoxThatHasChanged->getSelectedId ());

  else if (comboBoxThatHasChanged == m_shadowModeComboBox)
    m_options.shadowMode = vf::BlendMode::Type (comboBoxThatHasChanged->getSelectedId ());

  vf::componentNotifyParent (this, &Options::Listener::onOptionsBevelEmboss, m_options);
}

void CBevelEmbossTab::sliderValueChanged (Slider* slider)
{
  if (slider == m_sizeSlider)
    m_options.size = int (slider->getValue ());

  else if (slider == m_softenSlider)
    m_options.soften = int (slider->getValue ());

  else if (slider == m_depthSlider)
    m_options.depth = slider->getValue () / 100;

  else if (slider == m_angleSlider)
    m_options.lightAngle = vf::degreesToRadians <float> (slider->getValue ());

  else if (slider == m_elevationSlider)
    m_options.lightElevation = vf::degreesToRadians <float> (slider->getValue ());

  else if (slider == m_hiliteOpacitySlider)
    m_options.hilightOpacity = slider->getValue () / 100.;

  else if (slider == m_shadowOpacitySlider)
    m_options.shadowOpacity = slider->getValue () / 100.;

  vf::componentNotifyParent (this, &Options::Listener::onOptionsBevelEmboss, m_options);
}
