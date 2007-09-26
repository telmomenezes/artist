/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

/*
 * ACKNOWLEDGMENT: This code is based on an exemple by
 * Sven Olsen know as Lesson #43 of the NeHe tutorials.
 * http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=43
 */

#if !defined(__INCLUDE_PYCASSO_FONT_OPENGL_H)
#define __INCLUDE_PYCASSO_FONT_OPENGL_H

#include "Font.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <GL/gl.h>

#include <string>

namespace pyc
{

using std::string;

class FontOpenGL : public Font
{
public:
    FontOpenGL();
    virtual ~FontOpenGL();

    void init(string fontFile, unsigned int height);

    GLuint* mTextures;
    GLuint mListBase;

protected:
    void makedlist(FT_Face& face, char ch);
};

}

#endif

