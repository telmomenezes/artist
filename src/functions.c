/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "functions.h"

int _art_nextPowerOfTwo(int value)
{
    int result = 2;

    while (result < value)
    {
        result *= 2;
    }

    return result;
}

