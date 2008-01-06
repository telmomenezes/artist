/*
 * Artist Demo #4
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "art.h"

int main(int argc, char *argv[])
{
    /* Initialize Artist library, creates window */
    art_initSimple(800, 600, 0);

    /* Initial window settings */
    art_setWinTitle("Artist Demo #4");
    art_setBackgroundColor(255, 255, 255);
    art_setColor(0, 200, 0, 255);

    Art_Layer* layer = art_createLayer(100.0, 100.0); 
    art_drawToLayer(layer);
    art_fillCircle(50.0, 50.0, 50.0);
    art_drawToRoot();

    int exit = 0;

    /* Drawing loop */
    while (!exit)
    {
        /* Draw frame */
        art_drawLayer(layer, 100.0, 100.0);

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
    return 0;
}

