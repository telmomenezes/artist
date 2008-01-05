/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "eventq.h"
#include "artist.h"

void _art_initEventQData()
{
    artG_session.eventData.ctrl = 0;
    artG_session.eventData.shift = 0;
    artG_session.eventData.alt = 0;
    artG_session.eventData.meta = 0;
    artG_session.eventData.caps = 0;
    artG_session.eventData.num = 0;
    artG_session.eventData.mousePosX = 0;
    artG_session.eventData.mousePosY = 0;
    artG_session.eventData.leftButton = 0;
    artG_session.eventData.middleButton = 0;
    artG_session.eventData.rightButton = 0;

    _art_resetEventQValues();
}

void _art_resetEventQValues()
{
    artG_session.eventData.type = ART_EVENT_NULL;
    artG_session.eventData.keyCode = ART_KEY_NULL;
    artG_session.eventData.keyChar = 0;
    artG_session.eventData.mouseButton = ART_BUTTON_NULL;
    artG_session.eventData.mouseRelX = 0;
    artG_session.eventData.mouseRelY = 0;
    artG_session.eventData.resizeWidth = 0;
    artG_session.eventData.resizeHeight = 0;
}

void _art_updateMouseButton(Art_MouseButton button, int val)
{
    switch (button)
    {
    case ART_BUTTON_LEFT:
        artG_session.eventData.leftButton = val;
        break;
    case ART_BUTTON_MIDDLE:
        artG_session.eventData.middleButton = val;
        break;
    case ART_BUTTON_RIGHT:
        artG_session.eventData.rightButton = val;
        break;
    }
}

Art_EventType art_getEventType()
{
    return artG_session.eventData.type;
}

Art_KeyCode art_getKeyCode()
{
    return artG_session.eventData.keyCode;
}

unsigned int art_getKeyChar()
{
    return artG_session.eventData.keyChar;
}

Art_MouseButton art_getMouseButton()
{
    return artG_session.eventData.mouseButton;
}

int art_getMousePosX()
{
    return artG_session.eventData.mousePosX;
}

int art_getMousePosY()
{
    return artG_session.eventData.mousePosY;
}

int art_getMouseRelX()
{
    return artG_session.eventData.mouseRelX;
}

int art_getMouseRelY()
{
    return artG_session.eventData.mouseRelY;
}

int art_getLeftButton()
{
    return artG_session.eventData.leftButton;
}

int art_getMiddleButton()
{
    return artG_session.eventData.middleButton;
}

int art_getRightButton()
{
    return artG_session.eventData.rightButton;
}

int art_getCtrl()
{
    return artG_session.eventData.ctrl;
}

int art_getShift()
{
    return artG_session.eventData.shift;
}

int art_getAlt()
{
    return artG_session.eventData.alt;
}

int art_getMeta()
{
    return artG_session.eventData.meta;
}

int art_getCaps()
{
    return artG_session.eventData.caps;
}

int art_getNum()
{
    return artG_session.eventData.num;
}

