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
#include <list>

namespace pyc
{

class Window
{
public:
	Window();
	virtual ~Window();

	virtual void init(int width,
        		        int height,
				bool fullScreen=false,
		                int colorDepth=0,
				bool resizable=false,
				bool windowDecorations=true);

	virtual void update()=0;

	virtual void setTitle(std::string title)=0;


	int getWidth(){return mWidth;}
	int getHeight(){return mHeight;}
	Layer* getRootLayer();

	virtual void showCursor(bool show)=0;

	virtual Layer* createLayer(int width, int height)=0;
	virtual Layer* createPNGLayer(std::string filePath)=0;
	bool removeLayer(Layer* layer);

	virtual void setClearOnUpdate(bool clear){mClearOnUpdate = clear;}

protected:
	int mWidth;
	int mHeight;
	Layer* mRootLayer;
	std::list<Layer*> mLayers;
	bool mClearOnUpdate;
};

}

#endif

