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

    virtual void update()=0;

    virtual void setTitle(std::string title)=0;


    int getWidth();
    int getHeight();
    Layer* getRootLayer();

    virtual void showCursor(bool show)=0;

    virtual Layer* createLayer(int width, int height)=0;
    virtual Layer* createPNGLayer(std::string filePath)=0;
    bool removeLayer(Layer* layer);

    virtual void setClearOnUpdate(bool clear);
};
