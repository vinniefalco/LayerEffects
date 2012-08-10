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

#ifndef LAYEREFFECTS_CINNERGLOWTAB_HEADER
#define LAYEREFFECTS_CINNERGLOWTAB_HEADER

/** Inner Glow options.
*/
class CInnerGlowTab : public COptionsTab
{
public:
  CInnerGlowTab ();
  ~CInnerGlowTab ();

  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void sliderValueChanged (Slider* slider);

private:
  Options::InnerGlow m_options;

  ToggleButton* m_activeButton;
  ComboBox* m_modeComboBox;
  Slider* m_opacitySlider;
  //CGradientPicker* m_gradientPicker;
  ToggleButton* m_preciseButton;
  ToggleButton* m_reverseButton;
  Slider* m_chokeSlider;
  Slider* m_sizeSlider;
  //CContourPicker* m_contourPicker;
  Slider* m_rangeSlider;
};

#endif
