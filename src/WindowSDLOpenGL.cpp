/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "WindowSDLOpenGL.h"
#include "LayerSDLOpenGL.h"

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

bool WindowSDLOpenGL::init(int width,
				int height,
				bool fullScreen,
				int colorDepth,
				bool resizable,
				bool windowDecorations)
{
	try
	{
		Window::init(width, height, colorDepth, fullScreen, resizable, windowDecorations);
	}
	catch (std::string exception)
	{
		throw exception;
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		char errorText[255];
		sprintf(errorText, "Unable to initialize SDL: %s\n", SDL_GetError());
		std::string errorStr = errorText;
		throw errorText;
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
		char errorText[255];
		sprintf(errorText, "Unable to set SDL video mode: %s\n", SDL_GetError());
		std::string errorStr = errorText;
		throw errorText;
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

	mRootLayer = new LayerSDLOpenGL();
	mRootLayer->_setRoot(mWidth, mHeight);

	return true;
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
	LayerSDLOpenGL* layer = new LayerSDLOpenGL();

        try
        {
                layer->_initEmpty(width, height);
        }
        catch (std::string exception)
        {
                delete layer;
                throw exception;
                return NULL;
        }

        mLayers.push_back(layer);

        return layer;
}

Layer* WindowSDLOpenGL::createPNGLayer(std::string filePath)
{
        LayerSDLOpenGL* layer = new LayerSDLOpenGL();

        try
        {
                layer->_loadPNG(filePath);
        }
        catch (std::string exception)
        {
                delete layer;
                throw exception;
                return NULL;
        }

        mLayers.push_back(layer);

        return layer;
}

}

