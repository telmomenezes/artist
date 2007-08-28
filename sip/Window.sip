class Window
{

%TypeHeaderCode
#include "Window.h"
using namespace pyc;
%End

public:
	Window();
	virtual ~Window();

	virtual void init(int width,
        		        int height,
				bool fullScreen=false,
		                int colorDepth=0,
				bool resizable=false,
				bool windowDecorations=true);

	virtual void update();

	virtual void setTitle(std::string title);


	int getWidth();
	int getHeight();
	Layer* getRootLayer();

	virtual void showCursor(bool show);

	virtual Layer* createLayer(int width, int height);
	virtual Layer* createPNGLayer(std::string filePath);
	bool removeLayer(Layer* layer);

	virtual void setClearOnUpdate(bool clear);
};
