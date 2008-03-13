/*
 * Artist Demo #8
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
    art_setWinTitle("Artist Demo #8");
    art_setBackgroundColor(255, 255, 255);

    int exit = 0;

    // Load images to a layers
    Art_Layer* grass = art_loadImage("media/grass.jpg");
    Art_Layer* fabric = art_loadImage("media/fabric.jpg");

    float grassX = 0;
    float grassY = 0;

    /* Drawing loop */
    while (!exit)
    {
        art_setColor(0, 255, 0, 255);
        art_setBrush(grass);
        art_fillSquare(sin(grassX) * 100, grassY, 5000);

        grassX += 0.03f;
        grassY += 2.0f;
        if (grassY > grass->height)
        {
            grassY = 0.0f;
        }

        art_setColor(255, 0, 0, 100);
        art_setBrush(fabric);
        art_fillCircle(400.0f, 300.0f, 120.0f);
        art_setColor(255, 0, 0, 255);
        art_fillCircle(400.0f, 300.0f, 100.0f);

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

