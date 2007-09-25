/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_LAYER_2D_H)
#define __INCLUDE_PYCASSO_LAYER_2D_H

#include "Layer.h"
#include "Font.h"

#include <math.h>
#include <string>

namespace pyc
{

using std::string;

class Layer2D : public Layer
{
public:
    Layer2D();
    virtual ~Layer2D();

    virtual void setRotation(float x, float y, float angle)=0;
    virtual void clearRotation()=0;

    virtual void setScale(float scaleX, float scaleY)=0;
    virtual void clearScale()=0;

    virtual void setTranslation(float transX, float transY)=0;
    virtual void clearTranslation()=0;

    virtual void setScreenTranslation(float transX, float transY)=0;
    virtual void clearScreenTranslation()=0;

    virtual void drawPoint(float x, float y)=0;

    virtual void drawLine(float x1, float y1, float x2, float y2)=0;

    virtual void drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)=0;

    virtual void drawSquare(float x,
                    float y,
                    float side)=0;

    virtual void drawCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0.0f,
                    float endAngle=(M_PI * 2))=0;

    virtual void fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)=0;

    virtual void fillSquare(float x,
                    float y,
                    float side)=0;

    virtual void fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0.0f,
                    float endAngle=(M_PI * 2))=0;

    virtual void drawLayer(Layer* layer,
                    float x=0.0f,
                    float y=0.0f,
                    float width=0.0f,
                    float height=0.0f)=0;

    void setFont(Font* font){mCurrentFont = font;}

    virtual void printText(float x, float y, string text)=0;

    virtual void _loadPNG(string filePath){};

protected:
    Font* mCurrentFont;
};

}

#endif

