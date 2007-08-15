/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_PYCASSO_CANVAS_SDL_OPENGL_H)
#define __INCLUDE_PYCASSO_CANVAS_SDL_OPENGL_H

#include "CanvasOpenGL.h"

namespace pyc
{

class CanvasSDLOpenGL : public CanvasOpenGL
{
public:
	CanvasSDLOpenGL();
	virtual ~CanvasSDLOpenGL();

	virtual void stopDrawing();
};

}

#endif

