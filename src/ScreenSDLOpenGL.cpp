/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "ScreenSDLOpenGL.h"

#include "SDL.h"
#include "SDL_opengl.h" 

namespace pyc
{

ScreenSDLOpenGL::ScreenSDLOpenGL()
{
}

ScreenSDLOpenGL::~ScreenSDLOpenGL()
{
}

bool ScreenSDLOpenGL::init(int width,
				int height,
				bool fullScreen,
				int colorDepth,
				bool resizable,
				bool windowDecorations)
{
	if (!Canvas::init(width, height, colorDepth, fullScreen, resizable, windowDecorations))
	{
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		//printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}
 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	unsigned int flags = SDL_OPENGL;

	if (fullScreen)
	{
		flags |= SDL_FULLSCREEN; 
	}

	if (resizable)
	{
		flags |= SDL_RESIZABLE;
	}

	if (!windowDecorations)
	{
		flags |= SDL_NOFRAME;
	}

	if (SDL_SetVideoMode(width, height, colorDepth, flags) == NULL)
	{
		return false;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glViewport(0, 0, mWidth, mHeight);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0.0f, mWidth, mHeight, 0.0f, -1.0f, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

	return true;
}

void ScreenSDLOpenGL::setCaption(std::string caption)
{
	SDL_WM_SetCaption(caption.c_str(), NULL);
}

void ScreenSDLOpenGL::beginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void ScreenSDLOpenGL::endFrame()
{
	SDL_GL_SwapBuffers();
}

}

