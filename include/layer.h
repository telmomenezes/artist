/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_ARTIST_LAYER_H)
#define __INCLUDE_ARTIST_LAYER_H

#include "font.h"
#include <math.h>

#if defined(__ARTIST_COMPILER_CL)
#define M_PI 3.14159265f
#endif

typedef struct
{
    int width;
    int height;
    int isRoot;
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;
    float curveAngleStep;
    Art_Font* currentFont;
    int clearOnUpdate;
    void* extraData;
    void* prevLayer;
    void* nextLayer;
} Art_Layer;

int art_getLayerWidth();
int art_getLayerHeight();

void art_setColor(unsigned int red,
                unsigned int green,
                unsigned int blue,
                unsigned int alpha);
void art_setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue);

void art_setPointSize(float size);
void art_setLineWidth(float width);

void art_setCurveAngleStep(float angle);

void art_clear();

int art_isRoot();

void art_setRotation(float x, float y, float angle);
void art_clearRotation();

void art_setScale(float scaleX, float scaleY);
void art_clearScale();

void art_setTranslation(float transX, float transY);
void art_clearTranslation();

void art_setScreenTranslation(float transX, float transY);
void art_clearScreenTranslation();

void art_drawPoint(float x, float y);

void art_drawLine(float x1, float y1, float x2, float y2);

void art_drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3);

void art_drawSquare(float x,
                    float y,
                    float side);

void art_drawRectangle(float x,
                    float y,
                    float width,
                    float height);

void art_drawCircle(float x,
                    float y,
                    float rad,
                    float beginAngle,
                    float endAngle);

void art_drawEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle);

void art_fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3);

void art_fillSquare(float x,
                    float y,
                    float side);

void art_fillRectangle(float x,
                    float y,
                    float width,
                    float height);

void art_fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle,
                    float endAngle);

void art_fillEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle);

void art_drawLayer(Art_Layer* layer, float x, float y);

void art_drawScaledLayer(Art_Layer* layer,
                    float x,
                    float y,
                    float width,
                    float height);

void art_setFont(Art_Font* font);

int art_drawText(float x, float y, char* text);

void art_setClearLayerOnUpdate(Art_Layer* layer, int clear);

void _art_initLayer(Art_Layer* layer);
void _art_initExtraLayerData(Art_Layer* layer);
void _art_destroyLayer(Art_Layer* layer);
void _art_setRoot(Art_Layer* layer, int width, int height);
void _art_layerLock(Art_Layer* layer);
void _art_layerUnlock(Art_Layer* layer);
int _art_initEmptyLayer(Art_Layer* layer, int width, int height);
int _art_loadImageLayer(Art_Layer* layer, char* filePath);

#endif

