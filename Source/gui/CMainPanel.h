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

#ifndef LAYEREFFECTS_CMAINPANEL_HEADER
#define LAYEREFFECTS_CMAINPANEL_HEADER

class CMainPanel
  : public Component
  , public MenuBarModel
  , public vf::ResizableLayout
  , public vf::TopLevelConstrainer
  , public Options::Listener
{
public:
  CMainPanel ();
  ~CMainPanel ();

  void paint (Graphics& g);

  void onOptionsGeneral         (Options::General options);
  void onOptionsFill            (Options::Fill options);
  void onOptionsDropShadow      (Options::DropShadow options);
  void onOptionsInnerShadow     (Options::InnerShadow options);
  void onOptionsOuterGlow       (Options::OuterGlow options);
  void onOptionsInnerGlow       (Options::InnerGlow options);
  void onOptionsBevelEmboss     (Options::BevelEmboss options);
  void onOptionsGradientOverlay (Options::GradientOverlay options);
  void onOptionsStroke          (Options::Stroke options);

  StringArray getMenuBarNames();
  PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

private:
  Options m_options;
};

#endif

