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
  : COptionsTab ("Drop Shadow")
{
  m_activeButton = createToggleButton ("Active", false);

  m_kindComboBox = createEmptyComboBox ("Kind");
  m_kindComboBox->addItem ("Outer Bevel", 1);
  m_kindComboBox->addItem ("Inner Bevel", 2);
  m_kindComboBox->addItem ("Emboss", 3);
  m_kindComboBox->addItem ("Pillow Emboss", 4);
  m_kindComboBox->addItem ("Stroke Emboss", 5);

  m_techniqueComboBox = createEmptyComboBox ("How");
  m_techniqueComboBox->addItem ("Smooth", 1);
  m_techniqueComboBox->addItem ("Chisel Hard", 2);
  m_techniqueComboBox->addItem ("Chisel Soft", 3);

  m_depthSlider = createPercentSlider ("Depth", 100, 1000);

  m_reverseButton = createToggleButton ("Reverse", false);

  m_sizeSlider = createIntegerSlider ("Size", 0, 250, 0);

  m_softenSlider = createIntegerSlider ("Soften", 0, 16, 0);

  m_hiliteModeComboBox = createModeComboBox ("Mode (H)", vf::BlendMode::modeNormal);

  m_hiliteOpacitySlider = createPercentSlider ("Hilite", 1);

  m_shadowModeComboBox = createModeComboBox ("Mode (S)", vf::BlendMode::modeNormal);

  m_shadowOpacitySlider = createPercentSlider ("Shadow", 1);
}

CBevelEmbossTab::~CBevelEmbossTab ()
{
  deleteAllChildren ();
}

void CBevelEmbossTab::buttonClicked (Button* button)
{
}

void CBevelEmbossTab::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
}

void CBevelEmbossTab::sliderValueChanged (Slider* slider)
{
}
