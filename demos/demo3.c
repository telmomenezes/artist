/*
 * Artist Demo #3
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 _* license. The license text is available in the file COPYING.
 */

#include "art.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* Initialize Artist library, creates window */
    art_initSimple(800, 600, 0);

    /* Initial window settings */
    art_setWinTitle("Artist Demo #3");
    art_setClearWindowOnUpdate(0);
    art_setBackgroundColor(255, 255, 255);

    int exit = 0;

    /* Drawing loop */
    while (!exit)
    {
        /* Draw frame */
        int gray = rand() % 255;
        art_setColor(gray, gray, gray, 255);
        art_setLineWidth(rand() % 10);
        art_drawLine(rand() % 800, rand() % 600, rand() % 800, rand() % 600);

        art_setColor(rand() % 255, 0, 0, 255);
        art_setPointSize(rand() % 10);
        art_drawPoint(rand() % 800, rand() % 600);

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

