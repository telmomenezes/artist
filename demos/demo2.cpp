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

	win->setTitle("Pycasso Demo #2");

	root->setBackgroundColor(255, 255, 255);

        pyc::Layer* pngImage = win->createPNGLayer("media/avignon.png");

	bool exit = false;

	while (!exit)
	{
		root->startDrawing();
		root->setColor(255, 0, 0);
		root->drawLayer(pngImage, 0.0f, 0.0f, 1000.0f, 1000.0f);
		root->setColor(255, 255, 255);
		root->drawLayer(pngImage, 10.0f, 10.0f);
		root->stopDrawing();

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

