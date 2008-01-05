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

#if defined(__ARTIST_OS_WIN32)
#include <windows.h>
#endif

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#if defined(__ARTIST_OS_OSX)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    GLuint* textures;
    GLuint listBase;
    float* widths;
} Art_FontOpenGL;

int _art_fontMakedlist(Art_FontOpenGL* fontOGL, FT_Face* face, char ch);

#ifdef __cplusplus
}
#endif

#endif

