#include "pyc.h"
#include <string>

void updateScale(pyc::Layer2D* layer, float scale)
{
    layer->setScale(scale, scale);

    float newCenterX = 400.0f * scale;
    float newCenterY = 300.0f * scale;

    layer->setScreenTranslation(400.0f - newCenterX, 300.0f - newCenterY);
}

int main(int argc, char *argv[])
{
    pyc::Pycasso pycasso;
    pyc::Window* win = NULL;
    pyc::Layer2D* root = NULL;
    pyc::EventQ* event = NULL;

    win = pycasso.createWindow(800, 600);
    event = pycasso.createEventQ();
    root = win->getRootLayer2D();

    win->setTitle("Pycasso Demo #5");

    root->setBackgroundColor(255, 255, 255);

    pyc::Layer2D* pngImage = win->createPNGLayer("media/avignon.png");
    
    pyc::Font* font = win->loadFont("media/vera/Vera.ttf", 9);
    root->setFont(font);

    bool exit = false;

    float rot = 0.0f;

    float scale = 1.0f;

    while (!exit)
    {
        root->setRotation(400, 300, rot);

        root->setColor(50, 50, 50);
        root->drawText(500, 200, "Hello World!");

        root->setColor(0, 150, 0);
        root->fillSquare(300, 200, 50);

        root->setColor(150, 150, 255);
        root->drawCircle(370, 270, 50);

        root->setColor(255, 0, 0);
        for (float x = 350; x <= 450; x += 10.0f)
        {
            for (float y = 250; y <= 350; y += 10.0f)
            {
                root->drawPoint(x, y);
            }
        }

        root->setColor(150, 150, 0);
        root->drawLine(500, 400, 550, 450);
        root->drawLine(550, 400, 500, 450);

        root->setColor(255, 255, 255, 200);
        root->drawLayer(pngImage, 0.0f, 0.0f);
    
        root->setColor(134, 219, 43);
        root->drawTriangle(10, 12, 23, 45, 100, 43);

        rot += 0.005f;

        root->setColor(0, 0, 150);
        root->clearRotation();
        root->fillCircle(400, 300, 10);

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
            else if (event->getType() == pyc::EVENT_MOUSE_WHEEL_UP)
            {
                scale += 0.05f;
                updateScale(root, scale);
            }
            else if (event->getType() == pyc::EVENT_MOUSE_WHEEL_DOWN)
            {
                if (scale >= 0.05f)
                {
                    scale -= 0.05f;
                    updateScale(root, scale);
                }
            }
        }
    }

    return 0;
}

