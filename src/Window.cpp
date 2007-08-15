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
	mMainCanvas = NULL;
}

Window::~Window()
{
	if (mMainCanvas != NULL)
	{
		delete mMainCanvas;
		mMainCanvas = NULL;
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

Canvas* Window::getMainCanvas()
{
	if (mMainCanvas == NULL)
	{
		std::string errorText = "Window not initialized";
		throw errorText;
		return NULL;
	}

	return mMainCanvas;
}

}

