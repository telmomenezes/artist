PROJECT(artist)

#SET(CMAKE_VERBOSE_MAKEFILE ON)

OPTION(SYSTEM_SDLOPENGL "SDLOpenGL Support" ON)
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

SET(SOURCE_FILES ${SOURCE_FILES}
    src/Artist.cpp
    src/Window.cpp
    src/Layer.cpp
    src/Layer2D.cpp
    src/Font.cpp
    src/EventQ.cpp)

# SYSTEM_NULL source files
SET(SOURCE_FILES ${SOURCE_FILES}
    src/WindowNull.cpp
    src/Layer2DNull.cpp
    src/FontNull.cpp
    src/EventQNull.cpp)

SET(INCLUDE_DIRS include)

IF(SYSTEM_SDLOPENGL)
    INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)

    SET(SOURCE_FILES ${SOURCE_FILES}
        src/Layer2DOpenGL.cpp
        src/FontOpenGL.cpp
        src/WindowSDLOpenGL.cpp
        src/EventQSDL.cpp
        src/stb_image.c
        )

    SET(DEFINITIONS ${DEFINITIONS} -D__ARTIST_SYSTEM_SDLOPENGL)

    INCLUDE(CMakeModules/FindFreeType.cmake)

    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${SDL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR_freetype2})
    SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} ${FREETYPE_LIBRARY})

    IF (WIN32)
        SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} SDL opengl32 glu32)
    ELSE(WIN32)
        IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} ${SDL_LIBRARY})
            FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
            MARK_AS_ADVANCED(OPENGL_LIBRARY)
            SET(EXTRA_LIBS ${OPENGL_LIBRARY})
        ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            SET(ARTIST_LINK_LIBRARIES ${ARTIST_LINK_LIBRARIES} SDL GL GLU)
        ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ENDIF(WIN32)
ENDIF(SYSTEM_SDLOPENGL)

ADD_DEFINITIONS(${DEFINITIONS})

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_LIBRARY(artist SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(artist ${ARTIST_LINK_LIBRARIES} ${EXTRA_LIBS})

INSTALL_TARGETS(/lib artist)

INSTALL_FILES(/include/artist FILES
                include/EventQ.h
                include/Layer.h
                include/Layer2D.h
                include/Artist.h
                include/Window.h include/Font.h
                include/art.h
                include/artist_types.h)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(EXTRA_SRC_FILES ${EXTRA_SRC_FILES} src/MacOSXSDL/SDLMain.m)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

ADD_EXECUTABLE(demo1 demos/demo1.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo1 artist)

ADD_EXECUTABLE(demo2 demos/demo2.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo2 artist)

ADD_EXECUTABLE(demo3 demos/demo3.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo3 artist)

ADD_EXECUTABLE(demo4 demos/demo4.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo4 artist)

ADD_EXECUTABLE(demo5 demos/demo5.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo5 artist)

ADD_EXECUTABLE(demo6 demos/demo6.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo6 artist)

ADD_EXECUTABLE(demo7 demos/demo7.cpp ${EXTRA_SRC_FILES})
TARGET_LINK_LIBRARIES(demo7 artist)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(artist demo1 demo2 demo3 demo4 demo5 demo6 demo7 PROPERTIES LINK_FLAGS "-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
