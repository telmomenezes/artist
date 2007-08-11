/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Pycasso.h"
#include <stdio.h>

#if defined(__LAYER_SDLOPENGL)
#include "ScreenSDLOpenGL.h"
#endif

namespace pyc
{

Pycasso::Pycasso()
{
	mScreen = NULL;
}

Pycasso::~Pycasso()
{
}

Canvas* Pycasso::createScreen(ScreenType type,
					int width,
					int height,
					int colorDepth,
					bool fullScreen,
					bool resizable,
					bool windowDecorations)
{
	switch (type)
	{
#if defined(__LAYER_SDLOPENGL)
	case SDLOpenGL:
		mScreen = new ScreenSDLOpenGL();
		break;
#endif
	default:
		mScreen = NULL;
	}

	if (mScreen != NULL)
	{
		if (!mScreen->init(width,
					height,
					colorDepth,
					fullScreen,
					resizable,
					windowDecorations))
		{
			delete mScreen;
			mScreen = NULL;
		}
	}

	return mScreen;
}

}

