/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_WINDOW_SDL_OPENGL_H)
#define __INCLUDE_PYCASSO_WINDOW_SDL_OPENGL_H

#include "Window.h"
#include <string>

namespace pyc
{

class WindowSDLOpenGL : public Window
{
public:
    WindowSDLOpenGL();
    virtual ~WindowSDLOpenGL();

    virtual void init(int width,
    int height,
    bool fullScreen=false,
    int colorDepth=0,
    bool resizable=false,
    bool windowDecorations=true);

    virtual void update();

    virtual void setTitle(std::string title);

    virtual void showCursor(bool show);

    virtual Layer2D* createLayer2D(int width, int height);
    virtual Layer2D* loadImage(std::string filePath);

    virtual Font* loadFont(string fontName, unsigned int height);

    virtual void setClearOnUpdate(bool clear);

    virtual bool isReal(){return true;}
};

}

#endif

