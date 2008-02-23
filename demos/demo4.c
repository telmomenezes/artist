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

    int exit = 0;

    /* Initialize various sizes of fonts */
    int sizeCount = 6;
    Art_Font* fonts[sizeCount];

    int i;
    int size = 4;
    for (i = 0; i < sizeCount; i++)
    {
        fonts[i] = art_loadFont("media/vera/Vera.ttf", size);
        size *= 2;
    }
    
    char* text = "Hello Artist World :)";

    /* Drawing loop */
    while (!exit)
    {
        size = 4;
        int y = 100;
        for (i = 0; i < sizeCount; i++)
        {
            art_setFont(fonts[i]);
            float textWidth = art_getTextWidth(text);
            art_setColor(10, 10, 10, 255);
            art_drawLine(0, y, textWidth, y);
            art_setColor(255, 0, 0, 255);
            art_drawText(0, y, text);
            y += size * 3;
            size *= 2;
        }

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

