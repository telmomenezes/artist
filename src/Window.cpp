/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Window.h"

#include <stdexcept>

namespace art
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

Layer2D* Window::getRootLayer2D()
{
	if (mRootLayer == NULL)
	{
		throw std::runtime_error("Window not initialized");
	}

    // TODO: This needs to be changed when 3D layers get introduced
	return (Layer2D*)mRootLayer;
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

