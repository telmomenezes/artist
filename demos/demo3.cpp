#include "pyc.h"
#include <string>

int main(int argc, char *argv[])
{
	pyc::Pycasso pycasso;
	pyc::Window* win = NULL;
	pyc::Layer* root = NULL;
	pyc::EventQ* event = NULL;

	try
	{
		win = pycasso.createWindow(800, 600);
		event = pycasso.createEventQ();
		root = win->getRootLayer();
	}
	catch(std::string exception)
	{
		printf("%s", exception.c_str());
		return 1;
	}

	win->setTitle("Pycasso Demo #3");

	root->setBackgroundColor(255, 255, 255);

        pyc::Layer* subLayer = win->createLayer(200, 200);

	subLayer->startDrawing();
	subLayer->setColor(255, 0, 0);
	subLayer->fillCircle(250.0f, 250.0f, 250.0f);
	subLayer->setColor(0, 255, 255, 100);
	subLayer->fillCircle(50.0f, 50.0f, 50.0f);
	subLayer->stopDrawing();

	bool exit = false;

	while (!exit)
	{
		root->startDrawing();
		root->setColor(255, 255, 255, 255);
		root->drawLayer(subLayer, 10.0f, 10.0f);
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

