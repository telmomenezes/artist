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

#include "FontOpenGL.h"
#include "functions.h"

#include <stdexcept>

namespace pyc
{

FontOpenGL::FontOpenGL()
{
}

FontOpenGL::~FontOpenGL()
{
    glDeleteLists(mListBase, 128);
    glDeleteTextures(128, mTextures);
    delete [] mTextures;
}

void FontOpenGL::makedlist(FT_Face& face, char ch)
{
    if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
    {
        throw std::runtime_error("Error processing font file: FT_Load_Glyph failed");
    }

    FT_Glyph glyph;
    if (FT_Get_Glyph(face->glyph, &glyph))
    {
        throw std::runtime_error("Error processing font file: FT_Get_Glyph failed");
    }

    FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
    FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;

    FT_Bitmap& bitmap = bitmapGlyph->bitmap;

    int width = nextPowerOfTwo(bitmap.width);
    int height = nextPowerOfTwo(bitmap.rows);

    GLubyte* expandedData = new GLubyte[2 * width * height];

    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            expandedData[2 * (i + j * width)] = expandedData[2 * (i + j * width) + 1] =
                (i >= bitmap.width || j >= bitmap.rows) ?
                0 : bitmap.buffer[i + bitmap.width * j];
        }
    }

    glBindTexture( GL_TEXTURE_2D, mTextures[ch]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    width,
                    height,
                    0,
                    GL_LUMINANCE_ALPHA,
                    GL_UNSIGNED_BYTE,
                    expandedData);

    delete [] expandedData;

    glNewList(mListBase + ch, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, mTextures[ch]);

    glTranslatef(bitmapGlyph->left, 0, 0);

    float texX = (float)bitmap.width / (float)width;
    float texY = (float)bitmap.rows / (float)height;

    float lower = bitmapGlyph->top-bitmap.rows;
    float y1 = -bitmap.rows - lower;
    float y2 = -lower;
    float advance = ((float)face->glyph->advance.x) / 64.0f;

    glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2f(0, y1);
        glTexCoord2d(0, texY);
        glVertex2f(0, y2);
        glTexCoord2d(texX, texY);
        glVertex2f(bitmap.width, y2);
        glTexCoord2d(texX, 0);
        glVertex2f(bitmap.width, y1);
    glEnd();

    glTranslatef(advance, 0.0f, 0.0f);

    glEndList();
}



void FontOpenGL::init(string fontFile, unsigned int height)
{
    mTextures = new GLuint[128];
    
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

    FT_Set_Char_Size(face, mHeight * 64, mHeight * 64, 96, 96);

    mListBase = glGenLists(128);
    glGenTextures(128, mTextures);

    for(unsigned char i = 0; i < 128; i++)
    {
        makedlist(face, i);
    }

    FT_Done_Face(face);

    FT_Done_FreeType(library);
}

}

