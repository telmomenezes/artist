#include "pyc.h"
#include <string>

int main(int argc, char *argv[])
{
    pyc::Pycasso pycasso;
    pyc::Window* win = NULL;
    pyc::Layer* root = NULL;
    pyc::EventQ* event = NULL;

    win = pycasso.createWindow(800, 600);
    event = pycasso.createEventQ();
    root = win->getRootLayer();

    win->setTitle("Pycasso Demo #4");

    root->setBackgroundColor(255, 255, 255);

    bool exit = false;

    root->setColor(0, 150, 0);
    pyc::Font* font = win->loadFont("test.TTF", 9);
    root->setFont(font);

    while (!exit)
    {
        root->print(100, 100, "Hello Pycasso World!");

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

