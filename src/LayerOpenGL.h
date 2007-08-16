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

	virtual void startDrawing();

	virtual void setColor(float red,
				float green,
				float blue,
				float alpha=1.0f);
	virtual void setBackgroundColor(float red,
				float green,
				float blue);

	virtual void setPointSize(float size);
	virtual void setLineWidth(float width);

	virtual void drawPoint(float x, float y);
	virtual void drawLine(float x1, float y1, float x2, float y2);
	virtual void drawTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3);
	virtual void drawFilledTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3);
	virtual void drawFilledSquare(float x,
					float y,
					float rad,
					float rot=0.0f);
	virtual void drawFilledCircle(float x,
					float y,
					float rad,
					float beginAngle=0.0f,
					float endAngle=(M_PI * 2));

        virtual void drawLayer(Layer* layer, float x=0.0f, float y=0.0f);

	virtual bool _loadPNG(std::string filePath);

protected:
        GLuint mTexture;

	int mTextureWidth;
	int mTextureHeight;
};

}

#endif

