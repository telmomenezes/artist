class Font
{

%TypeHeaderCode
#include "Font.h"
using namespace pyc;
%End

public:
    Font();
    virtual ~Font();

    unsigned int getHeight();
    virtual float getTextWidth(std::string text)=0;
};
