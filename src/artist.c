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
#include <stdlib.h>

#if defined(__ARTIST_COMPILER_GCC)
#include <sys/time.h>
#endif

#if defined(__ARTIST_COMPILER_CL)
#include <windows.h>
#define EPOCHFILETIME (116444736000000000i64)
#endif

Art_Session artG_session;

int art_initSimple(int width,
                    int height,
                    int fullScreen)
{
    return art_init(width, height, fullScreen, 0, 0, 1, 1);
}

void _art_sessionInit()
{
    artG_session.windowWidth = 0;
    artG_session.windowHeight = 0;
    artG_session.clearOnUpdate = 1;
    artG_session.layers = NULL;
    artG_session.fonts = NULL;
    artG_session.currentLayer = NULL;
    artG_session.rootLayer = NULL;
}

#if !defined(__ARTIST_COMPILER_GCC)
double art_getTime()
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
double art_getTime()
{
    struct timeval time;
    gettimeofday(&time, NULL);

    double seconds = (double)time.tv_sec;
    seconds += ((double)time.tv_usec) / 1000000.0f;
    return seconds;
}
#endif

Art_Layer* art_createLayer(int width, int height)
{
    Art_Layer* layer = (Art_Layer*)malloc(sizeof(Art_Layer));
    _art_initLayer(layer);

    if (_art_initEmptyLayer(layer, width, height) != 0)
    {
        free(layer);
        return NULL;
    }


    if (artG_session.layers != NULL)
    {
        artG_session.layers->prevLayer = layer;
    }    
    layer->nextLayer = artG_session.layers;
    layer->prevLayer = NULL;
    artG_session.layers = layer;

    return layer;
}

Art_Layer* art_loadImage(char* filePath)
{
    Art_Layer* layer = malloc(sizeof(Art_Layer));
    _art_initLayer(layer);

    if (_art_loadImageLayer(layer, filePath) != 0)
    {
        free(layer);
        return NULL;
    }

    if (artG_session.layers != NULL)
    {
        artG_session.layers->prevLayer = layer;
    }
    layer->nextLayer = artG_session.layers;
    layer->prevLayer = NULL;
    artG_session.layers = layer;

    return layer;
}

Art_Font* art_loadFont(char* fontName, unsigned int height)
{
    Art_Font* font = malloc(sizeof(Art_Font));
    _art_initFont(font, fontName, height);

    if (artG_session.fonts != NULL)
    {
        artG_session.fonts->prevFont = font;
    }
    font->nextFont = artG_session.fonts;
    font->prevFont = NULL;
    artG_session.fonts = font;

    return font;
}

int art_removeLayer(Art_Layer* layer)
{
    if (layer == NULL)
    {
        //TODO: set error
        return -1;
    }

    Art_Layer* nextLayer = (Art_Layer*)layer->nextLayer;
    Art_Layer* prevLayer = (Art_Layer*)layer->prevLayer;

    if (nextLayer != NULL)
    {
        nextLayer->prevLayer = prevLayer;
    }

    if (prevLayer == NULL)
    {
        artG_session.layers = nextLayer;
    }
    else
    {
        prevLayer->nextLayer = nextLayer;
    }

    _art_destroyLayer(layer);
    free(layer->extraData);
    free(layer);

    return 0;
}

int art_removeFont(Art_Font* font)
{
    if (font == NULL)
    {
        //TODO: set error
        return -1;
    }

    Art_Font* nextFont = (Art_Font*)font->nextFont;
    Art_Font* prevFont = (Art_Font*)font->prevFont;

    if (nextFont != NULL)
    {
        nextFont->prevFont = prevFont;
    }

    if (prevFont == NULL)
    {
        artG_session.fonts = nextFont;
    }
    else
    {
        prevFont->nextFont = nextFont;
    }

    _art_destroyFont(font);
    free(font->extraData);
    free(font);

    return 0;
}

void art_setClearWindowOnUpdate(int clear)
{
    artG_session.clearOnUpdate = clear;

    if (artG_session.rootLayer != NULL)
    {
        art_setClearLayerOnUpdate(artG_session.rootLayer, clear);
    }
}

int art_close()
{
    if (artG_session.rootLayer != NULL)
    {
        _art_destroyLayer(artG_session.rootLayer);
        free(artG_session.rootLayer->extraData);
        free(artG_session.rootLayer);
        artG_session.rootLayer = NULL;
    }

    Art_Layer* layer = (Art_Layer*)artG_session.layers;
    Art_Layer* nextLayer;
    
    while (layer != NULL)
    {
        nextLayer = (Art_Layer*)layer->nextLayer;
        _art_destroyLayer(layer);        
        free(layer->extraData);
        free(layer);
        layer = nextLayer;
    }

    Art_Font* font = (Art_Font*)artG_session.fonts;
    Art_Font* nextFont;
    
    while (font != NULL)
    {
        nextFont = (Art_Font*)font->nextFont;
        _art_destroyFont(font);        
        free(font->extraData);
        free(font);
        font = nextFont;
    }

    return 0;
}

int art_drawToLayer(Art_Layer* layer)
{
    if (layer == NULL)
    {
        // TODO: set error: layer is NULL
        return -1;
    }

    if (artG_session.currentLayer != layer)
    {
        _art_layerLock(artG_session.currentLayer);
        _art_layerUnlock(layer);
        artG_session.currentLayer = layer;
    }

    return 0;
}

int art_drawToRoot()
{
    if (artG_session.currentLayer != artG_session.rootLayer)
    {
        if (artG_session.currentLayer != NULL)
        {
            _art_layerLock(artG_session.currentLayer);
        }
        _art_layerUnlock(artG_session.rootLayer);
        artG_session.currentLayer = artG_session.rootLayer;
    }

    return 0;
}

int art_getWinWidth()
{
    return artG_session.windowWidth;
}

int art_getWinHeight()
{
    return artG_session.windowHeight;
}

