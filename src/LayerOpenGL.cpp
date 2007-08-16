/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "LayerOpenGL.h"
#include "ImageOpenGL.h"

namespace pyc
{

LayerOpenGL::LayerOpenGL()
{
}

LayerOpenGL::~LayerOpenGL()
{
}

void LayerOpenGL::startDrawing()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void LayerOpenGL::setColor(float red,
				float green,
				float blue,
				float alpha)
{
	glColor4f(red, green, blue, alpha);
}

void LayerOpenGL::setBackgroundColor(float red,
				float green,
				float blue)
{
	glClearColor(red, green, blue, 0.0f);
}

void LayerOpenGL::setPointSize(float size)
{
	glPointSize(size);
}

void LayerOpenGL::setLineWidth(float width)
{
	glLineWidth(width);
}

void LayerOpenGL::drawPoint(float x, float y)
{
	glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
	glEnd();
}

void LayerOpenGL::drawLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
	glEnd();
}

void LayerOpenGL::drawTriangle(float x1,
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

void LayerOpenGL::drawFilledTriangle(float x1,
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

void LayerOpenGL::drawFilledSquare(float x,
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

void LayerOpenGL::drawFilledCircle(float x,
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

Image* LayerOpenGL::loadPNG(std::string filePath)
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

