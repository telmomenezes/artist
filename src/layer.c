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
    layer->currentFont = NULL;
    layer->currentTexture = NULL;
    layer->texScale = 1.0f;
    layer->texX = 0.0f;
    layer->texY = 0.0f;
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

void art_setTexture(Art_Layer* layer)
{
    art_clearTexture();
    artG_session.currentLayer->currentTexture = layer;
}

void art_setTextureScale(float scale)
{
    artG_session.currentLayer->texScale = fabsf(scale);
}

void art_setTexturePosition(float x, float y)
{
    artG_session.currentLayer->texX = x;
    artG_session.currentLayer->texY = y;
}

void art_clearTexture()
{
    artG_session.currentLayer->currentTexture = NULL;
    artG_session.currentLayer->texScale = 1.0f;
    artG_session.currentLayer->texX = 0.0f;
    artG_session.currentLayer->texY = 0.0f;
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

void art_drawCircle(float x,
                    float y,
                    float rad)
{
    art_drawCircleSlice(x, y, rad, 0, 6.283185307179586f);
}

void art_drawEllipse(float x,
                    float y,
                    float radX,
                    float radY)
{
    art_drawEllipseSlice(x, y, radX, radY, 0, 6.283185307179586f);
}

void art_fillCircle(float x,
                    float y,
                    float rad)
{
    art_fillCircleSlice(x, y, rad, 0, 6.283185307179586f);
}

void art_fillEllipse(float x,
                    float y,
                    float radX,
                    float radY)
{
    art_fillEllipseSlice(x, y, radX, radY, 0, 6.283185307179586f);
}

