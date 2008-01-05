/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_ARTIST_FONT_H)
#define __INCLUDE_ARTIST_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    unsigned int height;
    void* extraData;
    void* prevFont;
    void* nextFont;
} Art_Font;

unsigned int art_getFontHeight(Art_Font* font);
float art_getTextWidth(char* text);

int _art_initFont(Art_Font* font, char* fontFile, unsigned int height);
int _art_destroyFont(Art_Font* font);

#ifdef __cplusplus
}
#endif

#endif

