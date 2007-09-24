/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "LayerOpenGL.h"
#include "FontOpenGL.h"
#include "functions.cpp"

#include <stdexcept>

#include <png.h>

namespace pyc
{

LayerOpenGL* LayerOpenGL::mWorkingLayer = NULL;

LayerOpenGL::LayerOpenGL()
{
    mLocked = true;
    mTexture = 0;
    mTextureWidth = 0;
    mTextureHeight = 0;
    mClearOnUpdate = true;
    mFirstUnlock = true;
    mfRed = 1.0f;
    mfGreen = 1.0f;
    mfBlue = 1.0f;
}

LayerOpenGL::~LayerOpenGL()
{
    GLuint textures[1] = {mTexture};
    glDeleteTextures(1, textures);
}

void LayerOpenGL::unlock()
{
    mLocked = false;

    if (mWorkingLayer != this)
    {
        if (mWorkingLayer != NULL)
        {
            mWorkingLayer->lock();
        }

        mWorkingLayer = this;

        int width = mWidth;
        int height = mHeight;

        glViewport(0, 0, width, height);
    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (mRoot)
        {
            glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        }
        else
        {
            glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();   
    }

    if ((mRoot && mClearOnUpdate) || ((!mRoot) && mFirstUnlock))
    {
        glClearColor(mfRed, mfGreen, mfBlue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
    }
    else if (mTexture != 0)
    {
        drawLayer(this, 0.0f, 0.0f);
    }

    if (mFirstUnlock)
    {
        mFirstUnlock = false;
    }
}

void LayerOpenGL::lock()
{
    if ((!mRoot) || (!mClearOnUpdate))
    {
        glBindTexture(GL_TEXTURE_2D, mTexture);
        glCopyTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    0,
                    0,
                    mWidth,
                    mHeight);
    }

    mLocked = true;
}

void LayerOpenGL::setColor(unsigned int red,
                unsigned int green,
                unsigned int blue,
                unsigned int alpha)
{
    if (mLocked)
    {
        unlock();
    }
    
    mRed = red;
    mGreen = green;
    mBlue = blue;
    mAlpha = alpha;
    glColor4ub(mRed, mGreen, mBlue, mAlpha);
}

void LayerOpenGL::setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue)
{
    if (mLocked)
    {
        unlock();
    }

    mfRed = ((float)red) / 255.0f;
    mfGreen = ((float)green) / 255.0f;
    mfBlue = ((float)blue) / 255.0f;

    glClearColor(mfRed, mfGreen, mfBlue, 1.0f);

}

void LayerOpenGL::setPointSize(float size)
{
    if (mLocked)
    {
        unlock();
    }

    glPointSize(size);
}

void LayerOpenGL::setLineWidth(float width)
{
    if (mLocked)
    {
        unlock();
    }

    glLineWidth(width);
}

void LayerOpenGL::clear()
{
    if (mLocked)
    {
        unlock();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void LayerOpenGL::drawPoint(float x, float y)
{
    if (mLocked)
    {
        unlock();
    }

    glBegin(GL_POINTS);
    glVertex3f(x, y, 0.0f);
    glEnd();
}

void LayerOpenGL::drawLine(float x1, float y1, float x2, float y2)
{
    if (mLocked)
    {
        unlock();
    }

    glBegin(GL_LINES);
        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, 0.0f);
    glEnd();
}

void LayerOpenGL::drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
    if (mLocked)
    {
        unlock();
    }

    glBegin(GL_LINE_STRIP);
        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, 0.0f);
        glVertex3f(x3, y3, 0.0f);
        glVertex3f(x1, y1, 0.0f);
    glEnd();
}

void LayerOpenGL::drawSquare(float x,
                float y,
                float rad,
                float rot)
{
    if (mLocked)
    {
        unlock();
    }

    float ang = rot + M_PI * 0.25;
    float deltaAng = M_PI * 0.5;

    glBegin(GL_LINE_STRIP);

    for (unsigned int i = 0; i < 5; i++)
    {
        glVertex3f(x + (cosf(ang) * rad),
            y + (sinf(ang) * rad),
            0.0f);
        ang += deltaAng;
    }

    glEnd();
}

void LayerOpenGL::drawCircle(float x,
                float y,
                float rad,
                float beginAngle,
                float endAngle)
{
    if (mLocked)
    {
        unlock();
    }

    float ang = beginAngle;
    bool stop = false;

    glBegin(GL_LINE_STRIP);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = true;
        }

        glVertex3f(x + (cosf(ang) * rad),
            y + (sinf(ang) * rad),
            0.0f);
        ang += 0.1f;
    }

    glEnd();
}

