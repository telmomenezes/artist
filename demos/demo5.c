/*
 * Artist Demo #5
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
    art_setWinTitle("Artist Demo #5");
    art_setBackgroundColor(0, 0, 0);

    int exit = 0;

    // Load image to a layer
    Art_Layer* image = art_loadImage("media/saturn.jpg");

    int color = 255;
    int deltaColor = -1;

    /* Drawing loop */
    while (!exit)
    {
        color += deltaColor;

        if (color < 0)
        {
            color = 0;
            deltaColor = 1;
        }
        else if (color > 255)
        {
            color = 255;
            deltaColor = -1;
        }

        art_setColor(255, color, color, 255);
        art_drawLayer(image, 80.0f, 25.0f);

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

