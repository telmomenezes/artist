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

#include <string>

namespace art
{

using std::string;

class Font
{
public:
    Font();
    virtual ~Font();

    void init(string fontFile, unsigned int height);
    unsigned int getHeight(){return mHeight;}
    virtual float getTextWidth(string text)=0;

protected:
    unsigned int mHeight;
};

}

#endif

