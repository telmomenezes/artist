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
#include "EventQSDL.h"
#endif

namespace pyc
{

System Pycasso::mDefaultSystem = SYSTEM_NULL;
System Pycasso::mPreferredSystem = SYSTEM_NULL;
bool Pycasso::mSystemSDLOpenGL = false;
Canvas* Pycasso::mScreen = NULL;
EventQ* Pycasso::mEventQ = NULL;

Pycasso::Pycasso()
{
	mDefaultSystem = SYSTEM_NULL;
#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
	mSystemSDLOpenGL = true;
	mDefaultSystem = SYSTEM_SDL_OPENGL;
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

	if (mEventQ)
	{
		delete mEventQ;
		mEventQ = NULL;
	}
}

Canvas* Pycasso::createScreen(int width,
					int height,
					bool fullScreen,
					int colorDepth,
					bool resizable,
					bool windowDecorations)
{
	if (mScreen)
	{
		std::string errorStr = "Screen already created";
		throw errorStr;
		return false;
	}

	switch (mPreferredSystem)
	{
#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
	case SYSTEM_SDL_OPENGL:
		mScreen = new ScreenSDLOpenGL();
		break;
#endif
	default:
		mScreen = NULL;
	}

	if (mScreen != NULL)
	{
		try
		{
			mScreen->init(width,
					height,
					fullScreen,
					colorDepth,
					resizable,
					windowDecorations);
		}
		catch (std::string exception)
		{
			delete mScreen;
			mScreen = NULL;
			throw exception;
			return NULL;
		}
	}

	return mScreen;
}

Canvas* Pycasso::getScreen()
{
	if (!mScreen)
	{
		std::string errorStr = "Screen not created";
		throw errorStr;
		return NULL;
	}

	return mScreen;
}

EventQ* Pycasso::createEventQ()
{
	if (mEventQ)
	{
		std::string errorStr = "Event queue already created";
		throw errorStr;
		return false;
	}

	switch (mPreferredSystem)
	{
#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
	case SYSTEM_SDL_OPENGL:
		mEventQ = new EventQSDL();
		break;
#endif
	default:
		mEventQ = NULL;
	}

	if (mEventQ != NULL)
	{
		try
		{
			mEventQ->init();
		}
		catch (std::string exception)
		{
			delete mEventQ;
			mEventQ = NULL;
			throw exception;
			return NULL;
		}
	}

	return mEventQ;
}

EventQ* Pycasso::getEventQ()
{
	if (!mEventQ)
	{
		std::string errorStr = "Event queue not created";
		throw errorStr;
		return NULL;
	}

	return mEventQ;
}

bool Pycasso::setPreferredSystem(pyc::System sys)
{
	switch (sys)
	{
		case SYSTEM_NULL:
			mPreferredSystem = SYSTEM_NULL;
			return true;
		case SYSTEM_SDL_OPENGL:
			if (mSystemSDLOpenGL)
			{
				mPreferredSystem = SYSTEM_SDL_OPENGL;
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

