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

	virtual void setColor(float red,
				float green,
				float blue,
				float alpha=1.0f)=0;
	virtual void setBackgroundColor(float red,
				float green,
				float blue)=0;

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
	virtual void drawFilledTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)=0;
	virtual void drawFilledSquare(float x,
					float y,
					float rad,
					float rot=0.0f)=0;
	virtual void drawFilledCircle(float x,
					float y,
					float rad,
					float beginAngle=0.0f,
					float endAngle=(M_PI * 2))=0;

        virtual void drawLayer(Layer* layer, float x=0.0f, float y=0.0f)=0;

	virtual bool _loadPNG(std::string filePath)=0;

protected:
	int mWidth;
	int mHeight;
};

}

#endif

