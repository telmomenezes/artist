/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "layer.h"
#include "layer_opengl.h"
#include "font_opengl.h"
#include "functions.h"
#include "artist.h"

#include "stb_image.h"

#define APPLY_TRANSFORMS(X, Y) \
    Art_LayerOpenGL* ed = (Art_LayerOpenGL*)artG_session.currentLayer->extraData; \
    glLoadIdentity(); \
    if(ed->screenTranslate) \
        glTranslatef(ed->screenTransX, ed->screenTransY, 0.0f); \
    if(ed->scale) \
        glScalef(ed->scaleX, ed->scaleY, 0.0f); \
    if(ed->translate) \
        glTranslatef(ed->transX, ed->transY, 0.0f); \
    if (ed->rotate) \
    { \
        float aX = X - ed->rotX; \
        float aY = Y - ed->rotY; \
        glTranslatef(ed->rotX, ed->rotY, 0.0f); \
        glRotatef(ed->rotAngle, 0.0f, 0.0f, 1.0f); \
        glTranslatef(aX, aY, 0.0f); \
    } \
    else \
    { \
        glTranslatef(X, Y, 0.0f); \
    }

#define APPLY_TEXTURE() \
    Art_Layer* tex = (Art_Layer*)artG_session.currentLayer->currentTexture; \
    float widthRatio = 0.0f; \
    float heightRatio = 0.0f; \
    float texX = 0.0f; \
    float texY = 0.0f; \
    if (tex == NULL) \
    { \
        glDisable(GL_TEXTURE_2D); \
    } \
    else \
    { \
        Art_LayerOpenGL* edTex = tex->extraData; \
        glBindTexture(GL_TEXTURE_2D, edTex->texture); \
        glEnable(GL_TEXTURE_2D); \
        widthRatio = edTex->widthRatio * artG_session.currentLayer->texScale; \
        heightRatio = edTex->heightRatio * artG_session.currentLayer->texScale; \
        texX = artG_session.currentLayer->texX * widthRatio; \
        texY = artG_session.currentLayer->texY * heightRatio; \
    } \

void _art_initExtraLayerData(Art_Layer* layer)
{
    Art_LayerOpenGL* layerOGL = malloc(sizeof(Art_LayerOpenGL));
    layerOGL->locked = 1;
    layerOGL->texture = 0;
    layerOGL->textureWidth = 0;
    layerOGL->textureHeight = 0;
    layerOGL->firstUnlock = 1;
    layerOGL->fRed = 1.0f;
    layerOGL->fGreen = 1.0f;
    layerOGL->fBlue = 1.0f;
    layerOGL->rotate = 0;
    layerOGL->rotX = 0;
    layerOGL->rotY = 0;
    layerOGL->rotAngle = 0;
    layerOGL->scale = 0;
    layerOGL->scaleX = 1.0f;
    layerOGL->scaleY = 1.0f;
    layerOGL->translate = 0;
    layerOGL->transX = 0;
    layerOGL->transY = 0;
    layerOGL->screenTranslate = 0;
    layerOGL->screenTransX = 0;
    layerOGL->screenTransY = 0;
    layer->extraData = layerOGL;
    layerOGL->widthRatio = 0;
    layerOGL->heightRatio = 0;
}

void _art_destroyLayer(Art_Layer* layer)
{
    Art_LayerOpenGL* layerOGL = (Art_LayerOpenGL*)layer->extraData;
    GLuint textures[1] = {layerOGL->texture};
    glDeleteTextures(1, textures);
}

void _art_layerUnlock(Art_Layer* layer)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)layer->extraData;
    extraData->locked = 0;

    glViewport(0, 0, layer->width, layer->height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (layer->isRoot)
    {
        glOrtho(0.0f, layer->width, layer->height, 0.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(0.0f, layer->width, 0.0f, layer->height, -1.0f, 1.0f);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   

    if ((layer->isRoot && layer->clearOnUpdate) || ((!layer->isRoot) && extraData->firstUnlock))
    {
        glClearColor(extraData->fRed, extraData->fGreen, extraData->fBlue, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
    }
    else if (extraData->texture != 0)
    {
        art_drawLayer(layer, 0.0f, 0.0f);
    }

    if (extraData->firstUnlock)
    {
        extraData->firstUnlock = 0;
    }
}

void _art_layerLock(Art_Layer* layer)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)layer->extraData;

    if ((!layer->isRoot) || (!layer->clearOnUpdate))
    {
        glBindTexture(GL_TEXTURE_2D, extraData->texture);
        glCopyTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    0,
                    0,
                    layer->width,
                    layer->height);
    }

    extraData->locked = 0;
}

