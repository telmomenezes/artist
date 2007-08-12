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
#include <string>

#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
#include "ScreenSDLOpenGL.h"
#endif

namespace pyc
{

System Pycasso::mDefaultSystem = NullSystem;
System Pycasso::mPreferredSystem = NullSystem;
bool Pycasso::mSystemSDLOpenGL = false;
Canvas* Pycasso::mScreen = NULL;

Pycasso::Pycasso()
{
	mDefaultSystem = NullSystem;
#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
	mSystemSDLOpenGL = true;
	mDefaultSystem = SDLOpenGL;
#else
	mSystemSDLOpenGL = false;
#endif
	
	mPreferredSystem = mDefaultSystem;

	mScreen = NULL;
}

Pycasso::~Pycasso()
{
	if (mScreen)
	{
		delete mScreen;
		mScreen = NULL;
	}
}

Canvas* Pycasso::createScreen(int width,
					int height,
					bool fullScreen,
					int colorDepth,
					bool resizable,
					bool windowDecorations)
{
	std::string exception = "Exception test.";
	throw(exception);

	switch (mPreferredSystem)
	{
#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
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
					fullScreen,
					colorDepth,
					resizable,
					windowDecorations))
		{
			delete mScreen;
			mScreen = NULL;
		}
	}

	return mScreen;
}

void Pycasso::destroyScreen()
{
	if (mScreen)
	{
		delete mScreen;
		mScreen = NULL;
	}
}

bool Pycasso::setPreferredSystem(System sys)
{
	switch (sys)
	{
		case NullSystem:
			mPreferredSystem = NullSystem;
			return true;
		case SDLOpenGL:
			if (mSystemSDLOpenGL)
			{
				mPreferredSystem = SDLOpenGL;
				return true;
			}
			else
			{
				return false;
			}
		default:
			return false;
	}
}

}

