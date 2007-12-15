#include "art.h"
#include <string>

int main(int argc, char *argv[])
{
    art::Artist artist;
    art::Window* win = NULL;
    art::Layer2D* root = NULL;
    art::EventQ* event = NULL;

    win = artist.createWindow(800, 600);
    event = artist.createEventQ();
    root = win->getRootLayer2D();

    win->setTitle("Artist Demo #1");

    root->setBackgroundColor(255, 255, 255);

    bool exit = false;
    float x = 400.0f;
    float y = 300.0f;
    float deltaX = 3.0f;
    float deltaY = 3.0f;

    while (!exit)
    {
        root->setColor(255, 0, 0);
        root->fillCircle(x, y, 50.0f);

        win->update();

        x += deltaX;
                y += deltaY;

        if (x >= 750)
        {
            deltaX = -deltaX;
        }
        if (x <= 50)
        {
            deltaX = -deltaX;
        }
                if (y >= 550)
        {
            deltaY = -deltaY;
        }
        if (y <= 50)
        {
            deltaY = -deltaY;
        }

        while (event->next())
        {
            if (event->getType() == art::EVENT_QUIT)
            {
                exit = true;
            }
            else if (event->getType() == art::EVENT_KEY_DOWN)
            {
                if (event->getKeyCode() == art::KEY_ESCAPE)
                {
                    exit = true;
                }
            }
        }
    }

    return 0;
}

