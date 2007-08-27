/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "WindowSDLOpenGL.h"
#include "LayerOpenGL.h"
#include "PycassoException.h"

#include "SDL.h"
#include "SDL_opengl.h" 

namespace pyc
{

WindowSDLOpenGL::WindowSDLOpenGL()
{
}

WindowSDLOpenGL::~WindowSDLOpenGL()
{
}

void WindowSDLOpenGL::init(int width,
				int height,
				bool fullScreen,
				int colorDepth,
				bool resizable,
				bool windowDecorations)
{
	Window::init(width, height, colorDepth, fullScreen, resizable, windowDecorations);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		PycassoException exception(EXCEPTION_INITIALIZATION, SDL_GetError());
		throw exception;
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
		PycassoException exception(EXCEPTION_INITIALIZATION, SDL_GetError());
		throw exception;
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

	mRootLayer = new LayerOpenGL();
	mRootLayer->_setRoot(mWidth, mHeight);
}

void WindowSDLOpenGL::update()
{
	SDL_GL_SwapBuffers();

	if (mClearOnUpdate)
	{
		mRootLayer->clear();
	}
}

void WindowSDLOpenGL::setTitle(std::string title)
{
	SDL_WM_SetCaption(title.c_str(), NULL);
}

void WindowSDLOpenGL::showCursor(bool show)
{
	if (show)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
}

Layer* WindowSDLOpenGL::createLayer(int width, int height)
{
	LayerOpenGL* layer = new LayerOpenGL();

        try
        {
                layer->_initEmpty(width, height);
        }
        catch (PycassoException exception)
        {
                delete layer;
                throw exception;
        }

        mLayers.push_back(layer);

        return layer;
}

Layer* WindowSDLOpenGL::createPNGLayer(std::string filePath)
{
        LayerOpenGL* layer = new LayerOpenGL();

        try
        {
                layer->_loadPNG(filePath);
        }
        catch (PycassoException exception)
        {
                delete layer;
                throw exception;
        }

        mLayers.push_back(layer);

        return layer;
}

void WindowSDLOpenGL::setClearOnUpdate(bool clear)
{
	Window::setClearOnUpdate(clear);
}

}

