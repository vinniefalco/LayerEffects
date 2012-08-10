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

CInnerGlowTab::CInnerGlowTab () : COptionsTab ("Inner Glow")
{
  m_options.active = false;
  m_options.mode = vf::BlendMode::modeScreen;
  m_options.opacity = 0.75;
  m_options.colours = vf::GradientColours (Colours::white, Colours::transparentWhite);
  m_options.precise = true;
  m_options.reverse = false;
  m_options.choke = 0;
  m_options.size = 5;
  m_options.range = .5;

  m_activeButton = createToggleButton ("Active", m_options.active);
  m_modeComboBox = createModeComboBox ("Mode", m_options.mode);
  m_opacitySlider = createPercentSlider ("Opacity", m_options.opacity);
  m_preciseButton = createToggleButton ("Precise", m_options.precise);
  m_reverseButton = createToggleButton ("Reverse", m_options.reverse);
  m_chokeSlider = createPercentSlider ("Choke", m_options.choke);
  m_sizeSlider = createIntegerSlider ("Size", 0, 250, m_options.size);
  m_rangeSlider = createPercentSlider ("Range", m_options.range);
}

CInnerGlowTab::~CInnerGlowTab ()
{
  deleteAllChildren ();
}

void CInnerGlowTab::buttonClicked (Button* button)
{
  if (button == m_activeButton)
    m_options.active = button->getToggleState ();

  else if (button == m_preciseButton)
    m_options.precise = button->getToggleState ();

  else if (button == m_reverseButton)
    m_options.reverse = button->getToggleState ();

  vf::componentNotifyParent (this, &Options::Listener::onOptionsInnerGlow, m_options);
}

void CInnerGlowTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == m_modeComboBox)
    m_options.mode = vf::BlendMode::Type (m_modeComboBox->getSelectedId ());

  vf::componentNotifyParent (this, &Options::Listener::onOptionsInnerGlow, m_options);
}

void CInnerGlowTab::sliderValueChanged (Slider* slider)
{
  if (slider == m_opacitySlider)
    m_options.opacity = slider->getValue () / 100;

  else if (slider == m_chokeSlider)
    m_options.choke = slider->getValue ()/ 100;

  else if (slider == m_sizeSlider)
    m_options.size = int (slider->getValue ());

  else if (slider == m_rangeSlider)
    m_options.range = slider->getValue () / 100;

  vf::componentNotifyParent (this, &Options::Listener::onOptionsInnerGlow, m_options);
}
