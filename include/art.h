/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "artist_types.h"
#include "artist.h"
#include "layer.h"
#include "font.h"
#include "eventq.h"

// SDL on macs needs this
// We'll get rid of this hack when we have a mac-specific system
#if defined _OSX_SDL_
#define main SDL_main
#ifdef __cplusplus
extern "C" int SDL_main(int argc, char *argv[]);
#else
extern int SDL_main(int argc, char *argv[]);
#endif

#endif

