/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_TYPES_H)
#define __INCLUDE_PYCASSO_TYPES_H

namespace pyc
{

enum System
{
    SYSTEM_NULL,
    SYSTEM_SDL_OPENGL
};

enum EventType
{
    EVENT_NULL,
    EVENT_KEY_UP,
    EVENT_KEY_DOWN,
    EVENT_MOUSE_BUTTON_UP,
    EVENT_MOUSE_BUTTON_DOWN,
    EVENT_MOUSE_MOTION,
    EVENT_MOUSE_WHEEL_UP,
    EVENT_MOUSE_WHEEL_DOWN,
    EVENT_RESIZE,
    EVENT_QUIT
};

enum KeyCode
{
    KEY_NULL,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_CLEAR,
    KEY_RETURN,
    KEY_PAUSE,
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_BANG,
    KEY_DOUBLEQUOTE,
    KEY_HASH,
    KEY_DOLLAR,
    KEY_AMPERSAND,
    KEY_QUOTE,
    KEY_LEFT_PARENTHESIS,
    KEY_RIGHT_PARENTHESIS,
    KEY_ASTERISK,
    KEY_PLUS,
    KEY_COMMA,
    KEY_MINUS,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_COLON,
    KEY_SEMICOLON,
    KEY_LESS,
    KEY_EQUALS,
    KEY_GREATER,
    KEY_QUESTION_MARK,
    KEY_AT,
    KEY_LEFT_BRACKET,
    KEY_BACKSLASH,
    KEY_RIGHT_BRACKET,
    KEY_CARET,
    KEY_UNDERSCORE,
    KEY_BACKQUOTE,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_DELETE,
    KEY_PAD_0,
    KEY_PAD_1,
    KEY_PAD_2,
    KEY_PAD_3,
    KEY_PAD_4,
    KEY_PAD_5,
    KEY_PAD_6,
    KEY_PAD_7,
    KEY_PAD_8,
    KEY_PAD_9,
    KEY_PAD_PERIOD,
    KEY_PAD_DIVIDE,
    KEY_PAD_MULTIPLY,
    KEY_PAD_MINUS,
    KEY_PAD_PLUS,
    KEY_PAD_ENTER,
    KEY_PAD_EQUALS,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_INSERT,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_NUMLOCK,
    KEY_CAPSLOCK,
    KEY_SCROLLLOCK,
    KEY_RIGHT_SHIFT,
    KEY_LEFT_SHIFT,
    KEY_RIGHT_CONTROL,
    KEY_LEFT_CONTROL,
    KEY_RIGHT_ALT,
    KEY_LEFT_ALT,
    KEY_RIGHT_META,
    KEY_LEFT_META,
    KEY_LEFT_WINDOWS,
    KEY_RIGHT_WINDOWS,
    KEY_MODE,
    KEY_HELP,
    KEY_PRINT,
    KEY_SYSREQ,
    KEY_BREAK,
    KEY_MENU,
    KEY_POWER,
    KEY_EURO
};

enum MouseButton
{
    BUTTON_NULL,
    BUTTON_LEFT,
    BUTTON_MIDDLE,
    BUTTON_RIGHT
};

enum ExceptionCode
{
    EXCEPTION_UNDEFINED = 0,
    EXCEPTION_INITIALIZATION = 1,
    EXCEPTION_MISSING_OBJECT = 2,
    EXCEPTION_OBJECT_EXISTS = 3,
    EXCEPTION_MEMORY = 4,
    EXCEPTION_FILE = 5
};

}

#endif

