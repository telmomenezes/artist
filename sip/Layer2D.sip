class Layer2D : Layer
{

%TypeHeaderCode
#include "Layer2D.h"
using namespace pyc;
%End

public:
    Layer2D();
    virtual ~Layer2D();

    virtual void setRotation(float x, float y, float angle)=0;
    virtual void clearRotation()=0;

    virtual void setScale(float scaleX, float scaleY)=0;
    virtual void clearScale()=0;

    virtual void setTranslation(float transX, float transY)=0;
    virtual void clearTranslation()=0;

    virtual void setScreenTranslation(float transX, float transY)=0;
    virtual void clearScreenTranslation()=0;

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
                    float side)=0;

    virtual void drawRectangle(float x,
                    float y,
                    float width,
                    float height)=0;

    virtual void drawCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0,
                    float endAngle=6.28318531)=0;

    virtual void drawEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle=0.0,
                    float endAngle=6.28318531)=0;

    virtual void fillTriangle(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float x3,
                    float y3)=0;

    virtual void fillSquare(float x,
                    float y,
                    float side)=0;

    virtual void fillRectangle(float x,
                    float y,
                    float width,
                    float height)=0;

    virtual void fillCircle(float x,
                    float y,
                    float rad,
                    float beginAngle=0,
                    float endAngle=6.28318531)=0;

    virtual void fillEllipse(float x,
                    float y,
                    float radX,
                    float radY,
                    float beginAngle=0.0,
                    float endAngle=6.28318531)=0;

    virtual void drawLayer(Layer* layer,
                    float x=0,
                    float y=0,
                    float width=0,
                    float height=0)=0;

    void setFont(Font* font);

    virtual void drawText(float x, float y, std::string text)=0;
};
