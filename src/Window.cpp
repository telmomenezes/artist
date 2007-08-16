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
	mLayer = NULL;
}

Window::~Window()
{
	if (mLayer != NULL)
	{
		delete mLayer;
		mLayer = NULL;
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

Layer* Window::getLayer()
{
	if (mLayer == NULL)
	{
		std::string errorText = "Window not initialized";
		throw errorText;
		return NULL;
	}

	return mLayer;
}

}

