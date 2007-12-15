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

    win->setTitle("Artist Demo #7");

    root->setBackgroundColor(255, 255, 255);

    bool exit = false;

    while (!exit)
    {
        root->clearTranslation();
        for (unsigned int i = 1; i < 5; i++)
        {
            root->clearScale();
            root->setColor(255, 0, 0, 100);
            root->fillCircle(100.0f, 100.0f, 50.0f);

            root->setScale(0.5f, 0.5f);
            root->setColor(0, 255, 0, 150);
            root->fillCircle(100.0f, 100.0f, 50.0f);

            root->setScale(1.5f, 1.5f);
            root->setColor(0, 0, 255, 100);
            root->fillCircle(100.0f, 100.0f, 50.0f);

            root->setTranslation(i * 100.0f, i * 100.0f);
        }

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
            }
        }
    }

    return 0;
}

