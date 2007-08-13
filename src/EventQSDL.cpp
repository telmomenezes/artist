/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "EventQSDL.h"
#include "SDL.h"

namespace pyc
{

EventQSDL::EventQSDL()
{
}

EventQSDL::~EventQSDL()
{
}

bool EventQSDL::init()
{
	return true;
}

bool EventQSDL::next()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_QUIT:
				mType = pyc::Quit;
				break;
			default:
				break;
                }

		return true;
        }
	else
	{
		return false;
	}
}

}

