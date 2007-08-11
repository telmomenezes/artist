PROJECT(pycasso)

INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR} include)
ADD_DEFINITIONS(-D__LAYER_SDLOPENGL)

IF(DEBUG)
	SET(CMAKE_CXX_FLAGS "-Wno-deprecated -g")
ELSE(DEBUG)
	SET(CMAKE_CXX_FLAGS "-Wno-deprecated -O3")
ENDIF(DEBUG)

ADD_SUBDIRECTORY(src)

SET(SOURCE_FILES ${SOURCE_FILES}
	src/Pycasso.cpp
	src/Canvas.cpp
	src/Image.cpp
	src/CanvasOpenGL.cpp
	src/ScreenSDLOpenGL.cpp
	src/ImageOpenGL.cpp)

ADD_LIBRARY(pycasso STATIC ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(pycasso SDL GL GLU png)

ADD_EXECUTABLE(demo1 demos/demo1.cpp)
TARGET_LINK_LIBRARIES(demo1 pycasso)