void art_setRotation(float x, float y, float angle)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->rotate = 1;
    extraData->rotAngle = 57.2957795f * angle;
    extraData->rotX = x;
    extraData->rotY = y;
}

void art_clearRotation()
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->rotate = 0;
}

void art_setScale(float scaleX, float scaleY)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->scale = 1;
    extraData->scaleX = scaleX;
    extraData->scaleY = scaleY;
}

void art_clearScale()
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->scale = 0;
}

void art_setTranslation(float transX, float transY)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->translate = 1;
    extraData->transX = transX;
    extraData->transY = transY;
}

void art_clearTranslation()
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->translate = 0;
}

void art_setScreenTranslation(float transX, float transY)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->screenTranslate = 1;
    extraData->screenTransX = transX;
    extraData->screenTransY = transY;
}

void art_clearScreenTranslation()
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->screenTranslate = 0;
}

void art_setColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue,
                    unsigned int alpha)
{
    Art_Layer* layer = artG_session.currentLayer;
    layer->red = red;
    layer->green = green;
    layer->blue = blue;
    layer->alpha = alpha;
    glColor4ub(red, green, blue, alpha);
}

void art_setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)artG_session.currentLayer->extraData;
    extraData->fRed = ((float)red) / 255.0f;
    extraData->fGreen = ((float)green) / 255.0f;
    extraData->fBlue = ((float)blue) / 255.0f;

    glClearColor(extraData->fRed, extraData->fGreen, extraData->fBlue, 1.0f);

}

void art_setPointSize(float size)
{
    glPointSize(size);
}

void art_setLineWidth(float width)
{
    glLineWidth(width);
}

void art_clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void art_drawPoint(float x, float y)
{
    APPLY_TRANSFORMS(x, y)

    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0.0f);
    glEnd();
}

void art_drawLine(float x1, float y1, float x2, float y2)
{
    float deltaX = x2 - x1;
    float deltaY = y2 - y1;

    APPLY_TRANSFORMS(x1, y1)

    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(deltaX, deltaY, 0.0f);
    glEnd();
}

void art_drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
    APPLY_TRANSFORMS(x1, y1)

    float xa = x2 - x1;
    float ya = y2 - y1;
    float xb = x3 - x1;
    float yb = y3 - y1;

    glBegin(GL_LINE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(xb, yb, 0.0f);
        glVertex3f(xa, ya, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
}

void art_drawSquare(float x,
                float y,
                float side)
{
    APPLY_TRANSFORMS(x, y)

    float halfSide = side / 2.0f;

    glBegin(GL_LINE_STRIP);
        glVertex3f(halfSide, halfSide, 0.0f);
        glVertex3f(-halfSide, halfSide, 0.0f);
        glVertex3f(-halfSide, -halfSide, 0.0f);
        glVertex3f(halfSide, -halfSide, 0.0f);
        glVertex3f(halfSide, halfSide, 0.0f);
    glEnd();
}

void art_drawRectangle(float x,
                float y,
                float width,
                float height)
{
    APPLY_TRANSFORMS(x, y)

    glBegin(GL_LINE_STRIP);
        glVertex3f(width, height, 0.0f);
        glVertex3f(0, height, 0.0f);
        glVertex3f(0, 0, 0.0f);
        glVertex3f(width, 0, 0.0f);
        glVertex3f(width, height, 0.0f);
    glEnd();
}

void art_drawCircleSlice(float x,
                float y,
                float rad,
                float beginAngle,
                float endAngle)
{
    APPLY_TRANSFORMS(x, y)

    float ang = beginAngle;
    int stop = 0;

    glBegin(GL_LINE_STRIP);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = 1;
        }

        glVertex3f(cosf(ang) * rad,
            sinf(ang) * rad,
            0.0f);
        ang += artG_session.currentLayer->curveAngleStep;
    }

    glEnd();
}

void art_drawEllipseSlice(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle)
{
    APPLY_TRANSFORMS(x, y)

    float ang = beginAngle;
    int stop = 0;

    glBegin(GL_LINE_STRIP);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = 1;
        }

        glVertex3f(cosf(ang) * radX,
            sinf(ang) * radY,
            0.0f);
        ang += artG_session.currentLayer->curveAngleStep;
    }

    glEnd();
}

void art_fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
    APPLY_TEXTURE()
    APPLY_TRANSFORMS(x1, y1)

    float xa = x2 - x1;
    float ya = y2 - y1;
    float xb = x3 - x1;
    float yb = y3 - y1;

    glBegin(GL_TRIANGLES);
        glTexCoord2d(texX, texY);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2d((xb * widthRatio) + texX, (yb * heightRatio) + texY);
        glVertex3f(xb, yb, 0.0f);
        glTexCoord2d((xa * widthRatio) + texX, (ya * heightRatio) + texY);
        glVertex3f(xa, ya, 0.0f);
    glEnd();
}

