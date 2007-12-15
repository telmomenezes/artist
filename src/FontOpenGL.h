/*
 * Artist
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

#if !defined(__INCLUDE_ARTIST_FONT_OPENGL_H)
#define __INCLUDE_ARTIST_FONT_OPENGL_H

#include "Font.h"

#if defined(__ARTIST_OS_WIN32)
#include <windows.h>
#endif

extern "C" {
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
}

#if defined(__ARTIST_OS_OSX)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <string>

namespace art
{

using std::string;

class FontOpenGL : public Font
{
public:
    FontOpenGL();
    virtual ~FontOpenGL();

    void init(string fontFile, unsigned int height);
    virtual float getTextWidth(string text);

    GLuint* mTextures;
    GLuint mListBase;
    float* mWidths;

protected:
    void makedlist(FT_Face& face, char ch);
};

}

#endif

