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

    virtual void clear()=0;

    virtual void drawPoint(float x, float y)=0;
    virtual void drawLine(float x1, float y1, float x2, float y2)=0;
    virtual void drawTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)=0;
    virtual void drawSquare(float x,
                    float y,
                    float rad,
                    float rot=0)=0;
    virtual void drawCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0,
                    float endAngle=6.28318531)=0;
    virtual void fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)=0;
    virtual void fillSquare(float x,
                    float y,
                    float rad,
                    float rot=0)=0;
    virtual void fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0,
                    float endAngle=6.28318531)=0;

    virtual void drawLayer(Layer* layer,
                    float x=0,
                    float y=0,
                    float width=0,
                    float height=0)=0;

    bool isRoot();
};