void art_fillSquare(float x,
                    float y,
                    float side)
{
    APPLY_TEXTURE()
    APPLY_TRANSFORMS(x, y)

    float halfSide = side / 2.0f;

    float offsetX = (widthRatio * side) + texX;
    float offsetY = (heightRatio * side) + texY;

    glBegin(GL_QUADS);
        glTexCoord2d(offsetX, offsetY);
        glVertex3f(halfSide, halfSide, 0.0f);
        glTexCoord2d(texX, offsetY);
        glVertex3f(-halfSide, halfSide, 0.0f);
        glTexCoord2d(texX, texY);
        glVertex3f(-halfSide, -halfSide, 0.0f);
        glTexCoord2d(offsetX, texY);
        glVertex3f(halfSide, -halfSide, 0.0f);
    glEnd();
}

void art_fillRectangle(float x,
                float y,
                float width,
                float height)
{
    APPLY_TEXTURE()
    APPLY_TRANSFORMS(x, y)

    float offsetX = (widthRatio * width) + texX;
    float offsetY = (heightRatio * height) + texY;

    glBegin(GL_QUADS);
        glTexCoord2d(offsetX, offsetY);
        glVertex3f(width, height, 0.0f);
        glTexCoord2d(texX, offsetY);
        glVertex3f(0, height, 0.0f);
        glTexCoord2d(texX, texY);
        glVertex3f(0, 0, 0.0f);
        glTexCoord2d(offsetX, texY);
        glVertex3f(width, 0, 0.0f);
    glEnd();
}

void art_fillCircleSlice(float x,
                    float y,
                    float rad,
                    float beginAngle,
                    float endAngle)
{
    APPLY_TEXTURE()
    APPLY_TRANSFORMS(x, y)

    float ang = beginAngle;
    int stop = 0;

    glBegin(GL_POLYGON);

    glTexCoord2d((rad * widthRatio) + texX, (rad * heightRatio) + texY);
    glVertex3f(0.0f, 0.0f, 0.0f);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = 1;
        }
        
        float cx = cosf(ang) * rad;
        float cy = sinf(ang) * rad;
        glTexCoord2d(((cx + rad) * widthRatio) + texX,
                        ((cy + rad) * heightRatio) + texY);
        glVertex3f(cx, cy, 0.0f);
        ang += artG_session.currentLayer->curveAngleStep;
    }

    glEnd();
}

void art_fillEllipseSlice(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle)
{
    APPLY_TEXTURE()
    APPLY_TRANSFORMS(x, y)

    float ang = beginAngle;
    int stop = 0;

    glBegin(GL_POLYGON);

    glTexCoord2d((radX * widthRatio) + texX, (radY * heightRatio) + texY);
    glVertex3f(0.0f, 0.0f, 0.0f);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = 1;
        }

        float cx = cosf(ang) * radX;
        float cy = sinf(ang) * radY;
        glTexCoord2d(((cx + radX) * widthRatio) + texX,
                        ((cy + radY) * heightRatio) + texY);
        glVertex3f(cx, cy, 0.0f);
        ang += artG_session.currentLayer->curveAngleStep;
    }

    glEnd();
}

void art_drawScaledLayer(Art_Layer* layer,
        float x,
        float y,
        float width,
        float height)
{
    APPLY_TRANSFORMS(x, y)

    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)layer->extraData;

    float targetWidth;
    float targetHeight;

    if (width > 0.0f)
    {
        targetWidth = width;
    }
    else
    {
        targetWidth = (float)layer->width;
    }

    if (height > 0.0f)
    {
        targetHeight = height;
    }
    else
    {
        targetHeight = (float)layer->height;
    }

    float origX1 = 0.0f;
    float origY1 = 0.0f;
    float origX2 = ((float)layer->width) / ((float)extraData->textureWidth);
    float origY2 = ((float)layer->height) / ((float)extraData->textureHeight);

    // Hack to prevent anomalies in borders when rotating
    origX1 += 0.001f;
    origY1 += 0.001f;

    glBindTexture(GL_TEXTURE_2D, extraData->texture);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2f(origX1, origY1);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glTexCoord2f(origX2, origY1);
    glVertex3f(targetWidth, 0.0f, 0.0f);

    glTexCoord2f(origX2, origY2);
    glVertex3f(targetWidth, targetHeight, 0.0f);

    glTexCoord2f(origX1, origY2);
    glVertex3f(0.0f, targetHeight, 0.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

int _art_initEmptyLayer(Art_Layer* layer, int width, int height)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)layer->extraData;

    int texWidth = _art_nextPowerOfTwo(width);
    int texHeight = _art_nextPowerOfTwo(height);

    unsigned int* data;
    unsigned int dataSize = texWidth * texHeight;

    data = (unsigned int*)malloc(dataSize * 4 * sizeof(unsigned int));

    unsigned int i;
    for (i = 0; i < dataSize; i++)
    {
        data[i] = 0;
    }

    glGenTextures(1, &extraData->texture);
    glBindTexture(GL_TEXTURE_2D, extraData->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D,
            0,
            4,
            texWidth,
            texHeight,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);

    free(data);

    extraData->textureWidth = texWidth;
    extraData->textureHeight = texHeight;
    layer->width = width;
    layer->height = height;
    extraData->widthRatio = 1.0f / width;
    extraData->heightRatio = 1.0f / height;

    return 0;
}

