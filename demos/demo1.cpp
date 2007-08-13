#include "pyc.h"
#include <string>

int main(int argc, char *argv[])
{
	pyc::Pycasso pycasso;
	pyc::Canvas* screen = NULL;
	pyc::EventQ* event = NULL;

	try
	{
		screen = pycasso.createScreen(800, 600);
		event = pycasso.createEventQ();
	}
	catch(std::string exception)
	{
		printf("%s", exception.c_str());
		return 1;
	}

	screen->setTitle("Pycasso Demo #1");

	screen->setBackgroundColor(1.0f, 1.0f, 1.0f);

	bool exit = false;
	float x = 0.0f;
	float delta = 1.0f;

	while (!exit)
	{
		screen->startDrawing();
		screen->setColor(1.0f, 0.0f, 0.0f);
		screen->drawFilledCircle(x, 300.0f, 50.0f);
		screen->stopDrawing();

		x += delta;

		if (x >= 800)
		{
			delta = -delta;
		}
		if (x <=0)
		{
			delta = -delta;
		}

		while (event->next())
		{
			if (event->getType() == pyc::QUIT)
			{
				exit = true;
			}
		}
	}

	return 0;
}

