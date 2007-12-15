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

    win->setTitle("Artist Demo #6");

    root->setBackgroundColor(255, 255, 255);

    bool exit = false;

    float x1 = (float)(rand() % 800);
    float x2 = (float)(rand() % 800);
    float x3 = (float)(rand() % 800);
    float y1 = (float)(rand() % 600);
    float y2 = (float)(rand() % 600);
    float y3 = (float)(rand() % 600);
    int r = rand() & 255;
    int g = rand() & 255;
    int b = rand() & 255;

    while (!exit)
    {
        root->setColor(r, g, b);
        root->fillTriangle(x1, y1, x2, y2, x3, y3);

        win->update();

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
                else if (event->getKeyCode() == art::KEY_RETURN)
                {
                    x1 = (float)(rand() % 800);
                    x2 = (float)(rand() % 800);
                    x3 = (float)(rand() % 800);
                    y1 = (float)(rand() % 600);
                    y2 = (float)(rand() % 600);
                    y3 = (float)(rand() % 600);
                    r = rand() & 255;
                    g = rand() & 255;
                    b = rand() & 255;
                }
            }
        }
    }

    return 0;
}

