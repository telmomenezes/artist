/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_H)
#define __INCLUDE_PYCASSO_H

#include "Canvas.h"
#include "types.h"

namespace pyc
{

class Pycasso
{
public:
	Pycasso();
	virtual ~Pycasso();

	Canvas* createScreen(ScreenType type,
				int width,
				int height,
				int colorDepth=0,
				bool fullScreen=false,
				bool resizable=false,
				bool windowDecorations=true);

	Canvas* getScreen(){return mScreen;}

private:
	Canvas* mScreen;
};

}

#endif

