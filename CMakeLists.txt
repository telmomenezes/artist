########### Project name ###########

PROJECT(artist)
SET(ARTIST_MAJOR "0")
SET(ARTIST_MINOR "5")
SET(VERSION "${ARTIST_MAJOR}.${ARTIST_MINOR}")
SET(PACKAGE artist)


########### Global settings ###########

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

OPTION(DEBUG "Debug settings" OFF)
OPTION(SYSTEM_SDLOPENGL "SDLOpenGL Support" ON)
SET(SYSTEM_TYPE "SDLOpenGL" CACHE STRING "System type: [SDLOpenGL; Null]")

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

########### Compiler settings ###########

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    IF(DEBUG)
        SET(CMAKE_CXX_FLAGS "-g")
    ELSE(DEBUG)
        SET(CMAKE_CXX_FLAGS "-O3")
    ENDIF(DEBUG)
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_COMPILER_GCC)
ENDIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))

IF(CMAKE_C_COMPILER MATCHES cl)
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_COMPILER_CL)
ENDIF(CMAKE_C_COMPILER MATCHES cl)


########### System defines ###########

IF(WIN32)
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_OS_WIN32)
ENDIF(WIN32)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_OS_OSX)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


########### Include dirs ###########

SET(INCLUDE_DIRS include)


########### SDL OpenGL System ###########

IF(${SYSTEM_TYPE} MATCHES "SDLOpenGL")
    SET(SOURCE_FILES ${SOURCE_FILES}
        src/artist.c
        src/artist_sdlopengl.c
        src/eventq.c
        src/eventq_sdl.c
        src/layer.c
        src/layer_opengl.c
        src/font.c
        src/font_opengl.c
        src/stb_image.c
        src/functions.c)

    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_SYSTEM_SDLOPENGL)

    INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)
    find_package(Freetype REQUIRED)
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
    SET(ARTIST_LINK_LIBRARIES ${FREETYPE_LIBRARY})

    IF (WIN32)
        SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} ${SDL_LIBRARY} opengl32 glu32)
    ELSE(WIN32)
        IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            SET(DEFINITIONS ${DEFINITIONS} -D_OSX_SDL_)
            SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} ${SDL_LIBRARY})
            FIND_LIBRARY(COCOA_LIBRARY Cocoa)
            FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
            MARK_AS_ADVANCED(COCOA_LIBRARY)
            MARK_AS_ADVANCED(OPENGL_LIBRARY)
            SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OPENGL_LIBRARY})
        ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} ${SDL_LIBRARY} GL GLU)
        ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ENDIF(WIN32)
ENDIF(${SYSTEM_TYPE} MATCHES "SDLOpenGL")


########### Null System ###########

IF(${SYSTEM_TYPE} MATCHES "Null")
    SET(SOURCE_FILES ${SOURCE_FILES}
        src/artist.c
        src/artist_null.c
        src/eventq.c
        src/eventq_null.c
        src/layer.c
        src/layer_null.c
        src/font.c
        src/font_null.c)

    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_SYSTEM_NULL)

ENDIF(${SYSTEM_TYPE} MATCHES "Null")


########### Targets ###########

ADD_DEFINITIONS(${DEFINITIONS})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_LIBRARY(artist SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(artist ${ARTIST_LINK_LIBRARIES} ${EXTRA_LIBS})

ADD_EXECUTABLE(demo1 demos/demo1.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo1 artist)
ADD_EXECUTABLE(demo2 demos/demo2.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo2 artist)
ADD_EXECUTABLE(demo3 demos/demo3.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo3 artist)
ADD_EXECUTABLE(demo4 demos/demo4.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo4 artist)
ADD_EXECUTABLE(demo5 demos/demo5.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo5 artist)
ADD_EXECUTABLE(demo6 demos/demo6.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo6 artist)
ADD_EXECUTABLE(demo7 demos/demo7.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo7 artist)
ADD_EXECUTABLE(demo8 demos/demo8.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo8 artist)
ADD_EXECUTABLE(demo9 demos/demo9.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo9 artist)
ADD_EXECUTABLE(demo10 demos/demo10.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo10 artist)


######################
# A bug in Mac OS X Leopard forces us to use this workaround for now
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(artist demo1 demo2 demo3 demo4 demo5 demo6 demo7 demo8 demo9 demo10 PROPERTIES LINK_FLAGS "-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


########### Installation ###########

INSTALL_TARGETS(/lib artist)

INSTALL_FILES(/include/artist FILES
                include/eventq.h
                include/layer.h
                include/artist.h
                include/font.h
                include/art.h
                include/artist_types.h)

