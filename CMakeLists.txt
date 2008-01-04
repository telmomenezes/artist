PROJECT(artist)

#SET(CMAKE_VERBOSE_MAKEFILE ON)

OPTION(SYSTEM_SDLOPENGL "SDLOpenGL Support" ON)
SET(SYSTEM_TYPE "SDLOpenGL" CACHE STRING "System type: [SDLOpenGL; Null]")
OPTION(DEBUG "Debug settings" OFF)

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

IF(WIN32)
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_OS_WIN32)
ENDIF(WIN32)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_OS_OSX)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

SET(INCLUDE_DIRS include)

IF(${SYSTEM_TYPE} MATCHES "SDLOpenGL")
    SET(SOURCE_FILES ${SOURCE_FILES}
        src/artist.c
        src/artist_sdlopengl.c
        src/layer.c
        src/layer_opengl.c
        src/eventq.c
        src/font.c
        src/font_opengL.c
        src/eventq_sdl.c
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

ADD_DEFINITIONS(${DEFINITIONS})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_LIBRARY(artist SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(artist ${ARTIST_LINK_LIBRARIES} ${EXTRA_LIBS})

INSTALL_TARGETS(/lib artist)

INSTALL_FILES(/include/artist FILES
                include/eventq.h
                include/layer.h
                include/artist.h
                include/font.h
                include/art.h
                include/artist_types.h)

ADD_EXECUTABLE(demo1 demos/demo1.c ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo1 artist)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(artist demo1 PROPERTIES LINK_FLAGS "-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

