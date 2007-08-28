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

	win->setTitle("Pycasso Demo #1");

	root->setBackgroundColor(255, 255, 255);

	bool exit = false;
	float x = 400.0f;
        float y = 300.0f;
	float deltaX = 0.5f;
        float deltaY = 0.5f;

	while (!exit)
	{
		root->setColor(255, 0, 0);
		root->fillCircle(x, y, 50.0f);

		root->setColor(0, 255, 0);
		root->fillSquare(y, x, 50.0f, rot);

		win->update();

		x += deltaX;
                y += deltaY;

		if (x >= 750)
		{
			deltaX = -deltaX;
		}
		if (x <= 50)
		{
			deltaX = -deltaX;
		}
                if (y >= 550)
		{
			deltaY = -deltaY;
		}
		if (y <= 50)
		{
			deltaY = -deltaY;
		}

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

