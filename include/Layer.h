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

	virtual void setColor(unsigned int red,
				unsigned int green,
				unsigned int blue,
				unsigned int alpha)=0;
	virtual void setColor(unsigned int red,
				unsigned int green,
				unsigned int blue);
	virtual void setAlpha(unsigned int alpha);
	virtual void setColorRGBA(unsigned int color);
	virtual void setColorRGB(unsigned int color);
	virtual void setBackgroundColor(unsigned int red,
					unsigned int green,
					unsigned int blue)=0;
	virtual void setBackgroundColorRGB(unsigned int color);

	virtual void setPointSize(float size)=0;
	virtual void setLineWidth(float width)=0;

	virtual void clear()=0;

	virtual void drawPoint(float x, float y)=0;
	virtual void drawLine(float x1, float y1, float x2, float y2)=0;
	virtual void drawTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)=0;
	virtual void drawSquare(float x,
					float y,
					float rad,
					float rot=0.0f)=0;
	virtual void drawCircle(float x,
					float y,
					float rad,
					float beginAngle=0.0f,
					float endAngle=(M_PI * 2))=0;
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

	virtual void _initEmpty(int width, int height){};
	virtual void _loadPNG(std::string filePath){};
	void _setRoot(int width, int height);

protected:
	int mWidth;
	int mHeight;
	bool mRoot;

	unsigned int mRed;
	unsigned int mGreen;
	unsigned int mBlue;
	unsigned int mAlpha;
};

}

#endif

