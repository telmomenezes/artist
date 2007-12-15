/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "EventQSDL.h"
#include "SDL.h"

namespace art
{

EventQSDL::EventQSDL()
{
}

EventQSDL::~EventQSDL()
{
}

bool EventQSDL::init()
{
    return true;
}

void EventQSDL::enableKeyChar(bool enable)
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

bool EventQSDL::next()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        resetValues();

        switch (event.type)
        {
            case SDL_KEYDOWN:
                mType = EVENT_KEY_DOWN;
                mKeyCode = getKeyCode(event.key.keysym.sym);
                mKeyChar = event.key.keysym.unicode;
                updateKeyModifiers(event.key.keysym.mod);
                break;
            case SDL_KEYUP:
                mType = EVENT_KEY_UP;
                mKeyCode = getKeyCode(event.key.keysym.sym);
                mKeyChar = event.key.keysym.unicode;
                updateKeyModifiers(event.key.keysym.mod);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button <= 3)
                {
                    mType = EVENT_MOUSE_BUTTON_DOWN;
                    mMouseButton = getMouseButton(event.button.button);
                    updateMouseButton(mMouseButton, true);
                }
                else
                {
                    if (event.button.button == 4)
                    {
                        mType = EVENT_MOUSE_WHEEL_UP;
                    }
                    if (event.button.button == 5)
                    {
                        mType = EVENT_MOUSE_WHEEL_DOWN;
                    }
                }
                mMousePosX = event.button.x;
                mMousePosY = event.button.y;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button <= 3)
                {
                    mType = EVENT_MOUSE_BUTTON_UP;
                    mMouseButton = getMouseButton(event.button.button);
                }
                else
                {
                    return false;
                }
                mMousePosX = event.button.x;
                mMousePosY = event.button.y;
                updateMouseButton(mMouseButton, false);
                break;
            case SDL_MOUSEMOTION:
                mType = EVENT_MOUSE_MOTION;
                mMousePosX = event.motion.x;
                mMousePosY = event.motion.y;
                mMouseRelX = event.motion.xrel;
                mMouseRelY = event.motion.yrel;
                break;
            case SDL_QUIT:
                mType = EVENT_QUIT;
                break;
            case SDL_VIDEORESIZE:
                mType = EVENT_RESIZE;
                mResizeWidth = event.resize.w;
                mResizeHeight = event.resize.h;
                break;
            default:
                break;
        }

        return true;
    }
    else
    {
        return false;
    }
}

