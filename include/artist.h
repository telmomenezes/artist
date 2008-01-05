/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_ARTIST_H)
#define __INCLUDE_ARTIST_H

#include "artist_types.h"
#include "eventq.h"
#include "layer.h"
#include "font.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int windowWidth;
    int windowHeight;
    Art_Layer* rootLayer;
    Art_Layer* currentLayer;
    int clearOnUpdate;
    Art_Layer* layers;
    Art_Font* fonts;
    Art_EventData eventData;
} Art_Session;

extern Art_Session artG_session;

int art_init(int width,
                int height,
                int fullScreen,
                int colorDepth,
                int resizable,
                int windowDecorations);

int art_initSimple(int width,
                int height,
                int fullScreen);

int art_close();

double art_getTime();

void art_update();

void art_setWinTitle(char* title);

int art_getWinWidth();
int art_getWinHeight();

void art_showCursor(int show);

Art_Layer* art_createLayer(int width, int height);
Art_Layer* art_loadImage(char* filePath);
int art_removeLayer(Art_Layer* layer);

Art_Font* art_loadFont(char* fontName, unsigned int height);
int art_removeFont(Art_Font* font);

void art_setClearWindowOnUpdate(int clear);

char* art_systemName();

int art_drawToLayer(Art_Layer* layer);
int art_drawToRoot();

void _art_sessionInit();

#ifdef __cplusplus
}
#endif

#endif

