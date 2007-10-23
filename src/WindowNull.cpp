/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if defined(__PYCASSO_OS_WIN32)
#include <windows.h>
#endif

#include "WindowNull.h"
#include "Layer2DNull.h"
#include "FontNull.h"

namespace pyc
{

WindowNull::WindowNull()
{
}

WindowNull::~WindowNull()
{
}

void WindowNull::init(int width,
                int height,
                bool fullScreen,
                int colorDepth,
                bool resizable,
                bool windowDecorations)
{
    Window::init(width, height, colorDepth, fullScreen, resizable, windowDecorations);

    mRootLayer = new Layer2DNull();
    mRootLayer->_setRoot(mWidth, mHeight);
}

Layer2D* WindowNull::createLayer2D(int width, int height)
{
    Layer2DNull* layer = new Layer2DNull();
    mLayers.push_back(layer);
    return layer;
}

Layer2D* WindowNull::loadImage(std::string filePath)
{
    Layer2DNull* layer = new Layer2DNull();
    return layer;
}

Font* WindowNull::loadFont(string fontName, unsigned int height)
{
    FontNull* font = new FontNull();
    font->init(fontName, height);

    mFonts.push_back(font);

    return font;
}

}

