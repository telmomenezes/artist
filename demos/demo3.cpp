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

	root->setBackgroundColor(1.0f, 1.0f, 1.0f);

        pyc::Layer* subLayer = win->createLayer(200, 200);

	subLayer->startDrawing();
	subLayer->setColor(1.0f, 0.0f, 0.0f);
	subLayer->drawFilledCircle(250.0f, 250.0f, 250.0f);
	subLayer->setColor(0.0f, 1.0f, 1.0f, 0.5f);
	subLayer->drawFilledCircle(50.0f, 50.0f, 50.0f);
	subLayer->stopDrawing();

	bool exit = false;

	while (!exit)
	{
		root->startDrawing();
		root->setColor(1.0f, 1.0f, 1.0f);
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

