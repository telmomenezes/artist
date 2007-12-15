/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "EventQNull.h"

namespace art
{

EventQNull::EventQNull()
{
}

EventQNull::~EventQNull()
{
}

bool EventQNull::init()
{
    return true;
}

bool EventQNull::next()
{
    return false;
}

}

