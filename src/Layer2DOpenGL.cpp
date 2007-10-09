/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Layer2DOpenGL.h"
#include "FontOpenGL.h"
#include "functions.cpp"

#include <stdexcept>

#include <png.h>

#define CHECK_LOCK() if(mLocked) unlock();
#define APPLY_TRANSFORMS(X, Y) glLoadIdentity(); if(mScreenTranslate) glTranslatef(mScreenTransX, mScreenTransY, 0.0f); if(mScale) glScalef(mScaleX, mScaleY, 0.0f); if(mTranslate) glTranslatef(mTransX, mTransY, 0.0f); if (mRotate){float aX = X - mRotX; float aY = Y - mRotY; glTranslatef(mRotX, mRotY, 0.0f); glRotatef(mRotAngle, 0.0f, 0.0f, 1.0f); glTranslatef(aX, aY, 0.0f);}else{glTranslatef(X, Y, 0.0f);}

namespace pyc
{

Layer2DOpenGL* Layer2DOpenGL::mWorkingLayer = NULL;

Layer2DOpenGL::Layer2DOpenGL()
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
    mRotate = false;
    mRotX = 0;
    mRotY = 0;
    mRotAngle = 0;
    mScale = false;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mTranslate = false;
    mTransX = 0;
    mTransY = 0;
    mScreenTranslate = false;
    mScreenTransX = 0;
    mScreenTransY = 0;
}

Layer2DOpenGL::~Layer2DOpenGL()
{
    GLuint textures[1] = {mTexture};
    glDeleteTextures(1, textures);
}

void Layer2DOpenGL::unlock()
{
    mLocked = false;

    if (mWorkingLayer != this)
    {
        if (mWorkingLayer != NULL)
        {
            mWorkingLayer->lock();
        }

        mWorkingLayer = this;

        glViewport(0, 0, mWidth, mHeight);
    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (mRoot)
        {
            glOrtho(0.0f, mWidth, mHeight, 0.0f, -1.0f, 1.0f);
        }
        else
        {
            glOrtho(0.0f, mWidth, 0.0f, mHeight, -1.0f, 1.0f);
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

void Layer2DOpenGL::lock()
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

void Layer2DOpenGL::setRotation(float x, float y, float angle)
{
    mRotate = true;
    mRotAngle = 57.2957795f * angle;
    mRotX = x;
    mRotY = y;
}

void Layer2DOpenGL::clearRotation()
{
    mRotate = false;
}

void Layer2DOpenGL::setScale(float scaleX, float scaleY)
{
    mScale = true;
    mScaleX = scaleX;
    mScaleY = scaleY;
}

void Layer2DOpenGL::clearScale()
{
    mScale = false;
}

void Layer2DOpenGL::setTranslation(float transX, float transY)
{
    mTranslate = true;
    mTransX = transX;
    mTransY = transY;
}

void Layer2DOpenGL::clearTranslation()
{
    mTranslate = false;
}

void Layer2DOpenGL::setScreenTranslation(float transX, float transY)
{
    mScreenTranslate = true;
    mScreenTransX = transX;
    mScreenTransY = transY;
}

void Layer2DOpenGL::clearScreenTranslation()
{
    mScreenTranslate = false;
}

void Layer2DOpenGL::setColor(unsigned int red,
                unsigned int green,
                unsigned int blue,
                unsigned int alpha)
{
    CHECK_LOCK()

    mRed = red;
    mGreen = green;
    mBlue = blue;
    mAlpha = alpha;
    glColor4ub(mRed, mGreen, mBlue, mAlpha);
}

void Layer2DOpenGL::setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue)
{
    CHECK_LOCK()

    mfRed = ((float)red) / 255.0f;
    mfGreen = ((float)green) / 255.0f;
    mfBlue = ((float)blue) / 255.0f;

    glClearColor(mfRed, mfGreen, mfBlue, 1.0f);

}

void Layer2DOpenGL::setPointSize(float size)
{
    CHECK_LOCK()

    glPointSize(size);
}

void Layer2DOpenGL::setLineWidth(float width)
{
    CHECK_LOCK()

    glLineWidth(width);
}

void Layer2DOpenGL::clear()
{
    CHECK_LOCK()

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void Layer2DOpenGL::drawPoint(float x, float y)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0.0f);
    glEnd();
}

void Layer2DOpenGL::drawLine(float x1, float y1, float x2, float y2)
{
    CHECK_LOCK()

    float deltaX = x2 - x1;
    float deltaY = y2 - y1;

    APPLY_TRANSFORMS(x1, y1)

    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(deltaX, deltaY, 0.0f);
    glEnd();
}

void Layer2DOpenGL::drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
    CHECK_LOCK()

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

void Layer2DOpenGL::drawSquare(float x,
                float y,
                float side)
{
    CHECK_LOCK()

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

void Layer2DOpenGL::drawRectangle(float x,
                float y,
                float width,
                float height)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    glBegin(GL_LINE_STRIP);
        glVertex3f(width, height, 0.0f);
        glVertex3f(0, height, 0.0f);
        glVertex3f(0, 0, 0.0f);
        glVertex3f(width, 0, 0.0f);
        glVertex3f(width, height, 0.0f);
    glEnd();
}

void Layer2DOpenGL::drawCircle(float x,
                float y,
                float rad,
                float beginAngle,
                float endAngle)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

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

        glVertex3f(cosf(ang) * rad,
            sinf(ang) * rad,
            0.0f);
        ang += mCurveAngleStep;
    }

    glEnd();
}

