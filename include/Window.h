/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_PYCASSO_WINDOW_H)
#define __INCLUDE_PYCASSO_WINDOW_H

#include "Canvas.h"
#include <string>

namespace pyc
{

class Window
{
public:
	Window();
	virtual ~Window();

	virtual bool init(int width,
        		        int height,
				bool fullScreen=false,
		                int colorDepth=0,
				bool resizable=false,
				bool windowDecorations=true);

	virtual void setTitle(std::string title)=0;


	int getWidth(){return mWidth;}
	int getHeight(){return mHeight;}
	Canvas* getMainCanvas();

protected:
	int mWidth;
	int mHeight;
	Canvas* mMainCanvas;
};

}

#endif

