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

    win->setTitle("Artist Demo #4");

    root->setBackgroundColor(255, 255, 255);

    bool exit = false;

    art::Font* font = win->loadFont("media/vera/Vera.ttf", 9);
    root->setFont(font);
    
    std::string text = "Hello Artist World :)";
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

