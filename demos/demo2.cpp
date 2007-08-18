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

	win->setTitle("Pycasso Demo #2");

	//root->setBackgroundColor(pyc::Color(1.0f, 1.0f, 1.0f));

        pyc::Layer* pngImage = win->createPNGLayer("media/avignon.png");

	bool exit = false;

	pyc::Color backColor(1.0f, 0.0f, 0.0f);
	pyc::Color frontColor(1.0f, 1.0f, 1.0f);

	while (!exit)
	{
		root->startDrawing();
		root->setColor(backColor);
		root->drawLayer(pngImage, 0.0f, 0.0f, 1000.0f, 1000.0f);
		root->setColor(frontColor);
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

