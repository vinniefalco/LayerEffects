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

CDropShadowTab::CDropShadowTab ()
  : COptionsTab ("Drop Shadow")
{
  m_options.active = false;
  m_options.mode = vf::BlendMode::modeNormal;
  m_options.colour = Colours::black;
  m_options.opacity = 1;
  m_options.angle = vf::degreesToRadians <double> (135);
  m_options.distance = 4;
  m_options.spread = 0;
  m_options.size = 9;
  m_options.knockout = true;

  m_activeButton = createToggleButton ("Active", m_options.active);
  m_modeComboBox = createModeComboBox ("Mode", m_options.mode);
  m_colourPicker = createColourPicker ("Colour", m_options.colour);
  m_opacitySlider = createPercentSlider ("Opacity", m_options.opacity);
  m_angleSlider = createIntegerSlider ("Angle", 0, 359, vf::radiansToDegrees <int> (m_options.angle));
  m_distanceSlider = createIntegerSlider ("Distance", 0, 1000, m_options.distance);
  m_spreadSlider = createPercentSlider ("Spread", m_options.spread);
  m_sizeSlider = createIntegerSlider ("Size", 0, 250, m_options.size);
  m_knockoutButton = createToggleButton ("Knockout", m_options.knockout);

  m_colourPicker->addListener (this);
}

CDropShadowTab::~CDropShadowTab ()
{
  deleteAllChildren ();
}

void CDropShadowTab::buttonClicked (Button* button)
{
  if (button == m_activeButton)
    m_options.active = button->getToggleState ();

  else if (button == m_knockoutButton)
    m_options.knockout = button->getToggleState ();

  vf::componentNotifyParent (this, &Options::Listener::onOptionsDropShadow, m_options);
}

void CDropShadowTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == m_modeComboBox)
    m_options.mode = vf::BlendMode::Type (m_modeComboBox->getSelectedId ());

  vf::componentNotifyParent (this, &Options::Listener::onOptionsDropShadow, m_options);
}

void CDropShadowTab::sliderValueChanged (Slider* slider)
{
  if (slider == m_opacitySlider)
    m_options.opacity = slider->getValue () / 100;

  else if (slider == m_angleSlider)
    m_options.angle = vf::degreesToRadians <double> (slider->getValue ());

  else if (slider == m_distanceSlider)
    m_options.distance = int (slider->getValue ());

  else if (slider == m_spreadSlider)
    m_options.spread = slider->getValue () / 100;

  else if (slider == m_sizeSlider)
    m_options.size = int (slider->getValue ());

  vf::componentNotifyParent (this, &Options::Listener::onOptionsDropShadow, m_options);
}

void CDropShadowTab::onColourPickerChanged (CColourPicker* picker, Colour colour)
{
  if (picker = m_colourPicker)
  {
    m_options.colour = colour;

    vf::componentNotifyParent (this, &Options::Listener::onOptionsDropShadow, m_options);
  }
}
