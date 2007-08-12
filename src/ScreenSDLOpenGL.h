/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_SCREEN_SDL_OPENGL_H)
#define __INCLUDE_PYCASSO_SCREEN_SDL_OPENGL_H

#include "CanvasOpenGL.h"
#include <math.h>

namespace pyc
{

class ScreenSDLOpenGL : public CanvasOpenGL
{
public:
	ScreenSDLOpenGL();
	virtual ~ScreenSDLOpenGL();

	virtual bool init(int width,
		int height,
		bool fullScreen=false,
		int colorDepth=0,
		bool resizable=false,
		bool windowDecorations=true);

	virtual void setCaption(std::string caption);

	virtual void beginFrame();
        virtual void endFrame();
};

}

#endif

