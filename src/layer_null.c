/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "layer.h"
#include <stdio.h>

void _art_initExtraLayerData(Art_Layer* layer)
{
    layer->extraData = NULL;
}

void _art_destroyLayer(Art_Layer* layer)
{
}

void _art_layerUnlock(Art_Layer* layer)
{
}

void _art_layerLock(Art_Layer* layer)
{
}

void art_setRotation(float x, float y, float angle)
{
}

void art_clearRotation()
{
}

void art_setScale(float scaleX, float scaleY)
{
}

void art_clearScale()
{
}

void art_setTranslation(float transX, float transY)
{
}

void art_clearTranslation()
{
}

void art_setScreenTranslation(float transX, float transY)
{
}

void art_clearScreenTranslation()
{
}

void art_setColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue,
                    unsigned int alpha)
{
}

void art_setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue)
{
}

void art_setPointSize(float size)
{
}

void art_setLineWidth(float width)
{
}

void art_clear()
{
}

void art_drawPoint(float x, float y)
{
}

void art_drawLine(float x1, float y1, float x2, float y2)
{
}

void art_drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
}

void art_drawSquare(float x,
                float y,
                float side)
{
}

void art_drawRectangle(float x,
                float y,
                float width,
                float height)
{
}

void art_drawCircleSlice(float x,
                float y,
                float rad,
                float beginAngle,
                float endAngle)
{
}

void art_drawEllipseSlice(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle)
{
}

void art_fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
}

void art_fillSquare(float x,
                    float y,
                    float side)
{
}

void art_fillRectangle(float x,
                float y,
                float width,
                float height)
{
}

void art_fillCircleSlice(float x,
                    float y,
                    float rad,
                    float beginAngle,
                    float endAngle)
{
}

void art_fillEllipseSlice(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle)
{
}

void art_drawScaledLayer(Art_Layer* layer,
        float x,
        float y,
        float width,
        float height)
{
}

int _art_initEmptyLayer(Art_Layer* layer, int width, int height)
{
    return 0;
}

int _art_loadImageLayer(Art_Layer* layer, char* filePath)
{
    return 0;
}

int art_drawText(float x, float y, char* text)
{
    return 0;
}

void art_drawPixels(char* pixels)
{
}

