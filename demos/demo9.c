/*
 * Artist Demo #9
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
    art_setWinTitle("Artist Demo #9");
    art_setBackgroundColor(255, 255, 255);

    int exit = 0;

    // Load images to a layers
    Art_Layer* grass = art_loadImage("media/grass.jpg");
    Art_Layer* fabric = art_loadImage("media/fabric.jpg");
    Art_Layer* saturn = art_loadImage("media/saturn.jpg");

    float v1 = 0.0f;

    /* Drawing loop */
    while (!exit)
    {
        art_setColor(255, 0, 0, 255);
        art_setTexture(fabric);
        art_setTexturePosition(v1 * 100, cos(v1 * 1.7) * 200);
        art_fillCircle(200.0f, 150.0f, 100.0f);

        art_setColor(0, 255, 0, 255);
        art_setTexture(grass);
        art_setTexturePosition(cos(v1 * 1.4) * 150, sin(v1 * 1.5) * 170);
        art_setTextureScale(cos(v1 * 1.3));
        art_fillCircle(400.0f, 450.0f, 100.0f);

        art_setColor(255, 255, 255, 255);
        art_setTexture(saturn);
        art_setTextureScale(sin(v1));
        art_fillCircle(600.0f, 150.0f, 100.0f);

        v1 += 0.01f;

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