void Layer2DOpenGL::drawEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

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

        glVertex3f(cosf(ang) * radX,
            sinf(ang) * radY,
            0.0f);
        ang += mCurveAngleStep;
    }

    glEnd();
}

void Layer2DOpenGL::fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x1, y1)

    float xa = x2 - x1;
    float ya = y2 - y1;
    float xb = x3 - x1;
    float yb = y3 - y1;

    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(xb, yb, 0.0f);
        glVertex3f(xa, ya, 0.0f);
    glEnd();
}

void Layer2DOpenGL::fillSquare(float x,
                    float y,
                    float side)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    float halfSide = side / 2.0f;

    glBegin(GL_QUADS);
        glVertex3f(halfSide, halfSide, 0.0f);
        glVertex3f(-halfSide, halfSide, 0.0f);
        glVertex3f(-halfSide, -halfSide, 0.0f);
        glVertex3f(halfSide, -halfSide, 0.0f);
    glEnd();
}

void Layer2DOpenGL::fillRectangle(float x,
                float y,
                float width,
                float height)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    glBegin(GL_QUADS);
        glVertex3f(width, height, 0.0f);
        glVertex3f(0, height, 0.0f);
        glVertex3f(0, 0, 0.0f);
        glVertex3f(width, 0, 0.0f);
    glEnd();
}

void Layer2DOpenGL::fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle,
                    float endAngle)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    float ang = beginAngle;
    bool stop = false;

    glBegin(GL_POLYGON);

    glVertex3f(0.0f, 0.0f, 0.0f);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = true;
        }

        glVertex3f(cosf(ang) * rad,
            sinf(ang) * rad,
            0.0f);
        ang += mCurveAngleStep;
    }

    glEnd();
}

void Layer2DOpenGL::fillEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle,
                    float endAngle)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    float ang = beginAngle;
    bool stop = false;

    glBegin(GL_POLYGON);

    glVertex3f(0.0f, 0.0f, 0.0f);

    while (!stop)
    {
        if (ang >= endAngle)
        {
            ang = endAngle;
            stop = true;
        }

        glVertex3f(cosf(ang) * radX,
            sinf(ang) * radY,
            0.0f);
        ang += mCurveAngleStep;
    }

    glEnd();
}

void Layer2DOpenGL::drawLayer(Layer* layer,
        float x,
        float y,
        float width,
        float height)
{
    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    Layer2DOpenGL* layGL = (Layer2DOpenGL*)layer;

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

    glBindTexture(GL_TEXTURE_2D, layGL->mTexture);
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

void Layer2DOpenGL::_initEmpty(int width, int height)
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

void Layer2DOpenGL::_loadPNG(string filePath)
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

void Layer2DOpenGL::drawText(float x, float y, string text)
{
    if (mCurrentFont == NULL)
    {
        throw std::runtime_error("Attempting to print text without setting a font first");
    }

    CHECK_LOCK()

    APPLY_TRANSFORMS(x, y)

    FontOpenGL* fontGL = (FontOpenGL*)mCurrentFont;

    GLuint font = fontGL->mListBase;

    glEnable(GL_TEXTURE_2D);

    glListBase(font);

    //  The commented out raster position stuff can be useful if you need to
    //  know the length of the text that you are creating.
    //  If you decide to use it make sure to also uncomment the glBitmap command
    //  in make_dlist().
    //  glRasterPos2f(0,0);
    glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
    //  float rpos[4];
    //  glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
    //  float len=x-rpos[0];

    glDisable(GL_TEXTURE_2D);
}

}

