#include "pyc.h"
#include <string>

int main(int argc, char *argv[])
{
	pyc::Pycasso pycasso;
	pyc::Canvas* screen = NULL;

	try
	{
		screen = pycasso.createScreen(800, 600);
	}
	catch(std::string exception)
	{
		printf("%s", exception.c_str());
		return 1;
	}

	if (screen == NULL)
	{
		return 1;
	}

	screen->setCaption("Pycasso Demo #1");

	screen->setBackgroundColor(1.0f, 1.0f, 1.0f);

	for (float x = 0.0f; x < 800.0f; x += 1.0f)
	{
		screen->beginFrame();
		screen->setColor(0.0f, 1.0f, 0.0f);
		screen->drawFilledCircle(x, 250.0f, 100.0f);
		screen->setColor(1.0f, 0.0f, 0.0f);
		screen->drawFilledCircle(x, 300.0f, 100.0f);
		screen->endFrame();
	}

	return 0;
}

