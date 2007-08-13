/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_EVENT_Q_H)
#define __INCLUDE_PYCASSO_EVENT_Q_H

#include "pyc_types.h"

namespace pyc
{

class EventQ
{
public:
	EventQ();
	virtual ~EventQ();

	virtual bool init()=0;
	virtual bool next()=0;

	EventType getType(){return mType;}

protected:
	EventType mType; 
};

}

#endif

