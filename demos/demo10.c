/*
 * Artist Demo #10
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "art.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* Initialize Artist library, creates window */
    art_initSimple(800, 600, 0);

    /* Initial window settings */
    art_setWinTitle("Artist Demo #10");
    art_setBackgroundColor(255, 255, 255);

    char* pixels = (char*)malloc(800 * 600 * 4 * sizeof(char));

    unsigned int x;
    unsigned int y;
    for (y = 0; y < 600; y++)
    {
        for (x = 0; x < 800; x++)
        {
            unsigned int offset = (y * 800 * 4) + (x * 4);
            pixels[offset] = x / 4;
            pixels[offset + 1] = y / 4;
            pixels[offset + 2] = (float)x / (float)y * 200;
            pixels[offset + 3] = 255;
        }
    }

    int exit = 0;

    /* Drawing loop */
    while (!exit)
    {
        art_drawPixels(pixels);

        /* Update window */
        art_update();

        /* Check events */
        while (art_nextEvent())
        {
            if (art_getEventType() == ART_EVENT_QUIT)
            {
                exit = 1;
            }
            else if (art_getEventType() == ART_EVENT_KEY_DOWN)
            {
                if (art_getKeyCode() == ART_KEY_ESCAPE)
                {
                    exit = 1;
                }
            }
        }
    }
    
    /* Close artist libarary before exiting program */
    art_close();

    free(pixels);

    return 0;
}

