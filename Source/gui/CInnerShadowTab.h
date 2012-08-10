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

#ifndef LAYEREFFECTS_CINNERSHADOWTAB_HEADER
#define LAYEREFFECTS_CINNERSHADOWTAB_HEADER

/** Inner Shadow options.
*/
class CInnerShadowTab : public COptionsTab
{
public:
  CInnerShadowTab ();
  ~CInnerShadowTab ();

  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void sliderValueChanged (Slider* slider);

private:
  vf::InnerShadowStyle m_options;

  ToggleButton* m_activeButton;
  ComboBox* m_modeComboBox;
  CSolidColourPicker* m_colourPicker;
  Slider* m_opacitySlider;
  Slider* m_angleSlider;
  Slider* m_distanceSlider;
  Slider* m_chokeSlider;
  Slider* m_sizeSlider;
};

#endif
