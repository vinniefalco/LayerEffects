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

#ifndef LAYEREFFECTS_CBEVELEMBOSSTAB_HEADER
#define LAYEREFFECTS_CBEVELEMBOSSTAB_HEADER

/** Bevel and emboss options.
*/
class CBevelEmbossTab : public COptionsTab
{
public:
  CBevelEmbossTab ();
  ~CBevelEmbossTab ();

  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void sliderValueChanged (Slider* slider);

private:
  Options::BevelEmboss m_options;

  ToggleButton* m_activeButton;
  ComboBox* m_kindComboBox;
  ComboBox* m_techniqueComboBox;
  Slider* m_depthSlider;
  Slider* m_sizeSlider;
  Slider* m_softenSlider;
  Slider* m_angleSlider;
  Slider* m_elevationSlider;
  ComboBox* m_hiliteModeComboBox;
  Slider* m_hiliteOpacitySlider;
  ComboBox* m_shadowModeComboBox;
  Slider* m_shadowOpacitySlider;
};

#endif
