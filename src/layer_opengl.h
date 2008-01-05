/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */


#if !defined(__INCLUDE_ARTIST_LAYER_OPENGL_H)
#define __INCLUDE_ARTIST_LAYER_OPENGL_H

#if defined(__ARTIST_OS_WIN32)
#include <windows.h>
#endif

#if defined(__ARTIST_OS_OSX)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int locked;

    GLuint texture;

    int textureWidth;
    int textureHeight;

    int firstUnlock;

    float fRed;
    float fGreen;
    float fBlue;

    int rotate;
    float rotX;
    float rotY;
    float rotAngle;

    int scale;
    float scaleX;
    float scaleY;

    int translate;
    float transX;
    float transY;

    int screenTranslate;
    float screenTransX;
    float screenTransY;
} Art_LayerOpenGL;

#ifdef __cplusplus
}
#endif

#endif

