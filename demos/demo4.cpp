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

    win->setTitle("Pycasso Demo #4");

    root->setBackgroundColor(255, 255, 255);

    bool exit = false;

    pyc::Font* font = win->loadFont("media/vera/Vera.ttf", 9);
    root->setFont(font);
    
    std::string text = "Hello Pycasso World :)";
    float textWidth = font->getTextWidth(text);

    while (!exit)
    {
        root->setColor(250, 0, 0);
        root->drawLine(100, 100, 100 + textWidth, 100);
        root->setColor(0, 150, 0);
        root->drawText(100, 100, text);

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

