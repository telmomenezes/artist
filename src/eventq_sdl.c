/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "eventq.h"
#include "SDL.h"

int _art_initEventQ()
{
    _art_initEventQData();
    return 0;
}

Art_KeyCode _art_getKeyCode(int key)
{
    switch(key)
    {
    case SDLK_BACKSPACE:
        return ART_KEY_BACKSPACE;
    case SDLK_TAB:
        return ART_KEY_TAB;
    case SDLK_CLEAR:
        return ART_KEY_CLEAR;
    case SDLK_RETURN:
        return ART_KEY_RETURN;
    case SDLK_PAUSE:
        return ART_KEY_PAUSE;
    case SDLK_ESCAPE:
        return ART_KEY_ESCAPE;
    case SDLK_SPACE:
        return ART_KEY_SPACE;
    case SDLK_EXCLAIM:
        return ART_KEY_BANG;
    case SDLK_QUOTEDBL:
        return ART_KEY_DOUBLEQUOTE;
    case SDLK_HASH:
        return ART_KEY_HASH;
    case SDLK_DOLLAR:
        return ART_KEY_DOLLAR;
    case SDLK_AMPERSAND:
        return ART_KEY_AMPERSAND;
    case SDLK_QUOTE:
        return ART_KEY_QUOTE;
    case SDLK_LEFTPAREN:
        return ART_KEY_LEFT_PARENTHESIS;
    case SDLK_RIGHTPAREN:
        return ART_KEY_RIGHT_PARENTHESIS;
    case SDLK_ASTERISK:
        return ART_KEY_ASTERISK;
    case SDLK_PLUS:
        return ART_KEY_PLUS;
    case SDLK_COMMA:
        return ART_KEY_COMMA;
    case SDLK_MINUS:
        return ART_KEY_MINUS;
    case SDLK_PERIOD:
        return ART_KEY_PERIOD;
    case SDLK_SLASH:
        return ART_KEY_SLASH;
    case SDLK_0:
        return ART_KEY_0;
    case SDLK_1:
        return ART_KEY_1;
    case SDLK_2:
        return ART_KEY_2;
    case SDLK_3:
        return ART_KEY_3;
    case SDLK_4:
        return ART_KEY_4;
    case SDLK_5:
        return ART_KEY_5;
    case SDLK_6:
        return ART_KEY_6;
    case SDLK_7:
        return ART_KEY_7;
    case SDLK_8:
        return ART_KEY_8;
    case SDLK_9:
        return ART_KEY_9;
    case SDLK_COLON:
        return ART_KEY_COLON;
    case SDLK_SEMICOLON:
        return ART_KEY_SEMICOLON;
    case SDLK_LESS:
        return ART_KEY_LESS;
    case SDLK_EQUALS:
        return ART_KEY_EQUALS;
    case SDLK_GREATER:
        return ART_KEY_GREATER;
    case SDLK_QUESTION:
        return ART_KEY_QUESTION_MARK;
    case SDLK_AT:
        return ART_KEY_AT;
    case SDLK_LEFTBRACKET:
        return ART_KEY_LEFT_BRACKET;
    case SDLK_BACKSLASH:
        return ART_KEY_BACKSLASH;
    case SDLK_RIGHTBRACKET:
        return ART_KEY_RIGHT_BRACKET;
    case SDLK_CARET:
        return ART_KEY_CARET;
    case SDLK_UNDERSCORE:
        return ART_KEY_UNDERSCORE;
    case SDLK_BACKQUOTE:
        return ART_KEY_BACKQUOTE;
    case SDLK_a:
        return ART_KEY_A;
    case SDLK_b:
        return ART_KEY_B;
    case SDLK_c:
        return ART_KEY_C;
    case SDLK_d:
        return ART_KEY_D;
    case SDLK_e:
        return ART_KEY_E;
    case SDLK_f:
        return ART_KEY_F;
    case SDLK_g:
        return ART_KEY_G;
    case SDLK_h:
        return ART_KEY_H;
    case SDLK_i:
        return ART_KEY_I;
    case SDLK_j:
        return ART_KEY_J;
    case SDLK_k:
        return ART_KEY_K;
    case SDLK_l:
        return ART_KEY_L;
    case SDLK_m:
        return ART_KEY_M;
    case SDLK_n:
        return ART_KEY_N;
    case SDLK_o:
        return ART_KEY_O;
    case SDLK_p:
        return ART_KEY_P;
    case SDLK_q:
        return ART_KEY_Q;
    case SDLK_r:
        return ART_KEY_R;
    case SDLK_s:
        return ART_KEY_S;
    case SDLK_t:
        return ART_KEY_T;
    case SDLK_u:
        return ART_KEY_U;
    case SDLK_v:
        return ART_KEY_V;
    case SDLK_w:
        return ART_KEY_W;
    case SDLK_x:
        return ART_KEY_X;
    case SDLK_y:
        return ART_KEY_Y;
    case SDLK_z:
        return ART_KEY_Z;
    case SDLK_DELETE:
        return ART_KEY_DELETE;
    case SDLK_KP0:
        return ART_KEY_PAD_0;
    case SDLK_KP1:
        return ART_KEY_PAD_1;
    case SDLK_KP2:
        return ART_KEY_PAD_2;
    case SDLK_KP3:
        return ART_KEY_PAD_3;
    case SDLK_KP4:
        return ART_KEY_PAD_4;
    case SDLK_KP5:
        return ART_KEY_PAD_5;
    case SDLK_KP6:
        return ART_KEY_PAD_6;
    case SDLK_KP7:
        return ART_KEY_PAD_7;
    case SDLK_KP8:
        return ART_KEY_PAD_8;
    case SDLK_KP9:
        return ART_KEY_PAD_9;
    case SDLK_KP_PERIOD:
        return ART_KEY_PAD_PERIOD;
    case SDLK_KP_DIVIDE:
        return ART_KEY_PAD_DIVIDE;
    case SDLK_KP_MULTIPLY:
        return ART_KEY_PAD_MULTIPLY;
    case SDLK_KP_MINUS:
        return ART_KEY_PAD_MINUS;
    case SDLK_KP_PLUS:
        return ART_KEY_PAD_PLUS;
    case SDLK_KP_ENTER:
        return ART_KEY_PAD_ENTER;
    case SDLK_KP_EQUALS:
        return ART_KEY_PAD_EQUALS;
    case SDLK_UP:
        return ART_KEY_UP;
    case SDLK_DOWN:
        return ART_KEY_DOWN;
    case SDLK_RIGHT:
        return ART_KEY_RIGHT;
    case SDLK_LEFT:
        return ART_KEY_LEFT;
    case SDLK_INSERT:
        return ART_KEY_INSERT;
    case SDLK_HOME:
        return ART_KEY_HOME;
    case SDLK_END:
        return ART_KEY_END;
    case SDLK_PAGEUP:
        return ART_KEY_PAGE_UP;
    case SDLK_PAGEDOWN:
        return ART_KEY_PAGE_DOWN;
    case SDLK_F1:
        return ART_KEY_F1;
    case SDLK_F2:
        return ART_KEY_F2;
    case SDLK_F3:
        return ART_KEY_F3;
    case SDLK_F4:
        return ART_KEY_F4;
    case SDLK_F5:
        return ART_KEY_F5;
    case SDLK_F6:
        return ART_KEY_F6;
    case SDLK_F7:
        return ART_KEY_F7;
    case SDLK_F8:
        return ART_KEY_F8;
    case SDLK_F9:
        return ART_KEY_F9;
    case SDLK_F10:
        return ART_KEY_F10;
    case SDLK_F11:
        return ART_KEY_F11;
    case SDLK_F12:
        return ART_KEY_F12;
    case SDLK_F13:
        return ART_KEY_F13;
    case SDLK_F14:
        return ART_KEY_F14;
    case SDLK_F15:
        return ART_KEY_F15;
    case SDLK_NUMLOCK:
        return ART_KEY_NUMLOCK;
    case SDLK_CAPSLOCK:
        return ART_KEY_CAPSLOCK;
    case SDLK_SCROLLOCK:
        return ART_KEY_SCROLLLOCK;
    case SDLK_RSHIFT:
        return ART_KEY_RIGHT_SHIFT;
    case SDLK_LSHIFT:
        return ART_KEY_LEFT_SHIFT;
    case SDLK_RCTRL:
        return ART_KEY_RIGHT_CONTROL;
    case SDLK_LCTRL:
        return ART_KEY_LEFT_CONTROL;
    case SDLK_RALT:
        return ART_KEY_RIGHT_ALT;
    case SDLK_LALT:
        return ART_KEY_LEFT_ALT;
    case SDLK_RMETA:
        return ART_KEY_RIGHT_META;
    case SDLK_LMETA:
        return ART_KEY_LEFT_META;
    case SDLK_LSUPER:
        return ART_KEY_LEFT_WINDOWS;
    case SDLK_RSUPER:
        return ART_KEY_RIGHT_WINDOWS;
    case SDLK_MODE:
        return ART_KEY_MODE;
    case SDLK_HELP:
        return ART_KEY_HELP;
    case SDLK_PRINT:
        return ART_KEY_PRINT;
    case SDLK_SYSREQ:
        return ART_KEY_SYSREQ;
    case SDLK_BREAK:
        return ART_KEY_BREAK;
    case SDLK_MENU:
        return ART_KEY_MENU;
    case SDLK_POWER:
        return ART_KEY_POWER;
    case SDLK_EURO:
        return ART_KEY_EURO;
    default:
        return ART_KEY_NULL;
    }
}

