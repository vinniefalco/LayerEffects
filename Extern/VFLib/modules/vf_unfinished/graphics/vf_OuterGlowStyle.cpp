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
/*

Experimental notes:

- The outer border of the glow has a fade, in addition to the alpha of the
  interpolated gradient colour.

- For Precise, the fade starts at radius = 76% of the size, rounded up.

- Range, Contour, and Jitter do not affect alpha of the fade (Softer and Precise)

- Spread affects fade. Increasing spread reduces the amount of fade for Softer and Precise.

- There is no fade at 100% spread

- Contour accepts "Adjusted Distance" as x and outputs position in gradient as Y

- Previewing Range changes is very fast for "Softer" at 0% spread.

- Fade extends 1 pixel past "size". 99% Spread at 250px yields fade at 251 distance

- Range has no effect when the gradient is a single solid colour at both ends.

- Varying the Size when Spread = 0% is very fast. It gets slower as spread tends
  towards 100%.

Data

Technique   Size    Spread    Fade (px)   (1-Spread)*Size   Fade%
-----------------------------------------------------------------
Precise     250     0         60          250               24%
Precise     250     25        44          188               23%
Precise     250     50        30          125               24%
Precise     250     75        14          63                22%
Precise     250     100       0           0
Precise     100     0         24          100               24%
Precise     100     25        18          75                24%
Precise     100     50        12          50                24%
Precise     100     75        6           25                24%
Precise     100     100       0           0

Softer      250


*/

#if 0
struct StackBlur
{
  int radius;

  StackBlur (int radius_)
    : radius (radius_)
  {
    jassert (radius > 0);
  }

