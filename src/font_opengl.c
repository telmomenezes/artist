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

#include "font.h"
#include "font_opengl.h"
#include "functions.h"
#include "artist.h"

int _art_fontMakedlist(Art_FontOpenGL* fontOGL, FT_Face* face, char ch)
{
    if (FT_Load_Glyph(*face, FT_Get_Char_Index(*face, ch), FT_LOAD_DEFAULT))
    {
        printf("Error processing font file: FT_Load_Glyph failed\n");
        return -1;
    }

    FT_Glyph glyph;
    if (FT_Get_Glyph((*face)->glyph, &glyph))
    {
        printf("Error processing font file: FT_Load_Glyph failed\n");
        return -1;
    }

    FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
    FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;

    FT_Bitmap* bitmap = &(bitmapGlyph->bitmap);

    int width = _art_nextPowerOfTwo(bitmap->width);
    int height = _art_nextPowerOfTwo(bitmap->rows);

    GLubyte* expandedData = (GLubyte*)malloc(sizeof(GLubyte) * 2 * width * height);

    int j;
    int i;
    for(j = 0; j < height; j++)
    {
        for(i = 0; i < width; i++)
        {
            expandedData[2 * (i + j * width)] = expandedData[2 * (i + j * width) + 1] =
                (i >= bitmap->width || j >= bitmap->rows) ?
                0 : bitmap->buffer[i + bitmap->width * j];
        }
    }

    glBindTexture(GL_TEXTURE_2D, fontOGL->textures[ch]);
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

    free(expandedData);

    glNewList(fontOGL->listBase + ch, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, fontOGL->textures[ch]);

    glTranslatef(bitmapGlyph->left, 0, 0);

    GLdouble texX = (GLdouble)bitmap->width / (GLdouble)width;
    GLdouble texY = (GLdouble)bitmap->rows / (GLdouble)height;

    GLfloat lower = (float)bitmapGlyph->top-bitmap->rows;
    GLfloat y1 = -((GLfloat)bitmap->rows) - lower;
    GLfloat y2 = -lower;
    GLfloat advance = ((GLfloat)(*face)->glyph->advance.x) / 64.0f;

    glBegin(GL_QUADS);
    
    glTexCoord2d(0.0, 0.0);
    glVertex2f(0.0, y1);
    glTexCoord2d(0.0, texY);
    glVertex2f(0.0, y2);
    glTexCoord2d(texX, texY);
    glVertex2f(bitmap->width, y2);
    glTexCoord2d(texX, 0.0);
    glVertex2f(bitmap->width, y1);
    glEnd();
    glTranslatef(advance, 0.0f, 0.0f);

    glEndList();

    fontOGL->widths[ch] = bitmapGlyph->left + advance;

    return 0;
}

int _art_initFont(Art_Font* font, const char* fontFile, unsigned int height)
{
    font->height = height;
    font->nextFont = NULL;
    font->prevFont = NULL;
    Art_FontOpenGL* extraData = malloc(sizeof(Art_FontOpenGL));
    font->extraData = extraData;
    extraData->textures = malloc(128 * sizeof(GLuint));

    extraData->widths = (float*)(malloc(128 * sizeof(float)));
    
    FT_Library library;
    if (FT_Init_FreeType(&library))
    {
        printf("Failed to initialize the FreeType library\n");
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(library, fontFile, 0, &face)) 
    {
        printf("Failed to load font file: %s\n", fontFile);
        return -1;
    }

    FT_Set_Char_Size(face, height * 64, height * 64, 96, 96);

    extraData->listBase = glGenLists(128);
    glGenTextures(128, extraData->textures);

    unsigned char i;
    for (i = 0; i < 128; i++)
    {
        if (_art_fontMakedlist(extraData, &face, i) != 0)
        {
            return -1;
        }
    }

    FT_Done_Face(face);

    FT_Done_FreeType(library);

    return 0;
}

float art_getTextWidth(const char* text)
{
    if (artG_session.currentLayer->currentFont == NULL)
    {
        return 0.0f;
    }
    Art_FontOpenGL* extraData = (Art_FontOpenGL*)artG_session.currentLayer->currentFont->extraData;
    unsigned int length = strlen(text);
    const char* textBuf = text;
    float width = 0;

    unsigned int i;
    for (i = 0; i < length; i++)
    {
        width += extraData->widths[textBuf[i]];
    }

    return width;
}

int _art_destroyFont(Art_Font* font)
{
    Art_FontOpenGL* extraData = (Art_FontOpenGL*)font->extraData;
    glDeleteLists(extraData->listBase, 128);

    if (extraData->textures)
    {
        glDeleteTextures(128, extraData->textures);
        free(extraData->textures);
        extraData->textures = NULL;
    }

    if (extraData->widths)
    {
        free(extraData->widths);
        extraData->widths = NULL;
    }

    return 0;
}