void LayerOpenGL::fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
    if (mLocked)
    {
        unlock();
    }

    glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, 0.0f);
        glVertex3f(x3, y3, 0.0f);
    glEnd();
}

void LayerOpenGL::fillSquare(float x,
                    float y,
                    float rad,
                    float rot)
{
    if (mLocked)
    {
        unlock();
    }

    float ang = rot + M_PI * 0.25;
    float deltaAng = M_PI * 0.5;

    glBegin(GL_QUADS);

    for (unsigned int i = 0; i < 4; i++)
    {
        glVertex3f(x + (cosf(ang) * rad),
            y + (sinf(ang) * rad),
            0.0f);
        ang += deltaAng;
    }

    glEnd();
}

void LayerOpenGL::fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle,
                    float endAngle)
{
    if (mLocked)
    {
        unlock();
    }

    float ang = beginAngle;
    bool stop = false;

    glBegin(GL_POLYGON);

    glVertex3f(x, y, 0.0f);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = true;
        }

        glVertex3f(x + (cosf(ang) * rad),
            y + (sinf(ang) * rad),
            0.0f);
        ang += 0.1f;
    }

    glEnd();
}

void LayerOpenGL::drawLayer(Layer* layer,
        float x,
        float y,
        float width,
        float height)
{
    if (mLocked)
    {
        unlock();
    }

    LayerOpenGL* layGL = (LayerOpenGL*)layer;

    float targetWidth;
    float targetHeight;

    if (width > 0.0f)
    {
        targetWidth = width;
    }
    else
    {
        targetWidth = (float)layGL->mWidth;
    }

    if (height > 0.0f)
    {
        targetHeight = height;
    }
    else
    {
        targetHeight = (float)layGL->mHeight;
    }

    float origX1 = 0.0f;
    float origY1 = 0.0f;
    float origX2 = ((float)layGL->mWidth) / ((float)layGL->mTextureWidth);
    float origY2 = ((float)layGL->mHeight) / ((float)layGL->mTextureHeight);

    float x2 = x + targetWidth;
    float y2 = y + targetHeight;

    glBindTexture(GL_TEXTURE_2D, layGL->mTexture);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2f(origX1, origY1);
    glVertex3f(x, y, 0.0f);

    glTexCoord2f(origX2, origY1);
    glVertex3f(x2, y, 0.0f);

    glTexCoord2f(origX2, origY2);
    glVertex3f(x2, y2, 0.0f);

    glTexCoord2f(origX1, origY2);
    glVertex3f(x, y2, 0.0f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void LayerOpenGL::_initEmpty(int width, int height)
{
    int texWidth = nextPowerOfTwo(width);
    int texHeight = nextPowerOfTwo(height);

    unsigned int* data;
    unsigned int dataSize = texWidth * texHeight;

    data = (unsigned int*)new GLuint[(dataSize * 4 * sizeof(unsigned int))];

    for (unsigned int i = 0; i < dataSize; i++)
    {
        data[i] = 0;
    }

    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
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

    delete [] data;

    mTextureWidth = texWidth;
    mTextureHeight = texHeight;
    mWidth = width;
    mHeight = height;
}

void LayerOpenGL::_loadPNG(string filePath)
{
    FILE *infile;
    png_structp pngPtr;
    png_infop infoPtr;

    unsigned char *imageData;
    char sig[8];

    int bitDepth;
    int colorType;

    unsigned long width;
    unsigned long height;
    unsigned int rowbytes;

    imageData = NULL;
    int i;
    png_bytepp rowPointers = NULL;

    infile = fopen(filePath.c_str(), "rb");
    if (!infile)
    {
        string text = "Loading PNG (" + filePath + "): failed to open file";
        throw std::runtime_error(text);
    }

    fread(sig, 1, 8, infile);

    if (!png_check_sig((unsigned char*)sig, 8))
    {
        fclose(infile);
        string text = "Loading PNG (" + filePath + "): wrong file format";
        throw std::runtime_error(text);
    }
 
    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngPtr)
    {
        fclose(infile);
        string text = "Loading PNG (" + filePath + "): out of memory";
        throw std::runtime_error(text);
    }
 
    infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr)
    {
        png_destroy_read_struct(&pngPtr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(infile);
        string text = "Loading PNG (" + filePath + "): out of memory";
        throw std::runtime_error(text);
    }
   
  
    if (setjmp(png_jmpbuf(pngPtr)))
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        fclose(infile);
        string text = "Loading PNG (" + filePath + ")";
        throw std::runtime_error(text);
    }

    png_init_io(pngPtr, infile);
   
    png_set_sig_bytes(pngPtr, 8);

    png_read_info(pngPtr, infoPtr);

    png_get_IHDR(pngPtr,
            infoPtr,
            &width,
            &height,
            &bitDepth,
            &colorType,
            NULL,
            NULL,
            NULL);

    mWidth = width;
    mHeight = height;

    mTextureWidth = nextPowerOfTwo(mWidth);
    mTextureHeight = nextPowerOfTwo(mHeight);
   
    if (bitDepth > 8)
    {
        png_set_strip_16(pngPtr);
    }
    if (colorType == PNG_COLOR_TYPE_GRAY
        || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(pngPtr);
    }
    if (colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngPtr);
    }

    png_read_update_info(pngPtr, infoPtr);
    png_get_IHDR(pngPtr,
            infoPtr,
            &width,
            &height,
            &bitDepth,
            &colorType,
            NULL,
            NULL,
            NULL);

    unsigned int bpp = 3;
    GLint internalTextureFormat = GL_RGB;
    GLenum textureFormat = GL_RGB;
    if (colorType == PNG_COLOR_TYPE_RGB_ALPHA)
    {
        bpp = 4;
        internalTextureFormat = GL_RGBA;
        textureFormat = GL_RGBA;
    }

    rowbytes = png_get_rowbytes(pngPtr, infoPtr);

    if ((imageData = (unsigned char*)malloc(rowbytes * height)) == NULL)
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        string text = "Loading PNG (" + filePath + ")";
        throw std::runtime_error(text);
    }

    if ((rowPointers = (png_bytepp)malloc(height * sizeof(png_bytep))) == NULL)
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
        free(imageData);
        imageData = NULL;
        string text = "Loading PNG (" + filePath + ")";
        throw std::runtime_error(text);
    }

    for (i = 0;  i < height;  ++i)
    {
        rowPointers[i] = imageData + i * rowbytes;
    }

    png_read_image(pngPtr, rowPointers);

    free(rowPointers);

    png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
    fclose(infile);

    unsigned char* textureData = (unsigned char*)malloc(mTextureWidth * mTextureHeight * bpp);

    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < rowbytes; x++)
        {
            textureData[(mTextureWidth * bpp * y) + x] = imageData[(rowbytes * y) + x];
        }
    }

    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D,
            0,
            internalTextureFormat,
            mTextureWidth,
            mTextureHeight,
            0,
            textureFormat,
            GL_UNSIGNED_BYTE,
            textureData);

    delete imageData;
    delete textureData;

    mFirstUnlock = false;
}

