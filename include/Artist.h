/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_ARTIST_H)
#define __INCLUDE_ARTIST_H

#include "Window.h"
#include "EventQ.h"
#include "artist_types.h"

namespace art
{

class Artist
{
public:
    Artist();
    virtual ~Artist();

    Window* createWindow(int width,
                int height,
                bool fullScreen=false,
                int colorDepth=0,
                bool resizable=false,
                bool windowDecorations=true);
    Window* getWindow();

    EventQ* createEventQ();
    EventQ* getEventQ();

    bool setPreferredSystem(System sys);

    double getTime();

private:
    static System mDefaultSystem;
    static System mPreferredSystem;

    static bool mSystemSDLOpenGL;

    static Window* mWindow;
    static EventQ* mEventQ;
};

}

#endif

