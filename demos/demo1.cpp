#include "pyc.h"

int main(int argc, char *argv[])
{
	pyc::Pycasso pycasso;
	pyc::Canvas* screen = pycasso.createScreen(pyc::SDLOpenGL, 800, 600);

	if (screen == NULL)
	{
		return 1;
	}

	screen->setCaption("Pycasso Demo #1");

	screen->setBackgroundColor(1.0f, 1.0f, 1.0f);

	for (float x = 0.0f; x < 800.0f; x += 1.0f)
	{
		screen->beginFrame();
		screen->setColor(1.0f, 0.0f, 0.0f);
		screen->drawFilledCircle(x, 300.0f, 100.0f);
		screen->endFrame();
	}

	delete screen;

	return 0;
}

