#include "pyc.h"
#include <string>

int main(int argc, char *argv[])
{
    pyc::Pycasso pycasso;
    pyc::Window* win = NULL;
    pyc::Layer2D* root = NULL;
    pyc::EventQ* event = NULL;

    win = pycasso.createWindow(800, 600);
    event = pycasso.createEventQ();
    root = win->getRootLayer2D();

    win->setTitle("Pycasso Demo #7");

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
            if (event->getType() == pyc::EVENT_QUIT)
            {
                exit = true;
            }
            else if (event->getType() == pyc::EVENT_KEY_DOWN)
            {
                if (event->getKeyCode() == pyc::KEY_ESCAPE)
                {
                    exit = true;
                }
            }
        }
    }

    return 0;
}