void _art_updateKeyModifiers(int modifiers)
{
    artG_eventData.ctrl = modifiers & KMOD_CTRL;
    artG_eventData.shift = modifiers & KMOD_SHIFT;
    artG_eventData.alt = modifiers & KMOD_ALT;
    artG_eventData.meta = modifiers & KMOD_META;
    artG_eventData.caps = modifiers & KMOD_CAPS;
    artG_eventData.num = modifiers & KMOD_NUM;
}

Art_MouseButton _art_getMouseButton(int button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return ART_BUTTON_LEFT;
    case SDL_BUTTON_MIDDLE:
        return ART_BUTTON_MIDDLE;
    case SDL_BUTTON_RIGHT:
        return ART_BUTTON_RIGHT;
    default:
        return ART_BUTTON_NULL;
    }
}

void art_enableKeyChar(int enable)
{
    if (enable)
    {
        SDL_EnableUNICODE(0);
    }
    else
    {
        SDL_EnableUNICODE(1);
    }
}

int art_nextEvent()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        _art_resetEventQValues();

        switch (event.type)
        {
            case SDL_KEYDOWN:
                artG_eventData.type = ART_EVENT_KEY_DOWN;
                artG_eventData.keyCode = _art_getKeyCode(event.key.keysym.sym);
                artG_eventData.keyChar = event.key.keysym.unicode;
                _art_updateKeyModifiers(event.key.keysym.mod);
                break;
            case SDL_KEYUP:
                artG_eventData.type = ART_EVENT_KEY_UP;
                artG_eventData.keyCode = _art_getKeyCode(event.key.keysym.sym);
                artG_eventData.keyChar = event.key.keysym.unicode;
                _art_updateKeyModifiers(event.key.keysym.mod);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button <= 3)
                {
                    artG_eventData.type = ART_EVENT_MOUSE_BUTTON_DOWN;
                    artG_eventData.mouseButton = _art_getMouseButton(event.button.button);
                    _art_updateMouseButton(artG_eventData.mouseButton, 1);
                }
                else
                {
                    if (event.button.button == 4)
                    {
                        artG_eventData.type = ART_EVENT_MOUSE_WHEEL_UP;
                    }
                    if (event.button.button == 5)
                    {
                        artG_eventData.type = ART_EVENT_MOUSE_WHEEL_DOWN;
                    }
                }
                artG_eventData.mousePosX = event.button.x;
                artG_eventData.mousePosY = event.button.y;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button <= 3)
                {
                    artG_eventData.type = ART_EVENT_MOUSE_BUTTON_UP;
                    artG_eventData.mouseButton = _art_getMouseButton(event.button.button);
                }
                else
                {
                    return 0;
                }
                artG_eventData.mousePosX = event.button.x;
                artG_eventData.mousePosY = event.button.y;
                _art_updateMouseButton(artG_eventData.mouseButton, 0);
                break;
            case SDL_MOUSEMOTION:
                artG_eventData.type = ART_EVENT_MOUSE_MOTION;
                artG_eventData.mousePosX = event.motion.x;
                artG_eventData.mousePosY = event.motion.y;
                artG_eventData.mouseRelX = event.motion.xrel;
                artG_eventData.mouseRelY = event.motion.yrel;
                break;
            case SDL_QUIT:
                artG_eventData.type = ART_EVENT_QUIT;
                break;
            case SDL_VIDEORESIZE:
                artG_eventData.type = ART_EVENT_RESIZE;
                artG_eventData.resizeWidth = event.resize.w;
                artG_eventData.resizeHeight = event.resize.h;
                break;
            default:
                break;
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

