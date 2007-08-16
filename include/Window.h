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

#include "Layer.h"
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
	Layer* getLayer();

	virtual void showCursor(bool show)=0;

protected:
	int mWidth;
	int mHeight;
	Layer* mLayer;
};

}

#endif

