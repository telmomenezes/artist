/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "LayerOpenGL.h"
#include "PycassoException.h"
#include "functions.cpp"

#include <png.h>

namespace pyc
{

LayerOpenGL::LayerOpenGL()
{
        mTexture = 0;
	mTextureWidth = 0;
	mTextureHeight = 0;
}

LayerOpenGL::~LayerOpenGL()
{
	GLuint textures[1] = {mTexture};
	glDeleteTextures(1, textures);
}

void LayerOpenGL::startDrawing()
{
	int width;
	int height;

	if (mRoot)
	{
		width = mWidth;
		height = mHeight;
	}
	else
	{
		width = mTextureWidth;
		height = mTextureHeight;
	}

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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void LayerOpenGL::stopDrawing()
{
	if (!mRoot)
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
}

void LayerOpenGL::setColor(unsigned int red,
				unsigned int green,
				unsigned int blue,
				unsigned int alpha)
{
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
	float fRed = ((float)red) / 255.0f;
	float fGreen = ((float)green) / 255.0f;
	float fBlue = ((float)blue) / 255.0f;

	glClearColor(fRed, fGreen, fBlue, 1.0f);

}

void LayerOpenGL::setPointSize(float size)
{
	glPointSize(size);
}

void LayerOpenGL::setLineWidth(float width)
{
	glLineWidth(width);
}

void LayerOpenGL::drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
	glEnd();
}

void LayerOpenGL::drawLine(float x1, float y1, float x2, float y2)
{
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
	glBegin(GL_LINE_STRIP);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
		glVertex3f(x1, y1, 0.0f);
	glEnd();
}

void LayerOpenGL::fillTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)
{
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
	float ang = rot;
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

void LayerOpenGL::_loadPNG(std::string filePath)
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
		std::string text = "Loading PNG (" + filePath + "): failed to open file";
		PycassoException exception(EXCEPTION_FILE, text);
		throw exception;
	}

	fread(sig, 1, 8, infile);

	if (!png_check_sig((unsigned char*)sig, 8))
	{
		fclose(infile);
		std::string text = "Loading PNG (" + filePath + "): wrong file format";
		PycassoException exception(EXCEPTION_FILE, text);
		throw exception;
	}
 
	pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pngPtr)
	{
		fclose(infile);
		std::string text = "Loading PNG (" + filePath + "): out of memory";
		PycassoException exception(EXCEPTION_MEMORY, text);
		throw exception;
	}
 
	infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr)
	{
		png_destroy_read_struct(&pngPtr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(infile);
		std::string text = "Loading PNG (" + filePath + "): out of memory";
		PycassoException exception(EXCEPTION_MEMORY, text);
		throw exception;
	}
   
  
	if (setjmp(png_jmpbuf(pngPtr)))
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
		fclose(infile);
		std::string text = "Loading PNG (" + filePath + ")";
		PycassoException exception(EXCEPTION_MEMORY, text);
		throw exception;
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
		std::string text = "Loading PNG (" + filePath + ")";
		PycassoException exception(EXCEPTION_MEMORY, text);
		throw exception;
	}

	if ((rowPointers = (png_bytepp)malloc(height * sizeof(png_bytep))) == NULL)
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
		free(imageData);
		imageData = NULL;
		std::string text = "Loading PNG (" + filePath + ")";
		PycassoException exception(EXCEPTION_MEMORY, text);
		throw exception;
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
}

}

