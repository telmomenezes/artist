/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "LayerSDLOpenGL.h"

#include "SDL.h"
#include "SDL_opengl.h" 

namespace pyc
{

LayerSDLOpenGL::LayerSDLOpenGL()
{
}

LayerSDLOpenGL::~LayerSDLOpenGL()
{
}

void LayerSDLOpenGL::stopDrawing()
{
	if (mRoot)
	{
		SDL_GL_SwapBuffers();
	}
	else
	{
		LayerOpenGL::stopDrawing();
	}
}

}

