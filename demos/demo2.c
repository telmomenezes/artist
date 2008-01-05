/*
 * Artist Demo #2
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
    art_setWinTitle("Artist Demo #2");
    art_setBackgroundColor(255, 255, 255);
    art_setColor(0, 200, 0, 255);

    int exit = 0;
    float x = 400.0f;
    float y = 300.0f;
    float deltaX = 3.0f;
    float deltaY = 3.0f;

    /* Drawing loop */
    while (!exit)
    {
        /* Draw frame */
        art_fillCircle(x, y, 50.0f);

        /* Update window */
        art_update();

        x += deltaX;
        y += deltaY;

        if ((x >= 750) || (x <= 50))
        {
            deltaX = -deltaX;
        }
        if ((y >= 550) || (y <= 50))
        {
            deltaY = -deltaY;
        }

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