int _art_loadImageLayer(Art_Layer* layer, char* filePath)
{
    Art_LayerOpenGL* extraData = (Art_LayerOpenGL*)layer->extraData;

    int width;
    int height;
    int bpp;
    unsigned char *data = stbi_load(filePath, &width, &height, &bpp, 0);
    
    if (data == NULL)
    {
        // TODO: set error "Error loading image (" + filePath + "): " + stbi_failure_reason()
        return -1;
    }
    
    layer->width = width;
    layer->height = height;
    extraData->widthRatio = 1.0f / width;
    extraData->heightRatio = 1.0f / height;

    extraData->textureWidth = _art_nextPowerOfTwo(width);
    extraData->textureHeight = _art_nextPowerOfTwo(height);
   
    GLint internalTextureFormat = GL_RGB;
    GLenum textureFormat = GL_RGB; 

    if (bpp == 4)
    {
        internalTextureFormat = GL_RGBA;
        textureFormat = GL_RGBA;
    }
    // TODO: check for bpp < 3 situations
    else
    {
        internalTextureFormat = GL_RGB;
        textureFormat = GL_RGB;
    }

    unsigned char* textureData = (unsigned char*)malloc(extraData->textureWidth * extraData->textureHeight * bpp);

    unsigned int dataRowBytes = width * bpp;
    unsigned int textureDataRowBytes = extraData->textureWidth * bpp;

    unsigned int x;
    unsigned int y;
    unsigned int dataX;
    unsigned int dataY;
    for (y = 0; y < extraData->textureHeight; y++)
    {
        dataY = y;
        if (dataY >= height)
        {
            dataY -= height;
        }
        for (x = 0; x < textureDataRowBytes; x++)
        {
            dataX = x;
            if (dataX >= dataRowBytes)
            {
                dataX -= dataRowBytes;
            }
            textureData[(textureDataRowBytes * y) + x] = data[(dataRowBytes * dataY) + dataX];
        }
    }

    glGenTextures(1, &extraData->texture);
    glBindTexture(GL_TEXTURE_2D, extraData->texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D,
            0,
            internalTextureFormat,
            extraData->textureWidth,
            extraData->textureHeight,
            0,
            textureFormat,
            GL_UNSIGNED_BYTE,
            textureData);

    free(textureData);
    stbi_image_free(data);

    extraData->firstUnlock = 0;

    return 0;
}

int art_drawText(float x, float y, char* text)
{
    if (artG_session.currentLayer->currentFont == NULL)
    {
        printf("Attempting to print text without setting a font first\n");
        return -1;
    }

    APPLY_TRANSFORMS(x, y)

    Art_FontOpenGL* fontGL = (Art_FontOpenGL*)artG_session.currentLayer->currentFont->extraData;

    GLuint font = fontGL->listBase;

    glEnable(GL_TEXTURE_2D);

    glListBase(font);

    //  The commented out raster position stuff can be useful if you need to
    //  know the length of the text that you are creating.
    //  If you decide to use it make sure to also uncomment the glBitmap command
    //  in make_dlist().
    //  glRasterPos2f(0,0);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    //  float rpos[4];
    //  glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
    //  float len=x-rpos[0];

    glDisable(GL_TEXTURE_2D);

    return 0;
}

void art_drawPixels(char* pixels)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glRasterPos2f(0, 0);
    glPixelZoom(1.0f, -1.0f);

    unsigned int width;
    unsigned int height;

    if (artG_session.currentLayer != NULL)
    {
        width = artG_session.currentLayer->width;
        height = artG_session.currentLayer->height;
    }
    else
    {
        width = artG_session.windowWidth;
        height = artG_session.windowHeight;
    }

    glDrawPixels(width,
                    height, 
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    (const GLvoid*)pixels);
}

