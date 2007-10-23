/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_EVENT_NULL_H)
#define __INCLUDE_PYCASSO_EVENT_NULL_H

#include "EventQ.h"
#include "pyc_types.h"

namespace pyc
{

class EventQNull : public EventQ
{
public:
    EventQNull();
    virtual ~EventQNull();

    virtual bool init();
    virtual bool next();

    virtual void enableKeyChar(bool enable=true){}
};

}

#endif