void LayerOpenGL::moveRasterX(int x)
{
    glBitmap(0, 0, 0, 0, x, 0, NULL);
}

void LayerOpenGL::moveRasterY(int y)
{
    glBitmap(0, 0, 0, 0, 0, y, NULL);
}

void LayerOpenGL::drawText(float x, float y, string text)
{
    if (mCurrentFont == NULL)
    {
        throw std::runtime_error("Attempting to print text without setting a font first");
    }

    if (mLocked)
    {
        unlock();
    }

    const char* cText = text.c_str();

    glPushAttrib(GL_CURRENT_BIT | GL_PIXEL_MODE_BIT | GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    GLint oldUnpack;
    glGetIntegerv(GL_UNPACK_ALIGNMENT,&oldUnpack); 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    float color[4];
    glGetFloatv(GL_CURRENT_COLOR, color);

    glPixelTransferf(GL_RED_SCALE, color[0]);
    glPixelTransferf(GL_GREEN_SCALE, color[1]);
    glPixelTransferf(GL_BLUE_SCALE, color[2]);
    glPixelTransferf(GL_ALPHA_SCALE, color[3]);

    moveRasterX((int)x);
    moveRasterY((int)(mHeight - y));

    FontOpenGL* font = (FontOpenGL*)mCurrentFont;

    for (int i = 0; cText[i]; i++)
    {
        CharacterOpenGL* cData = font->mChars[text[i]];

        moveRasterX(cData->mLeft);
        moveRasterY(cData->mMoveUp);

        glDrawPixels(cData->mWidth, cData->mHeight, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, cData->mData);

        moveRasterY(-cData->mMoveUp);
        moveRasterX(cData->mAdvance - cData->mLeft);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, oldUnpack);
    glPopAttrib();
}

}

