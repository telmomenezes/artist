%module(directors="1") pycasso
%feature("director");

%include stl.i

%{
#include "src/PycassoError.h"
%}

%exception
{
        try
        {
                $action
        }
        catch (PycassoError e)
        {
                PyErr_SetString(PyExc_RuntimeError, e.getmessage().c_str());
                return NULL;
        }
}


%{
#include "src/Session.h"
%}
%include "src/Session.h"

%{
#include "src/Stage.h"
%}
%include "src/Stage.h"

%{
#include "src/StageObject.h"
%}
%include "src/StageObject.h"
%{
#include "src/Object2D.h"
%}
%include "src/Object2D.h"

%{
#include "src/Object3D.h"
%}
%include "src/Object3D.h"

%{
#include "src/Shape3D.h"
%}
%include "src/Shape3D.h"

%{
#include "src/PhysicalObject.h"
%}
%include "src/PhysicalObject.h"

%{
#include "src/Light.h"
%}
%include "src/Light.h"

%{
#include "src/Mouse.h"
%}
%include "src/Mouse.h"

%{
#include "src/Keyboard.h"
%}
%include "src/Keyboard.h"

