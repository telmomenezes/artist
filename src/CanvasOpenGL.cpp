/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if defined(__LAYER_SDLOPENGL)

#include "CanvasOpenGL.h"
#include "ImageOpenGL.h"

#include "SDL.h"
#include "SDL_opengl.h" 

namespace pyc
{

CanvasOpenGL::CanvasOpenGL()
{
}

CanvasOpenGL::~CanvasOpenGL()
{
}

void CanvasOpenGL::beginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void CanvasOpenGL::endFrame()
{
	SDL_GL_SwapBuffers();
}

void CanvasOpenGL::setColor(float red,
				float green,
				float blue,
				float alpha)
{
	glColor4f(red, green, blue, alpha);
}

void CanvasOpenGL::setBackgroundColor(float red,
				float green,
				float blue)
{
	glClearColor(red, green, blue, 0.0f);
}

void CanvasOpenGL::setPointSize(float size)
{
	glPointSize(size);
}

void CanvasOpenGL::setLineWidth(float width)
{
	glLineWidth(width);
}

void CanvasOpenGL::drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
	glEnd();
}

void CanvasOpenGL::drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
	glEnd();
}

void CanvasOpenGL::drawTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)
{
	glBegin(GL_LINE_STRIP);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
		glVertex3f(x1, y1, 0.0f);
	glEnd();
}

void CanvasOpenGL::drawFilledTriangle(float x1,
					float y1,
					float x2,
					float y2,
					float x3,
					float y3)
{
	glBegin(GL_TRIANGLES);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
	glEnd();
}

void CanvasOpenGL::drawFilledSquare(float x,
					float y,
					float rad,
					float rot)
{
	float ang = rot;
	float deltaAng = M_PI * 0.5;

	glBegin(GL_QUADS);

	for (unsigned int i = 0; i < 4; i++)
	{
		glVertex3f(x + (cosf(ang) * rad),
			y + (sinf(ang) * rad),
			0.0f);
		ang += deltaAng;
	}

	glEnd();
}

void CanvasOpenGL::drawFilledCircle(float x,
					float y,
					float rad,
					float beginAngle,
					float endAngle)
{
	float ang = beginAngle;
	bool stop = false;

	glBegin(GL_POLYGON);

	glVertex3f(x, y, 0.0f);

	while (!stop)
	{
		if (ang >= endAngle)
		{
			ang = endAngle;
			stop = true;
		}

		glVertex3f(x + (cosf(ang) * rad),
			y + (sinf(ang) * rad),
			0.0f);
		ang += 0.1f;
	}

	glEnd();
}

Image* CanvasOpenGL::loadPNG(std::string filePath)
{
	ImageOpenGL* image = new ImageOpenGL();

	if (!image->loadPNG(filePath))
	{
		delete image;
		return NULL;
	}

	return image;
}

}

#endif

