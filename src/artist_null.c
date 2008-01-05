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

int art_init(int width,
                int height,
                int fullScreen,
                int colorDepth,
                int resizable,
                int windowDecorations)
{
    _art_sessionInit();

    Art_Layer* rootLayer = malloc(sizeof(Art_Layer));
    _art_initLayer(rootLayer);
    _art_setRoot(rootLayer, width, height);

    artG_session.rootLayer = rootLayer;
    artG_session.currentLayer = NULL;

    art_drawToRoot();
}

void art_update()
{
}

void art_setWinTitle(char* title)
{
}

void art_showCursor(int show)
{
}

char* systemName()
{
    return "Null";
}

