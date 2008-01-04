/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_ARTIST_TYPES_H)
#define __INCLUDE_ARTIST_TYPES_H

typedef enum
{
    ART_SYSTEM_NULL,
    ART_SYSTEM_SDL_OPENGL
} System;

typedef enum
{
    ART_EVENT_NULL,
    ART_EVENT_KEY_UP,
    ART_EVENT_KEY_DOWN,
    ART_EVENT_MOUSE_BUTTON_UP,
    ART_EVENT_MOUSE_BUTTON_DOWN,
    ART_EVENT_MOUSE_MOTION,
    ART_EVENT_MOUSE_WHEEL_UP,
    ART_EVENT_MOUSE_WHEEL_DOWN,
    ART_EVENT_RESIZE,
    ART_EVENT_QUIT
} EventType;

typedef enum
{
    ART_KEY_NULL,
    ART_KEY_BACKSPACE,
    ART_KEY_TAB,
    ART_KEY_CLEAR,
    ART_KEY_RETURN,
    ART_KEY_PAUSE,
    ART_KEY_ESCAPE,
    ART_KEY_SPACE,
    ART_KEY_BANG,
    ART_KEY_DOUBLEQUOTE,
    ART_KEY_HASH,
    ART_KEY_DOLLAR,
    ART_KEY_AMPERSAND,
    ART_KEY_QUOTE,
    ART_KEY_LEFT_PARENTHESIS,
    ART_KEY_RIGHT_PARENTHESIS,
    ART_KEY_ASTERISK,
    ART_KEY_PLUS,
    ART_KEY_COMMA,
    ART_KEY_MINUS,
    ART_KEY_PERIOD,
    ART_KEY_SLASH,
    ART_KEY_0,
    ART_KEY_1,
    ART_KEY_2,
    ART_KEY_3,
    ART_KEY_4,
    ART_KEY_5,
    ART_KEY_6,
    ART_KEY_7,
    ART_KEY_8,
    ART_KEY_9,
    ART_KEY_COLON,
    ART_KEY_SEMICOLON,
    ART_KEY_LESS,
    ART_KEY_EQUALS,
    ART_KEY_GREATER,
    ART_KEY_QUESTION_MARK,
    ART_KEY_AT,
    ART_KEY_LEFT_BRACKET,
    ART_KEY_BACKSLASH,
    ART_KEY_RIGHT_BRACKET,
    ART_KEY_CARET,
    ART_KEY_UNDERSCORE,
    ART_KEY_BACKQUOTE,
    ART_KEY_A,
    ART_KEY_B,
    ART_KEY_C,
    ART_KEY_D,
    ART_KEY_E,
    ART_KEY_F,
    ART_KEY_G,
    ART_KEY_H,
    ART_KEY_I,
    ART_KEY_J,
    ART_KEY_K,
    ART_KEY_L,
    ART_KEY_M,
    ART_KEY_N,
    ART_KEY_O,
    ART_KEY_P,
    ART_KEY_Q,
    ART_KEY_R,
    ART_KEY_S,
    ART_KEY_T,
    ART_KEY_U,
    ART_KEY_V,
    ART_KEY_W,
    ART_KEY_X,
    ART_KEY_Y,
    ART_KEY_Z,
    ART_KEY_DELETE,
    ART_KEY_PAD_0,
    ART_KEY_PAD_1,
    ART_KEY_PAD_2,
    ART_KEY_PAD_3,
    ART_KEY_PAD_4,
    ART_KEY_PAD_5,
    ART_KEY_PAD_6,
    ART_KEY_PAD_7,
    ART_KEY_PAD_8,
    ART_KEY_PAD_9,
    ART_KEY_PAD_PERIOD,
    ART_KEY_PAD_DIVIDE,
    ART_KEY_PAD_MULTIPLY,
    ART_KEY_PAD_MINUS,
    ART_KEY_PAD_PLUS,
    ART_KEY_PAD_ENTER,
    ART_KEY_PAD_EQUALS,
    ART_KEY_UP,
    ART_KEY_DOWN,
    ART_KEY_RIGHT,
    ART_KEY_LEFT,
    ART_KEY_INSERT,
    ART_KEY_HOME,
    ART_KEY_END,
    ART_KEY_PAGE_UP,
    ART_KEY_PAGE_DOWN,
    ART_KEY_F1,
    ART_KEY_F2,
    ART_KEY_F3,
    ART_KEY_F4,
    ART_KEY_F5,
    ART_KEY_F6,
    ART_KEY_F7,
    ART_KEY_F8,
    ART_KEY_F9,
    ART_KEY_F10,
    ART_KEY_F11,
    ART_KEY_F12,
    ART_KEY_F13,
    ART_KEY_F14,
    ART_KEY_F15,
    ART_KEY_NUMLOCK,
    ART_KEY_CAPSLOCK,
    ART_KEY_SCROLLLOCK,
    ART_KEY_RIGHT_SHIFT,
    ART_KEY_LEFT_SHIFT,
    ART_KEY_RIGHT_CONTROL,
    ART_KEY_LEFT_CONTROL,
    ART_KEY_RIGHT_ALT,
    ART_KEY_LEFT_ALT,
    ART_KEY_RIGHT_META,
    ART_KEY_LEFT_META,
    ART_KEY_LEFT_WINDOWS,
    ART_KEY_RIGHT_WINDOWS,
    ART_KEY_MODE,
    ART_KEY_HELP,
    ART_KEY_PRINT,
    ART_KEY_SYSREQ,
    ART_KEY_BREAK,
    ART_KEY_MENU,
    ART_KEY_POWER,
    ART_KEY_EURO
} KeyCode;

typedef enum
{
    ART_BUTTON_NULL,
    ART_BUTTON_LEFT,
    ART_BUTTON_MIDDLE,
    ART_BUTTON_RIGHT
} MouseButton;

#endif

