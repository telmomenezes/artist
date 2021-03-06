/*
 * Artist Demo #1
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
    art_setWinTitle("Artist Demo #1");
    art_setBackgroundColor(255, 255, 255);

    int exit = 0;

    /* Drawing loop */
    while (!exit)
    {
        /* Draw frame */
        art_setColor(255, 0, 0, 255);
        art_drawTriangle(50.0, 150.0, 150.0, 150.0, 100.0, 50.0);
        art_drawSquare(300.0, 100.0, 100.0);
        art_drawCircle(500.0, 100.0, 50.0);
        art_drawRectangle(680.0, 50.0, 40.0, 100.0);
        art_drawRectangle(650.0, 80.0, 100.0, 40.0);

        art_setColor(0, 255, 0, 255);
        art_fillTriangle(50.0, 350.0, 150.0, 350.0, 100.0, 250.0);
        art_fillSquare(300.0, 300.0, 100.0);
        art_fillCircle(500.0, 300.0, 50.0);
        art_fillRectangle(680.0, 250.0, 40.0, 100.0);
        art_fillRectangle(650.0, 280.0, 100.0, 40.0);

        art_setColor(0, 0, 255, 255);
        art_fillCircleSlice(100.0f, 500.0f, 50.0f, 0.0, M_PI * 0.5);
        art_fillCircleSlice(300.0f, 500.0f, 50.0f, 0.0, M_PI);
        art_fillCircleSlice(500.0f, 500.0f, 50.0f, 0.0, M_PI * 1.5);
        art_fillCircle(700.0f, 500.0f, 50.0f);

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

