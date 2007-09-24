/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "FontOpenGL.h"

#include <stdexcept>

namespace pyc
{

FontOpenGL::FontOpenGL()
{
}

FontOpenGL::~FontOpenGL()
{
    for (unsigned int i = 0; i < 128; i++)
    {
        delete mChars[i];
    }
}

void FontOpenGL::init(string fontFile, unsigned int height)
{
    mHeight = height;

    FT_Library library;

    if (FT_Init_FreeType(&library))
    {
        throw std::runtime_error("Failed to initialize the FreeType library");
    }

    FT_Face face;
    if (FT_New_Face(library, fontFile.c_str(), 0, &face)) 
    {
        throw std::runtime_error("Failed to load font file: " + fontFile);
    }

    unsigned int freeTypeHeight = mHeight * 64;
    FT_Set_Char_Size(face, freeTypeHeight, freeTypeHeight, 96, 96);

    for (unsigned int i = 0; i < 128; i++)
    {
        mChars[i] = loadChar(i, face);
    }

    FT_Done_Face(face);

    FT_Done_FreeType(library);
}

CharacterOpenGL* FontOpenGL::loadChar(char ch, FT_Face& face)
{
    CharacterOpenGL* charGL = new CharacterOpenGL();

    if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
    {
        throw std::runtime_error("FT_Load_Glyph failed");
    }

    FT_Glyph glyph;
    if (FT_Get_Glyph(face->glyph, &glyph))
    {
        throw std::runtime_error("FT_Get_Glyph failed");
    }

    FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

    FT_Bitmap& bitmap = bitmap_glyph->bitmap;

    charGL->mAdvance = face->glyph->advance.x >> 6;
    charGL->mLeft = bitmap_glyph->left;
    charGL->mWidth = bitmap.width;
    charGL->mHeight = bitmap.rows;
    charGL->mMoveUp = bitmap_glyph->top-bitmap.rows;
        
    charGL->mData = new unsigned char[2 * charGL->mWidth * charGL->mHeight];

    for (int x = 0; x < charGL->mWidth; x++)
    {
        for (int y = 0; y < charGL->mHeight; y++)
        {
            const int my = charGL->mHeight - 1 - y;
            charGL->mData[2 * (x + charGL->mWidth * my)] = 255;
            charGL->mData[2 * (x + charGL->mWidth * my) + 1] = bitmap.buffer[x + charGL->mWidth * y];
        }
    }

    return charGL;
}

}

