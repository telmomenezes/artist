%module(directors="1") pycasso
%feature("director");

%include stl.i

%exception
{
        try
        {
                $action
        }
        catch (std::string e)
        {
                PyErr_SetString(PyExc_RuntimeError, e.getMessage().c_str());
                return NULL;
        }
}


%{
#include "src/Pycasso.h"
%}
%include "src/Pycasso.h"

