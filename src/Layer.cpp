/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "Layer.h"

namespace pyc
{

Layer::Layer()
{
        mWidth = 0;
        mHeight = 0;
	mRoot = false;
}

Layer::~Layer()
{
}

void Layer::_setRoot(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mRoot = true;
}

}

