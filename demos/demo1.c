#include "art.h"

int main(int argc, char *argv[])
{
    art_initSimple(800, 600, 0);

    art_setWinTitle("Artist Demo #1");

    art_setBackgroundColor(255, 255, 255);

    int exit = 0;
    float x = 400.0f;
    float y = 300.0f;
    float deltaX = 3.0f;
    float deltaY = 3.0f;

    art_setColor(0, 200, 0, 255);

    while (!exit)
    {
        art_fillCircle(x, y, 50.0f);

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
    
    art_close();
    return 0;
}

