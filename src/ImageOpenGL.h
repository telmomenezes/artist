/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_IMAGE_OPENGL_H)
#define __INCLUDE_PYCASSO_IMAGE_OPENGL_H

#include "Image.h"

#include "SDL.h"
#include "SDL_opengl.h"

namespace pyc
{

class ImageOpenGL : public Image
{
public:
	ImageOpenGL();
	virtual ~ImageOpenGL();

	virtual bool loadPNG(std::string filePath);

	virtual void draw(float x, float y);

protected:
	GLuint mTexture;

	int mTextureWidth;
	int mTextureHeight;
};

}

#endif

