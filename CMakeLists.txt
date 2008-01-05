########### Project name ###########

PROJECT(artist)
SET(ARTIST_MAJOR "0")
SET(ARTIST_MINOR "4")
SET(VERSION "${ARTIST_MAJOR}.${ARTIST_MINOR}")
SET(PACKAGE artist)


########### Global settings ###########

SET(CMAKE_VERBOSE_MAKEFILE OFF)

OPTION(DEBUG "Debug settings" OFF)
OPTION(SYSTEM_SDLOPENGL "SDLOpenGL Support" ON)
SET(SYSTEM_TYPE "SDLOpenGL" CACHE STRING "System type: [SDLOpenGL; Null]")


########### Compiler settings ###########

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    IF(DEBUG)
        SET(CMAKE_CXX_FLAGS "-Wno-deprecated -g")
    ELSE(DEBUG)
        SET(CMAKE_CXX_FLAGS "-Wno-deprecated -O3")
    ENDIF(DEBUG)
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_COMPILER_GCC)
ENDIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

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
        src/font_opengL.c
        src/stb_image.c
        src/functions.c)

    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_SYSTEM_SDLOPENGL)

    INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)
    INCLUDE(CMakeModules/FindFreeType.cmake)
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR_freetype2})
    SET(ARTIST_LINK_LIBRARIES ${FREETYPE_LIBRARY})

    IF (WIN32)
        SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} ${SDL_LIBRARY} opengl32 glu32)
    ELSE(WIN32)
        IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            SET(DEFINITIONS ${DEFINITIONS} -D_OSX_SDL_)
            SET(EXTRA_SRC_FILES ${EXTRA_SRC_FILES}
                src/MacOSXSDL/SDLMain.m)
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

######################
# A bug in Mac OS X Leopard forces us to use this workaround for now
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(artist demo1 demo2 PROPERTIES LINK_FLAGS "-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
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

