/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_PYCASSO_LAYER_2D_OPENGL_H)
#define __INCLUDE_PYCASSO_LAYER_2D_OPENGL_H

#include "Layer2D.h"

#include <math.h>

#if defined(__PYCASSO_OS_WIN32)
#include <windows.h>
#endif

#if defined(__PYCASSO_OS_OSX)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <string>

namespace pyc
{

using std::string;

class Layer2DOpenGL : public Layer2D
{
public:
    Layer2DOpenGL();
    virtual ~Layer2DOpenGL();

    virtual void setRotation(float x, float y, float angle);
    virtual void clearRotation();

    virtual void setScale(float scaleX, float scaleY);
    virtual void clearScale();

    virtual void setTranslation(float transX, float transY);
    virtual void clearTranslation();

    virtual void setScreenTranslation(float transX, float transY);
    virtual void clearScreenTranslation();

    virtual void setColor(unsigned int red,
                unsigned int green,
                unsigned int blue,
                unsigned int alpha);

    virtual void setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue);

    virtual void setPointSize(float size);

    virtual void setLineWidth(float width);

    virtual void clear();

    virtual void drawPoint(float x, float y);

    virtual void drawLine(float x1, float y1, float x2, float y2);

    virtual void drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3);

    virtual void drawSquare(float x,
                    float y,
                    float side);

    virtual void drawRectangle(float x,
                    float y,
                    float width,
                    float height);

    virtual void drawCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0.0f,
                    float endAngle=(M_PI * 2));

    virtual void drawEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle=0.0f,
                    float endAngle=(M_PI * 2));

    virtual void fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3);

    virtual void fillSquare(float x,
                    float y,
                    float side);

    virtual void fillRectangle(float x,
                    float y,
                    float width,
                    float height);

    virtual void fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0.0f,
                    float endAngle=(M_PI * 2));

    virtual void fillEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle=0.0f,
                    float endAngle=(M_PI * 2));

    virtual void drawLayer(Layer* layer,
                float x=0.0f,
                float y=0.0f,
                float width=0.0f,
                float height=0.0f);

    virtual void drawText(float x, float y, string text);

    virtual void _initEmpty(int width, int height);
    virtual void _loadImage(string filePath);
    void _setClearOnUpdate(bool clear){mClearOnUpdate = clear;}

protected:
    void lock();
    void unlock();

    bool mLocked;

    static Layer2DOpenGL* mWorkingLayer;

    GLuint mTexture;

    int mTextureWidth;
    int mTextureHeight;

    bool mClearOnUpdate;
    bool mFirstUnlock;

    float mfRed;
    float mfGreen;
    float mfBlue;

    bool mRotate;
    float mRotX;
    float mRotY;
    float mRotAngle;

    bool mScale;
    float mScaleX;
    float mScaleY;

    bool mTranslate;
    float mTransX;
    float mTransY;

    bool mScreenTranslate;
    float mScreenTransX;
    float mScreenTransY;
};

}

#endif

