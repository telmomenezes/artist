/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "artist_types.h"
#include "Artist.h"
#include "Window.h"
#include "Layer.h"
#include "Layer2D.h"
#include "Font.h"
#include "EventQ.h"

// SDL on macs needs this
// We'll get rid of this hack when we have a mac-specific system
#if defined __APPLE__
#define main SDL_main
extern "C" int SDL_main(int argc, char *argv[]);
#endif

