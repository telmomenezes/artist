/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "CanvasSDLOpenGL.h"

#include "SDL.h"
#include "SDL_opengl.h" 

namespace pyc
{

CanvasSDLOpenGL::CanvasSDLOpenGL()
{
}

CanvasSDLOpenGL::~CanvasSDLOpenGL()
{
}

void CanvasSDLOpenGL::stopDrawing()
{
	SDL_GL_SwapBuffers();
}

}

