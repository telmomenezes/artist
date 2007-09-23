/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Window.h"
#include "PycassoException.h"

namespace pyc
{

Window::Window()
{
	mRootLayer = NULL;
	mClearOnUpdate = true;
}

Window::~Window()
{
	if (mRootLayer != NULL)
	{
		delete mRootLayer;
		mRootLayer = NULL;
	}
        
    for (list<Layer*>::iterator iterLayer = mLayers.begin();
            iterLayer != mLayers.end();
            iterLayer++)
    {
        delete (*iterLayer);
    }

    for (list<Font*>::iterator iterFont = mFonts.begin();
            iterFont != mFonts.end();
            iterFont++)
    {
        delete (*iterFont);
    }
}

void Window::init(int width,
			int height,
			bool fullScreen,
			int colorDepth,
			bool resizable,
			bool windowDecorations)
{
	mWidth = width;
	mHeight = height;
}

Layer* Window::getRootLayer()
{
	if (mRootLayer == NULL)
	{
		PycassoException exception(EXCEPTION_MISSING_OBJECT, "Window not initialized");
		throw exception;
	}

	return mRootLayer;
}

bool Window::removeLayer(Layer* layer)
{
        for (list<Layer*>::iterator iterLayer = mLayers.begin();
                iterLayer != mLayers.end();
                iterLayer++)
        {
                mLayers.erase(iterLayer);
                delete (*iterLayer);
                return true;
        }

        return false;
}

bool Window::removeFont(Font* font)
{
        for (list<Font*>::iterator iterFont = mFonts.begin();
                iterFont != mFonts.end();
                iterFont++)
        {
                mFonts.erase(iterFont);
                delete (*iterFont);
                return true;
        }

        return false;
}

}

