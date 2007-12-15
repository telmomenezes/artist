/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_ARTIST_LAYER_H)
#define __INCLUDE_ARTIST_LAYER_H

#include <math.h>
#include <string>

namespace art
{

using std::string;

class Layer
{
public:
    Layer();
    virtual ~Layer();

    int getWidth(){return mWidth;}
    int getHeight(){return mHeight;}

    virtual void setColor(unsigned int red,
                unsigned int green,
                unsigned int blue,
                unsigned int alpha)=0;
    virtual void setColor(unsigned int red,
                unsigned int green,
                unsigned int blue);
    virtual void setAlpha(unsigned int alpha);
    virtual void setColorRGBA(unsigned int color);
    virtual void setColorRGB(unsigned int color);
    virtual void setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue)=0;
    virtual void setBackgroundColorRGB(unsigned int color);

    virtual void setPointSize(float size)=0;
    virtual void setLineWidth(float width)=0;

    void setCurveAngleStep(float angle){mCurveAngleStep = angle;}

    virtual void clear()=0;

    bool isRoot(){return mRoot;}

    virtual void _initEmpty(int width, int height){};
    void _setRoot(int width, int height);

protected:
    int mWidth;
    int mHeight;
    bool mRoot;

    unsigned int mRed;
    unsigned int mGreen;
    unsigned int mBlue;
    unsigned int mAlpha;

    float mCurveAngleStep;
};

}

#endif

