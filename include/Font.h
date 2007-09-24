/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_FONT_H)
#define __INCLUDE_PYCASSO_FONT_H

#include <string>

namespace pyc
{

using std::string;

class Font
{
public:
    Font();
    virtual ~Font();

    void init(string fontFile, unsigned int height);

protected:
    unsigned int mHeight;
};

}

#endif

