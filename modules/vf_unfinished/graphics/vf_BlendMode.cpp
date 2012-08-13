/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

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
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/
/*============================================================================*/

namespace BlendMode
{

Type getMode (int index)
{
  switch (index)
  {
  case  0: return modeNormal;     
  case  1: return modeLighten;    
  case  2: return modeDarken;     
  case  3: return modeMultiply;   
  case  4: return modeAverage;    
  case  5: return modeAdd;        
  case  6: return modeSubtract;   
  case  7: return modeDifference; 
  case  8: return modeNegation;   
  case  9: return modeScreen;     
  case 10: return modeExclusion;  
  case 11: return modeOverlay;    
  case 12: return modeSoftLight;  
  case 13: return modeHardLight;  
  case 14: return modeColorDodge; 
  case 15: return modeColorBurn;  
  case 16: return modeLinearDodge;
  case 17: return modeLinearBurn; 
  case 18: return modeLinearLight;
  case 19: return modeVividLight; 
  case 20: return modePinLight;   
  case 21: return modeHardMix;    
  case 22: return modeReflect;    
  case 23: return modeGlow;       
  case 24: return modePhoenix;    
  default:
    jassertfalse;
    break;
  }

  return modeNormal;
}

String getName (Type mode)
{
  switch (mode)
  {
  case modeNormal:      return TRANS ("Normal");
  case modeLighten:     return TRANS ("Lighten");
  case modeDarken:      return TRANS ("Darken");
  case modeMultiply:    return TRANS ("Multiply");
  case modeAverage:     return TRANS ("Average");
  case modeAdd:         return TRANS ("Add");
  case modeSubtract:    return TRANS ("Subtract");
  case modeDifference:  return TRANS ("Difference");
  case modeNegation:    return TRANS ("Negation");
  case modeScreen:      return TRANS ("Screen");
  case modeExclusion:   return TRANS ("Exclusion");
  case modeOverlay:     return TRANS ("Overlay");
  case modeSoftLight:   return TRANS ("Soft Light");
  case modeHardLight:   return TRANS ("Hard Light");
  case modeColorDodge:  return TRANS ("Color Dodge");
  case modeColorBurn:   return TRANS ("Color Burn");
  case modeLinearDodge: return TRANS ("Linear Dodge");
  case modeLinearBurn:  return TRANS ("Linear Burn");
  case modeLinearLight: return TRANS ("Linear Light");
  case modeVividLight:  return TRANS ("Vivid Light");
  case modePinLight:    return TRANS ("Pin Light");
  case modeHardMix:     return TRANS ("Hard Mix");
  case modeReflect:     return TRANS ("Reflect");
  case modeGlow:        return TRANS ("Glow");
  case modePhoenix:     return TRANS ("Phoenix");
  default:
    jassertfalse;
    break;
  }

  return "<Unknown>";
}

}
