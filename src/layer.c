/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "layer.h"
#include "artist.h"
#include <stdio.h>

void _art_initLayer(Art_Layer* layer)
{
    layer->width = 0;
    layer->height = 0;
    layer->isRoot = 0;
    layer->red = 255;
    layer->green = 255;
    layer->blue = 255;
    layer->alpha = 255;
    layer->curveAngleStep = 0.1f;
    layer->clearOnUpdate = 1;
    layer->prevLayer = NULL;
    layer->nextLayer = NULL;

    _art_initExtraLayerData(layer);
}

void _art_setRoot(Art_Layer* layer, int width, int height)
{
    layer->width = width;
    layer->height = height;
    layer->isRoot = 1;
}

int art_getLayerWidth()
{
    return artG_session.currentLayer->width;
}

int art_getLayerHeight()
{
    return artG_session.currentLayer->height;
}

void art_setCurveAngleStep(float angle)
{
    artG_session.currentLayer->curveAngleStep = angle;
}


int art_isRoot()
{
    return artG_session.currentLayer->isRoot;
}

void art_setFont(Art_Font* font)
{
    artG_session.currentLayer->currentFont = font;
}

void art_setClearLayerOnUpdate(Art_Layer* layer, int clear)
{
    layer->clearOnUpdate = clear;
}

void art_drawLayer(Art_Layer* layer, float x, float y)
{
    art_drawScaledLayer(layer, x, y, 0, 0);
}

