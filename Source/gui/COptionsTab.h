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

#ifndef LAYEREFFECTS_COPTIONSTAB_HEADER
#define LAYEREFFECTS_COPTIONSTAB_HEADER

/** Common options tab functionality.
*/
class COptionsTab
  : public Component
  , public Button::Listener
  , public ComboBox::Listener
  , public Slider::Listener
  , public CLayerGraphicsPreview::Listener
{
public:
  explicit COptionsTab (String componentName);
  
  ~COptionsTab ();

  void buttonClicked (Button* button);
  void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
  void sliderValueChanged (Slider* slider);

protected:
  ComboBox* createEmptyComboBox (String label);
  ComboBox* createModeComboBox (String label, vf::BlendMode::Type mode);
  Slider* createPercentSlider (String label, double fraction, int maxPercent = 100);
  Slider* createIntegerSlider (String label, int startValue, int endValue, int initialValue);
  ToggleButton* createToggleButton (String label, bool initialValue);
  CColourPicker* createColourPicker (String label, Colour colour);
  CContourPicker* createContourPicker (String label);

  static void addBlendModesToComboBox (ComboBox* comboBox);

public:
  static int getXStart ()             { return 4; }
  static int getWidth ()              { return 232; }
  static int getYGap ()               { return 4; }
  static int getLabelHeight ()        { return 15; }
  static int getSliderHeight ()       { return 24; }
  static int getToggleButtonHeight () { return 20; }

  Point <int> m_pos;
};

#endif
