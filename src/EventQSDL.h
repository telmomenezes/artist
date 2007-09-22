/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_EVENT_Q_SDL_H)
#define __INCLUDE_PYCASSO_EVENT_Q_SDL_H

#include "EventQ.h"
#include "pyc_types.h"

namespace pyc
{

class EventQSDL : public EventQ
{
public:
    EventQSDL();
    virtual ~EventQSDL();

    virtual bool init();
    virtual bool next();

    virtual void enableKeyChar(bool enable=true);

protected:
    KeyCode getKeyCode(int key);
    void updateKeyModifiers(int modifiers);
    MouseButton getMouseButton(int button);
};

}

#endif

