/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_PYCASSO_LAYER_OPENGL_H)
#define __INCLUDE_PYCASSO_LAYER_OPENGL_H

#include "Layer.h"

#include <math.h>
#include <GL/gl.h>

namespace pyc
{

class LayerOpenGL : public Layer
{
public:
	LayerOpenGL();
	virtual ~LayerOpenGL();

	virtual void setColor(unsigned int red,
				unsigned int green,
				unsigned int blue,
				unsigned int alpha);
	virtual void setBackgroundColor(unsigned int red,
					unsigned int green,
					unsigned int blue);

	virtual void setPointSize(float size);
	virtual void setLineWidth(float width);

	virtual void clear();

	virtual void drawPoint(float x, float y);
	virtual void drawLine(float x1, float y1, float x2, float y2);
	virtual void drawTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3);
	virtual void drawSquare(float x,
					float y,
					float rad,
					float rot=0.0f);
	virtual void drawCircle(float x,
					float y,
					float rad,
					float beginAngle=0.0f,
					float endAngle=(M_PI * 2));
	virtual void fillTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3);
	virtual void fillSquare(float x,
					float y,
					float rad,
					float rot=0.0f);
	virtual void fillCircle(float x,
					float y,
					float rad,
					float beginAngle=0.0f,
					float endAngle=(M_PI * 2));

	virtual void drawLayer(Layer* layer,
				float x=0.0f,
				float y=0.0f,
				float width=0.0f,
				float height=0.0f);

	virtual void _initEmpty(int width, int height);
	virtual void _loadPNG(std::string filePath);
	void _setClearOnUpdate(bool clear){mClearOnUpdate = clear;}

protected:
	void lock();
	void unlock();

	bool mLocked;

	static LayerOpenGL* mWorkingLayer;

        GLuint mTexture;

	int mTextureWidth;
	int mTextureHeight;

	bool mClearOnUpdate;
	bool mFirstUnlock;

	float mfRed;
	float mfGreen;
	float mfBlue;
};

}

#endif

