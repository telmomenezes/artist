class Layer
{

%TypeHeaderCode
#include "Layer.h"
using namespace pyc;
%End

public:
    Layer();
    virtual ~Layer();

    int getWidth();
    int getHeight();

    virtual void setColor(unsigned int red,
                unsigned int green,
                unsigned int blue,
                unsigned int alpha)=0;
    virtual void setColor(unsigned int red,
                unsigned int green,
                unsigned int blue);
    virtual void setAlpha(unsigned int alpha);
    virtual void setColorRGBA(unsigned int color);
    virtual void setColorRGB(unsigned int color);
    virtual void setBackgroundColor(unsigned int red,
                    unsigned int green,
                    unsigned int blue)=0;
    virtual void setBackgroundColorRGB(unsigned int color);

    virtual void setPointSize(float size)=0;
    virtual void setLineWidth(float width)=0;

    void setCurveAngleStep(float angle);

    virtual void clear()=0;

    bool isRoot();
};
