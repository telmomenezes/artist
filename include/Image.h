/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_IMAGE_H)
#define __INCLUDE_PYCASSO_IMAGE_H

#include <string>

namespace pyc
{

class Image
{
public:
	Image();
	virtual ~Image();

	virtual bool loadPNG(std::string filePath)=0;

	virtual void draw(float x, float y)=0;

protected:
	int nextPowerOfTwo(int value);

	int mWidth;
	int mHeight;
};

}

#endif

