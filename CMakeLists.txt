PROJECT(pycasso)

OPTION(SYSTEM_SDLOPENGL "SDLOpenGL Support" ON)
OPTION(DEBUG "Debug settings" OFF)

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    IF(DEBUG)
        SET(CMAKE_CXX_FLAGS "-Wno-deprecated -g")
    ELSE(DEBUG)
        SET(CMAKE_CXX_FLAGS "-Wno-deprecated -O3")
    ENDIF(DEBUG)
ENDIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

IF(WIN32)
    SET(DEFINITIONS ${DEFINITIONS} -D__PYCASSO_OS_WIN32)
ENDIF(WIN32)

SET(SOURCE_FILES ${SOURCE_FILES}
    src/Pycasso.cpp
    src/Window.cpp
    src/Layer.cpp
    src/Layer2D.cpp
    src/Font.cpp
    src/EventQ.cpp)

SET(INCLUDE_DIRS include)
SET(SDL_INCLUDE_DIR C:/projects/SDL-1.2.12/include)

IF(SYSTEM_SDLOPENGL)
    INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)

    SET(SOURCE_FILES ${SOURCE_FILES}
        src/Layer2DOpenGL.cpp
        src/FontOpenGL.cpp
        src/WindowSDLOpenGL.cpp
        src/EventQSDL.cpp)

    SET(DEFINITIONS ${DEFINITIONS} -D__PYCASSO_SYSTEM_SDLOPENGL)

    # TODO: Automate search for freetype2 stuff
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_INCLUDE_DIR} /usr/include/freetype2)

    IF (WIN32)
        SET(PYCASSO_LINK_LIBRARIES ${PYCASSO_LINK_LIBRARIES} freetype SDL opengl32 glu32 libpng)
    ELSE(WIN32)
        SET(PYCASSO_LINK_LIBRARIES ${PYCASSO_LINK_LIBRARIES} SDL GL GLU png freetype)
    ENDIF(WIN32)
ENDIF(SYSTEM_SDLOPENGL)

ADD_DEFINITIONS(${DEFINITIONS})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_LIBRARY(pycasso SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(pycasso ${PYCASSO_LINK_LIBRARIES})

INSTALL_TARGETS(/lib pycasso)

INSTALL_FILES(/include/pycasso FILES
                include/EventQ.h
                include/Layer.h
                include/Layer2D.h
                include/Pycasso.h
                include/Window.h
                include/pyc.h
                include/pyc_types.h)

ADD_EXECUTABLE(demo1 demos/demo1.cpp)
TARGET_LINK_LIBRARIES(demo1 pycasso)

ADD_EXECUTABLE(demo2 demos/demo2.cpp)
TARGET_LINK_LIBRARIES(demo2 pycasso)

ADD_EXECUTABLE(demo3 demos/demo3.cpp)
TARGET_LINK_LIBRARIES(demo3 pycasso)

ADD_EXECUTABLE(demo4 demos/demo4.cpp)
TARGET_LINK_LIBRARIES(demo4 pycasso)

ADD_EXECUTABLE(demo5 demos/demo5.cpp)
TARGET_LINK_LIBRARIES(demo5 pycasso)

ADD_EXECUTABLE(demo6 demos/demo6.cpp)
TARGET_LINK_LIBRARIES(demo6 pycasso)

ADD_EXECUTABLE(demo7 demos/demo7.cpp)
TARGET_LINK_LIBRARIES(demo7 pycasso)
