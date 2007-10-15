/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if defined(__PYCASSO_OS_WIN32)
#include <windows.h>
#endif

#include "WindowSDLOpenGL.h"
#include "Layer2DOpenGL.h"
#include "FontOpenGL.h"

#include "SDL.h"
#include "SDL_opengl.h" 

#include <stdexcept>

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
        throw std::runtime_error(SDL_GetError());
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
        throw std::runtime_error(SDL_GetError());
    }

    mRootLayer = new Layer2DOpenGL();
    mRootLayer->_setRoot(mWidth, mHeight);
    ((Layer2DOpenGL*)mRootLayer)->_setClearOnUpdate(mClearOnUpdate);
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

Layer2D* WindowSDLOpenGL::createLayer2D(int width, int height)
{
    Layer2DOpenGL* layer = new Layer2DOpenGL();

    try
    {
        layer->_initEmpty(width, height);
    }
    catch (std::runtime_error exception)
    {
        delete layer;
        throw exception;
    }

    mLayers.push_back(layer);

    return layer;
}

Layer2D* WindowSDLOpenGL::loadImage(std::string filePath)
{
    Layer2DOpenGL* layer = new Layer2DOpenGL();

    try
    {
        layer->_loadImage(filePath);
    }
    catch (std::runtime_error exception)
    {
        delete layer;
        throw exception;
    }

    mLayers.push_back(layer);

    return layer;
}

Font* WindowSDLOpenGL::loadFont(string fontName, unsigned int height)
{
    FontOpenGL* font = new FontOpenGL();
    font->init(fontName, height);

    mFonts.push_back(font);

    return font;
}

void WindowSDLOpenGL::setClearOnUpdate(bool clear)
{
    Window::setClearOnUpdate(clear);

    if (mRootLayer != NULL)
    {
        // TODO: this needs to be changed when 3D layers get introduced
        ((Layer2DOpenGL*)mRootLayer)->_setClearOnUpdate(clear);
    }
}

}

