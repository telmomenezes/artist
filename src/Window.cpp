/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Window.h"

namespace pyc
{

Window::Window()
{
	mRootLayer = NULL;
}

Window::~Window()
{
	if (mRootLayer != NULL)
	{
		delete mRootLayer;
		mRootLayer = NULL;
	}
        
        for (std::list<Layer*>::iterator iterLayer = mLayers.begin();
                iterLayer != mLayers.end();
                iterLayer++)
        {
                delete (*iterLayer);
        }
}

bool Window::init(int width,
			int height,
			bool fullScreen,
			int colorDepth,
			bool resizable,
			bool windowDecorations)
{
	mWidth = width;
	mHeight = height;

	return true;
}

Layer* Window::getRootLayer()
{
	if (mRootLayer == NULL)
	{
		std::string errorText = "Window not initialized";
		throw errorText;
		return NULL;
	}

	return mRootLayer;
}

bool Window::removeLayer(Layer* layer)
{
        for (std::list<Layer*>::iterator iterLayer = mLayers.begin();
                iterLayer != mLayers.end();
                iterLayer++)
        {
                mLayers.erase(iterLayer);
                delete (*iterLayer);
                return true;
        }

        return false;
}

}

