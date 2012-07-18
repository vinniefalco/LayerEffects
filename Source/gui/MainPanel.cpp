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

MainPanel::MainPanel ()
{
#if 0
  CBlendModeDemo* c = new CBlendModeDemo;
#else
  CTextDemo* c = new CTextDemo;
#endif
  c->setBounds (0, 0, 4 + 256 + 4 + 256 + 4 + 256 + 4, 4 + 280 + 4);
  addAndMakeVisible (c);

  setSize (c->getBounds().getWidth (), c->getBounds().getHeight ());
}

MainPanel::~MainPanel()
{
  deleteAllChildren();
}

StringArray MainPanel::getMenuBarNames()
{
  StringArray names;
  names.add (TRANS("File"));
  return names;
}

PopupMenu MainPanel::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
  PopupMenu menu;
  ApplicationCommandManager* commandManager = MainApp::getInstance().getCommandManager();

  switch (topLevelMenuIndex)
  {
  case 0:
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
    break;

  case 1:
    menu.addCommandItem (commandManager, MainApp::cmdAbout);
    break;
  };

  return menu;
}

void MainPanel::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
}