KeyCode EventQSDL::getKeyCode(int key)
{
    switch(key)
    {
    case SDLK_BACKSPACE:
        return KEY_BACKSPACE;
    case SDLK_TAB:
        return KEY_TAB;
    case SDLK_CLEAR:
        return KEY_CLEAR;
    case SDLK_RETURN:
        return KEY_RETURN;
    case SDLK_PAUSE:
        return KEY_PAUSE;
    case SDLK_ESCAPE:
        return KEY_ESCAPE;
    case SDLK_SPACE:
        return KEY_SPACE;
    case SDLK_EXCLAIM:
        return KEY_BANG;
    case SDLK_QUOTEDBL:
        return KEY_DOUBLEQUOTE;
    case SDLK_HASH:
        return KEY_HASH;
    case SDLK_DOLLAR:
        return KEY_DOLLAR;
    case SDLK_AMPERSAND:
        return KEY_AMPERSAND;
    case SDLK_QUOTE:
        return KEY_QUOTE;
    case SDLK_LEFTPAREN:
        return KEY_LEFT_PARENTHESIS;
    case SDLK_RIGHTPAREN:
        return KEY_RIGHT_PARENTHESIS;
    case SDLK_ASTERISK:
        return KEY_ASTERISK;
    case SDLK_PLUS:
        return KEY_PLUS;
    case SDLK_COMMA:
        return KEY_COMMA;
    case SDLK_MINUS:
        return KEY_MINUS;
    case SDLK_PERIOD:
        return KEY_PERIOD;
    case SDLK_SLASH:
        return KEY_SLASH;
    case SDLK_0:
        return KEY_0;
    case SDLK_1:
        return KEY_1;
    case SDLK_2:
        return KEY_2;
    case SDLK_3:
        return KEY_3;
    case SDLK_4:
        return KEY_4;
    case SDLK_5:
        return KEY_5;
    case SDLK_6:
        return KEY_6;
    case SDLK_7:
        return KEY_7;
    case SDLK_8:
        return KEY_8;
    case SDLK_9:
        return KEY_9;
    case SDLK_COLON:
        return KEY_COLON;
    case SDLK_SEMICOLON:
        return KEY_SEMICOLON;
    case SDLK_LESS:
        return KEY_LESS;
    case SDLK_EQUALS:
        return KEY_EQUALS;
    case SDLK_GREATER:
        return KEY_GREATER;
    case SDLK_QUESTION:
        return KEY_QUESTION_MARK;
    case SDLK_AT:
        return KEY_AT;
    case SDLK_LEFTBRACKET:
        return KEY_LEFT_BRACKET;
    case SDLK_BACKSLASH:
        return KEY_BACKSLASH;
    case SDLK_RIGHTBRACKET:
        return KEY_RIGHT_BRACKET;
    case SDLK_CARET:
        return KEY_CARET;
    case SDLK_UNDERSCORE:
        return KEY_UNDERSCORE;
    case SDLK_BACKQUOTE:
        return KEY_BACKQUOTE;
    case SDLK_a:
        return KEY_A;
    case SDLK_b:
        return KEY_B;
    case SDLK_c:
        return KEY_C;
    case SDLK_d:
        return KEY_D;
    case SDLK_e:
        return KEY_E;
    case SDLK_f:
        return KEY_F;
    case SDLK_g:
        return KEY_G;
    case SDLK_h:
        return KEY_H;
    case SDLK_i:
        return KEY_I;
    case SDLK_j:
        return KEY_J;
    case SDLK_k:
        return KEY_K;
    case SDLK_l:
        return KEY_L;
    case SDLK_m:
        return KEY_M;
    case SDLK_n:
        return KEY_N;
    case SDLK_o:
        return KEY_O;
    case SDLK_p:
        return KEY_P;
    case SDLK_q:
        return KEY_Q;
    case SDLK_r:
        return KEY_R;
    case SDLK_s:
        return KEY_S;
    case SDLK_t:
        return KEY_T;
    case SDLK_u:
        return KEY_U;
    case SDLK_v:
        return KEY_V;
    case SDLK_w:
        return KEY_W;
    case SDLK_x:
        return KEY_X;
    case SDLK_y:
        return KEY_Y;
    case SDLK_z:
        return KEY_Z;
    case SDLK_DELETE:
        return KEY_DELETE;
    case SDLK_KP0:
        return KEY_PAD_0;
    case SDLK_KP1:
        return KEY_PAD_1;
    case SDLK_KP2:
        return KEY_PAD_2;
    case SDLK_KP3:
        return KEY_PAD_3;
    case SDLK_KP4:
        return KEY_PAD_4;
    case SDLK_KP5:
        return KEY_PAD_5;
    case SDLK_KP6:
        return KEY_PAD_6;
    case SDLK_KP7:
        return KEY_PAD_7;
    case SDLK_KP8:
        return KEY_PAD_8;
    case SDLK_KP9:
        return KEY_PAD_9;
    case SDLK_KP_PERIOD:
        return KEY_PAD_PERIOD;
    case SDLK_KP_DIVIDE:
        return KEY_PAD_DIVIDE;
    case SDLK_KP_MULTIPLY:
        return KEY_PAD_MULTIPLY;
    case SDLK_KP_MINUS:
        return KEY_PAD_MINUS;
    case SDLK_KP_PLUS:
        return KEY_PAD_PLUS;
    case SDLK_KP_ENTER:
        return KEY_PAD_ENTER;
    case SDLK_KP_EQUALS:
        return KEY_PAD_EQUALS;
    case SDLK_UP:
        return KEY_UP;
    case SDLK_DOWN:
        return KEY_DOWN;
    case SDLK_RIGHT:
        return KEY_RIGHT;
    case SDLK_LEFT:
        return KEY_LEFT;
    case SDLK_INSERT:
        return KEY_INSERT;
    case SDLK_HOME:
        return KEY_HOME;
    case SDLK_END:
        return KEY_END;
    case SDLK_PAGEUP:
        return KEY_PAGE_UP;
    case SDLK_PAGEDOWN:
        return KEY_PAGE_DOWN;
    case SDLK_F1:
        return KEY_F1;
    case SDLK_F2:
        return KEY_F2;
    case SDLK_F3:
        return KEY_F3;
    case SDLK_F4:
        return KEY_F4;
    case SDLK_F5:
        return KEY_F5;
    case SDLK_F6:
        return KEY_F6;
    case SDLK_F7:
        return KEY_F7;
    case SDLK_F8:
        return KEY_F8;
    case SDLK_F9:
        return KEY_F9;
    case SDLK_F10:
        return KEY_F10;
    case SDLK_F11:
        return KEY_F11;
    case SDLK_F12:
        return KEY_F12;
    case SDLK_F13:
        return KEY_F13;
    case SDLK_F14:
        return KEY_F14;
    case SDLK_F15:
        return KEY_F15;
    case SDLK_NUMLOCK:
        return KEY_NUMLOCK;
    case SDLK_CAPSLOCK:
        return KEY_CAPSLOCK;
    case SDLK_SCROLLOCK:
        return KEY_SCROLLLOCK;
    case SDLK_RSHIFT:
        return KEY_RIGHT_SHIFT;
    case SDLK_LSHIFT:
        return KEY_LEFT_SHIFT;
    case SDLK_RCTRL:
        return KEY_RIGHT_CONTROL;
    case SDLK_LCTRL:
        return KEY_LEFT_CONTROL;
    case SDLK_RALT:
        return KEY_RIGHT_ALT;
    case SDLK_LALT:
        return KEY_LEFT_ALT;
    case SDLK_RMETA:
        return KEY_RIGHT_META;
    case SDLK_LMETA:
        return KEY_LEFT_META;
    case SDLK_LSUPER:
        return KEY_LEFT_WINDOWS;
    case SDLK_RSUPER:
        return KEY_RIGHT_WINDOWS;
    case SDLK_MODE:
        return KEY_MODE;
    case SDLK_HELP:
        return KEY_HELP;
    case SDLK_PRINT:
        return KEY_PRINT;
    case SDLK_SYSREQ:
        return KEY_SYSREQ;
    case SDLK_BREAK:
        return KEY_BREAK;
    case SDLK_MENU:
        return KEY_MENU;
    case SDLK_POWER:
        return KEY_POWER;
    case SDLK_EURO:
        return KEY_EURO;
    default:
        return KEY_NULL;
    }
}

void EventQSDL::updateKeyModifiers(int modifiers)
{
    mCtrl = modifiers & KMOD_CTRL;
    mShift = modifiers & KMOD_SHIFT;
    mAlt = modifiers & KMOD_ALT;
    mMeta = modifiers & KMOD_META;
    mCaps = modifiers & KMOD_CAPS;
    mNum = modifiers & KMOD_NUM;
}

MouseButton EventQSDL::getMouseButton(int button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT:
        return BUTTON_LEFT;
    case SDL_BUTTON_MIDDLE:
        return BUTTON_MIDDLE;
    case SDL_BUTTON_RIGHT:
        return BUTTON_RIGHT;
    default:
        return BUTTON_NULL;
    }
}

}

