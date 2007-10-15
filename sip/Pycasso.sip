class Pycasso
{

%TypeHeaderCode
#include "Pycasso.h"
using namespace pyc;
%End

public:
    Pycasso();
    virtual ~Pycasso();

    Window* createWindow(int width,
                int height,
                bool fullScreen=false,
                int colorDepth=0,
                bool resizable=false,
                bool windowDecorations=true);
    Window* getWindow();

    EventQ* createEventQ();
    EventQ* getEventQ();

    bool setPreferredSystem(System sys);

    double getTime();
};

