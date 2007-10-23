/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_FONT_NULL_H)
#define __INCLUDE_PYCASSO_FONT_NULL_H

#include "Font.h"

#include <string>

namespace pyc
{

using std::string;

class FontNull : public Font
{
public:
    FontNull();
    virtual ~FontNull();

    void init(string fontFile, unsigned int height){}
    virtual float getTextWidth(string text){return 1.0f;}
};

}

#endif

