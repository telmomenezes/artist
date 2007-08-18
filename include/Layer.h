/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_PYCASSO_LAYER_H)
#define __INCLUDE_PYCASSO_LAYER_H

#include "Color.h"
#include <math.h>
#include <string>

namespace pyc
{

class Layer
{
public:
	Layer();
	virtual ~Layer();

	int getWidth(){return mWidth;}
	int getHeight(){return mHeight;}

	virtual void startDrawing()=0;
	virtual void stopDrawing()=0;

	virtual void setColor(Color &c)=0;
	virtual void setBackgroundColor(Color &c)=0;

	virtual void setPointSize(float size)=0;
	virtual void setLineWidth(float width)=0;

	virtual void drawPoint(float x, float y)=0;
	virtual void drawLine(float x1, float y1, float x2, float y2)=0;
	virtual void drawTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)=0;
	virtual void fillTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)=0;
	virtual void fillSquare(float x,
					float y,
					float rad,
					float rot=0.0f)=0;
	virtual void fillCircle(float x,
					float y,
					float rad,
					float beginAngle=0.0f,
					float endAngle=(M_PI * 2))=0;

        virtual void drawLayer(Layer* layer,
				float x=0.0f,
				float y=0.0f,
				float width=0.0f,
				float height=0.0f)=0;

	bool isRoot(){return mRoot;}

	virtual bool _initEmpty(int width, int height)=0;
	virtual bool _loadPNG(std::string filePath)=0;
	void _setRoot(int width, int height);

protected:
	int mWidth;
	int mHeight;
	bool mRoot;
};

}

#endif

