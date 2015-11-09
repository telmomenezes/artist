/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "artist.h"
#include <stdio.h>

#if defined (__ARTIST_OS_OSX)
#include <OpenGL/OpenGL.h>
#else
#include "SDL_opengl.h"
#endif

#include "SDL.h"

int art_init(int width,
                int height,
                int fullScreen,
                int colorDepth,
                int resizable,
                int windowDecorations,
                int vsync)
{
    _art_sessionInit();

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return -1;
        //TODO: Set error SDL_GetError()
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
        return -1;
        //TODO: Set error SDL_GetError()
    }

    artG_session.windowWidth = width;
    artG_session.windowHeight = height;

    Art_Layer* rootLayer = malloc(sizeof(Art_Layer));
    _art_initLayer(rootLayer);
    _art_setRoot(rootLayer, width, height);
    art_setClearLayerOnUpdate(rootLayer, artG_session.clearOnUpdate);

    artG_session.rootLayer = rootLayer;
    artG_session.currentLayer = NULL;

    art_drawToRoot();

    if (vsync)
    {
        // Activate vertical refresh synch on macs
        #if defined (__ARTIST_OS_OSX)
        GLint VBL = 1;
        CGLSetParameter(CGLGetCurrentContext(),  kCGLCPSwapInterval, &VBL);
        #endif
    }

    return 0;
}

void art_update()
{
    SDL_GL_SwapBuffers();

    if (artG_session.rootLayer->clearOnUpdate)
    {
        art_drawToRoot();
        art_clear();
    }
}

void art_setWinTitle(const char* title)
{
    SDL_WM_SetCaption(title, NULL);
}

void art_showCursor(int show)
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

char* art_systemName()
{
    return "SDLOpenGL";
}

