PROJECT(pycasso)

OPTION(SYSTEM_SDLOPENGL "SDLOpenGL Support" ON)
OPTION(DEBUG "Debug settings" OFF)

IF(DEBUG)
    SET(CMAKE_CXX_FLAGS "-Wno-deprecated -g")
ELSE(DEBUG)
    SET(CMAKE_CXX_FLAGS "-Wno-deprecated -O3")
ENDIF(DEBUG)

ADD_SUBDIRECTORY(src)

SET(SOURCE_FILES ${SOURCE_FILES}
    src/Pycasso.cpp
    src/Window.cpp
    src/Layer.cpp
    src/EventQ.cpp
    src/PycassoException.cpp)

SET(INCLUDE_DIRS include)

IF(SYSTEM_SDLOPENGL)
    INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)

    SET(SOURCE_FILES ${SOURCE_FILES}
        src/LayerOpenGL.cpp
        src/WindowSDLOpenGL.cpp
        src/EventQSDL.cpp)

    SET(DEFINITIONS ${DEFINITIONS} -D__PYCASSO_SYSTEM_SDLOPENGL)
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_INCLUDE_DIR})
    SET(PYCASSO_LINK_LIBRARIES ${PYCASSO_LINK_LIBRARIES} SDL GL GLU png)
ENDIF(SYSTEM_SDLOPENGL)

ADD_DEFINITIONS(${DEFINITIONS})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_LIBRARY(pycasso SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(pycasso ${PYCASSO_LINK_LIBRARIES})

INSTALL_TARGETS(/lib pycasso)

INSTALL_FILES(/include/pycasso FILES
                include/EventQ.h
                include/Layer.h
                include/Pycasso.h
                include/PycassoException.h
                include/Window.h
                include/pyc.h
                include/pyc_types.h)

ADD_EXECUTABLE(demo1 demos/demo1.cpp)
TARGET_LINK_LIBRARIES(demo1 pycasso)

ADD_EXECUTABLE(demo2 demos/demo2.cpp)
TARGET_LINK_LIBRARIES(demo2 pycasso)

ADD_EXECUTABLE(demo3 demos/demo3.cpp)
TARGET_LINK_LIBRARIES(demo3 pycasso)

