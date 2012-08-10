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

CFillTab::CFillTab () : COptionsTab ("Fill")
{
  m_modeComboBox = createModeComboBox ("Mode", m_options.mode);

  m_opacitySlider = createPercentSlider ("Opacity", m_options.opacity);
}

CFillTab::~CFillTab ()
{
}

void CFillTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
  if (comboBoxThatHasChanged == m_modeComboBox)
  {
    m_options.mode = vf::BlendMode::Type (m_modeComboBox->getSelectedId ());

    vf::componentNotifyParent (this, &Options::Listener::onOptionsFill, m_options);
  }
}

void CFillTab::sliderValueChanged (Slider* slider)
{
  if (slider == m_opacitySlider)
  {
    m_options.opacity = slider->getValue () / 100;

    vf::componentNotifyParent (this, &Options::Listener::onOptionsFill, m_options);
  }
}
