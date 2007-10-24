/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_PYCASSO_WINDOW_H)
#define __INCLUDE_PYCASSO_WINDOW_H

#include "Layer.h"
#include "Layer2D.h"
#include "Font.h"

#include <string>
#include <list>

namespace pyc
{

using std::string;
using std::list;

class Window
{
public:
    Window();
    virtual ~Window();

    virtual void init(int width,
                        int height,
                        bool fullScreen=false,
                        int colorDepth=0,
                        bool resizable=false,
                        bool windowDecorations=true);

    virtual void update()=0;

    virtual void setTitle(string title)=0;

    int getWidth(){return mWidth;}
    int getHeight(){return mHeight;}

    Layer2D* getRootLayer2D();

    virtual void showCursor(bool show)=0;

    virtual Layer2D* createLayer2D(int width, int height)=0;
    virtual Layer2D* loadImage(string filePath)=0;
    bool removeLayer(Layer* layer);

    virtual Font* loadFont(string fontName, unsigned int height)=0;
    bool removeFont(Font* font);

    virtual void setClearOnUpdate(bool clear){mClearOnUpdate = clear;}

    virtual bool isReal()=0;

protected:
    int mWidth;
    int mHeight;
    Layer* mRootLayer;
    list<Layer*> mLayers;
    list<Font*> mFonts;
    bool mClearOnUpdate;
};

}

#endif

