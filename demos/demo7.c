/*
 * Artist Demo #7
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "art.h"

void updateScale(float scale)
{
    art_setScale(scale, scale);

    float newCenterX = 400.0f * scale;
    float newCenterY = 300.0f * scale;

    art_setScreenTranslation(400.0f - newCenterX, 300.0f - newCenterY);
}

int main(int argc, char *argv[])
{
    /* Initialize Artist library, creates window */
    art_initSimple(800, 600, 0);

    /* Initial window settings */
    art_setWinTitle("Artist Demo #7");
    art_setBackgroundColor(0, 0, 0);

    int exit = 0;

    // Load image to a layer
    Art_Layer* image = art_loadImage("media/saturn.jpg");

    float scale = 1.0f;
    float rot = 0.0f;

    /* Drawing loop */
    while (!exit)
    {
        art_setRotation(400, 300, rot);
        art_setColor(255, 255, 255, 255);
        art_drawLayer(image, 80.0f, 25.0f);

        rot += 0.005f;

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
            else if (art_getEventType() == ART_EVENT_MOUSE_WHEEL_UP)
            {
                scale += 0.05f;
                updateScale(scale);
            }
            else if (art_getEventType() == ART_EVENT_MOUSE_WHEEL_DOWN)
            {
                if (scale >= 0.05f)
                {
                    scale -= 0.05f;
                    updateScale(scale);
                }
            }
        }
    }
    
    /* Close artist libarary before exiting program */
    art_close();
    return 0;
}

