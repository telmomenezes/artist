/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_FONT_OPENGL_H)
#define __INCLUDE_PYCASSO_FONT_OPENGL_H

#include "Font.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <vector>
#include <string>

#include <stdexcept>

namespace pyc
{

using std::string;

class CharacterOpenGL
{
public:
    int mWidth;
    int mHeight;
    int mAdvance;
    int mLeft;
    int mMoveUp;
    unsigned char* mData;

    CharacterOpenGL(){} 
    virtual ~CharacterOpenGL(){delete [] mData;}
};

class FontOpenGL : public Font
{
public:
    FontOpenGL();
    virtual ~FontOpenGL();

    void init(string fontName, unsigned int height);

    CharacterOpenGL* mChars[128];

protected:
    CharacterOpenGL* loadChar(char ch, FT_Face& face);
};

}

#endif