  template <class Map>
  void operator() (Map map)
  {
    int[] pix=img.pixels;
    int w=map.getCols ();
    int h=map.getRows ();
    int wm=w-1;
    int hm=h-1;
    int wh=w*h;
    int div=radius+radius+1;

    int r[]=new int[wh];
    int g[]=new int[wh];
    int b[]=new int[wh];
    int rsum,gsum,bsum,x,y,i,p,yp,yi,yw;
    int vmin[] = new int[max(w,h)];

    int divsum=(div+1)>>1;
    divsum*=divsum;
    int dv[]=new int[256*divsum];
    for (i=0;i<256*divsum;i++){
      dv[i]=(i/divsum);
    }

    yw=yi=0;

    int[][] stack=new int[div][3];
    int stackpointer;
    int stackstart;
    int[] sir;
    int rbs;
    int r1=radius+1;
    int routsum,goutsum,boutsum;
    int rinsum,ginsum,binsum;

    for (y=0;y<h;y++){
      rinsum=ginsum=binsum=routsum=goutsum=boutsum=rsum=gsum=bsum=0;
      for(i=-radius;i<=radius;i++){
        p=pix[yi+min(wm,max(i,0))];
        sir=stack[i+radius];
        sir[0]=(p & 0xff0000)>>16;
        sir[1]=(p & 0x00ff00)>>8;
        sir[2]=(p & 0x0000ff);
        rbs=r1-abs(i);
        rsum+=sir[0]*rbs;
        gsum+=sir[1]*rbs;
        bsum+=sir[2]*rbs;
        if (i>0){
          rinsum+=sir[0];
          ginsum+=sir[1];
          binsum+=sir[2];
        } else {
          routsum+=sir[0];
          goutsum+=sir[1];
          boutsum+=sir[2];
        }
      }
      stackpointer=radius;

      for (x=0;x<w;x++){

        r[yi]=dv[rsum];
        g[yi]=dv[gsum];
        b[yi]=dv[bsum];
      
        rsum-=routsum;
        gsum-=goutsum;
        bsum-=boutsum;

        stackstart=stackpointer-radius+div;
        sir=stack[stackstart%div];
      
        routsum-=sir[0];
        goutsum-=sir[1];
        boutsum-=sir[2];
      
        if(y==0){
          vmin[x]=min(x+radius+1,wm);
        }
        p=pix[yw+vmin[x]];
      
        sir[0]=(p & 0xff0000)>>16;
        sir[1]=(p & 0x00ff00)>>8;
        sir[2]=(p & 0x0000ff);

        rinsum+=sir[0];
        ginsum+=sir[1];
        binsum+=sir[2];

        rsum+=rinsum;
        gsum+=ginsum;
        bsum+=binsum;
      
        stackpointer=(stackpointer+1)%div;
        sir=stack[(stackpointer)%div];
     
        routsum+=sir[0];
        goutsum+=sir[1];
        boutsum+=sir[2];
     
         rinsum-=sir[0];
        ginsum-=sir[1];
        binsum-=sir[2];
     
         yi++;
      }
      yw+=w;
    }
    for (x=0;x<w;x++){
      rinsum=ginsum=binsum=routsum=goutsum=boutsum=rsum=gsum=bsum=0;
      yp=-radius*w;
      for(i=-radius;i<=radius;i++){
        yi=max(0,yp)+x;
     
         sir=stack[i+radius];
      
        sir[0]=r[yi];
        sir[1]=g[yi];
        sir[2]=b[yi];
     
        rbs=r1-abs(i);
      
        rsum+=r[yi]*rbs;
        gsum+=g[yi]*rbs;
        bsum+=b[yi]*rbs;
     
        if (i>0){
          rinsum+=sir[0];
          ginsum+=sir[1];
          binsum+=sir[2];
        } else {
          routsum+=sir[0];
          goutsum+=sir[1];
          boutsum+=sir[2];
        }
      
        if(i<hm){
          yp+=w;
        }
      }
      yi=x;
      stackpointer=radius;
      for (y=0;y<h;y++){
        pix[yi]=0xff000000 | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];

        rsum-=routsum;
        gsum-=goutsum;
        bsum-=boutsum;

        stackstart=stackpointer-radius+div;
        sir=stack[stackstart%div];
     
        routsum-=sir[0];
        goutsum-=sir[1];
        boutsum-=sir[2];
     
         if(x==0){
          vmin[y]=min(y+r1,hm)*w;
        }
        p=x+vmin[y];
      
        sir[0]=r[p];
        sir[1]=g[p];
        sir[2]=b[p];
      
        rinsum+=sir[0];
        ginsum+=sir[1];
        binsum+=sir[2];

        rsum+=rinsum;
        gsum+=ginsum;
        bsum+=binsum;

        stackpointer=(stackpointer+1)%div;
        sir=stack[stackpointer];
     
        routsum+=sir[0];
        goutsum+=sir[1];
        boutsum+=sir[2];
      
        rinsum-=sir[0];
        ginsum-=sir[1];
        binsum-=sir[2];

        yi+=w;
      }
    }
  }
};
#endif

void OuterGlowStyle::operator() (Pixels destPixels, Pixels maskPixels)
{
  if (!active)
    return;

  SharedTable <Colour> table = colours.createLookupTable ();

  if (precise)
  {
  #if 1
    DistanceTransform::Meijster::calculateAntiAliasedLoop (
      RenderPixelAntiAliased (
        destPixels,
        opacity,
        spread,
        size,
        table),
      GetMask (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight (),
      DistanceTransform::Meijster::EuclideanMetric ());
  #else
    DistanceTransform::Chamfer::calculate (
      RenderPixel (
        destPixels,
        opacity,
        spread,
        size,
        table),
      DistanceTransform::BlackTest (maskPixels),
      maskPixels.getWidth (),
      maskPixels.getHeight ()
      //,DistanceTransform::Meijster::ChessMetric ());
      );
  #endif
  }
  else
  {
    // "Softer"

    Map2D <int> temp (maskPixels.getWidth (), maskPixels.getHeight ());

    BoxBlur () (maskPixels, temp, temp.getCols (), temp.getRows (), size);

    PixelARGB c (0);

    for (int y = 0; y < temp.getRows (); ++y)
    {
      for (int x = 0; x < temp.getCols (); ++x)
      {
        int const v = (temp (x, y) + 0) / 1;

        PixelRGB& dest (*((PixelRGB*)destPixels.getPixelPointer (x, y)));

        c.setAlpha (v);
        dest.blend (c);
      }
    }
  }
}
