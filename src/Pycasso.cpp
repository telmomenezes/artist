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
#include <stdexcept>

#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
#include "WindowSDLOpenGL.h"
#include "EventQSDL.h"
#endif

#if defined(__PYCASSO_COMPILER_GCC)
#include <sys/time.h>
#endif

#if defined(__PYCASSO_COMPILER_CL)
#include <windows.h>
#define EPOCHFILETIME (116444736000000000i64)
#endif

namespace pyc
{

System Pycasso::mDefaultSystem = SYSTEM_NULL;
System Pycasso::mPreferredSystem = SYSTEM_NULL;
bool Pycasso::mSystemSDLOpenGL = false;
Window* Pycasso::mWindow = NULL;
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

	mWindow = NULL;
}

Pycasso::~Pycasso()
{
	if (mWindow)
	{
		delete mWindow;
		mWindow = NULL;
	}

	if (mEventQ)
	{
		delete mEventQ;
		mEventQ = NULL;
	}
}

Window* Pycasso::createWindow(int width,
					int height,
					bool fullScreen,
					int colorDepth,
					bool resizable,
					bool windowDecorations)
{
	if (mWindow)
	{
		throw std::runtime_error("Window already created");
	}

	switch (mPreferredSystem)
	{
#if defined(__PYCASSO_SYSTEM_SDLOPENGL)
	case SYSTEM_SDL_OPENGL:
		mWindow = new WindowSDLOpenGL();
		break;
#endif
	default:
		mWindow = NULL;
	}

	if (mWindow != NULL)
	{
		try
		{
			mWindow->init(width,
					height,
					fullScreen,
					colorDepth,
					resizable,
					windowDecorations);
		}
		catch (std::runtime_error exception)
		{
			delete mWindow;
			mWindow = NULL;
			throw exception;
		}
	}

	return mWindow;
}

Window* Pycasso::getWindow()
{
	if (!mWindow)
	{
		throw std::runtime_error("Window not created");
	}

	return mWindow;
}

EventQ* Pycasso::createEventQ()
{
	if (mEventQ)
	{
		throw std::runtime_error("Event queue already created");
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
		}
	}

	return mEventQ;
}

EventQ* Pycasso::getEventQ()
{
	if (!mEventQ)
	{
		throw std::runtime_error("Event queue not created");
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

#if !defined(__PYCASSO_COMPILER_GCC)
double Pycasso::getTime()
{
    FILETIME ft;
    LARGE_INTEGER li;
    __int64 t;
    static int tzflag;

    GetSystemTimeAsFileTime(&ft);
    li.LowPart  = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    t  = li.QuadPart;
    t -= EPOCHFILETIME;
    t /= 10;
    return ((double)t) / 1000000.0f;
}
#else
double Pycasso::getTime()
{
    timeval time;
    gettimeofday(&time, NULL);

    double seconds = (double)time.tv_sec;
    seconds += ((double)time.tv_usec) / 1000000.0f;
    return seconds;
}
#endif

}

