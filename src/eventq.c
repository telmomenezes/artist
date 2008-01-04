/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "eventq.h"

void _art_initEventQData()
{
    artG_eventData.ctrl = 0;
    artG_eventData.shift = 0;
    artG_eventData.alt = 0;
    artG_eventData.meta = 0;
    artG_eventData.caps = 0;
    artG_eventData.num = 0;
    artG_eventData.mousePosX = 0;
    artG_eventData.mousePosY = 0;
    artG_eventData.leftButton = 0;
    artG_eventData.middleButton = 0;
    artG_eventData.rightButton = 0;

    _art_resetEventQValues();
}

void _art_resetEventQValues()
{
    artG_eventData.type = ART_EVENT_NULL;
    artG_eventData.keyCode = ART_KEY_NULL;
    artG_eventData.keyChar = 0;
    artG_eventData.mouseButton = ART_BUTTON_NULL;
    artG_eventData.mouseRelX = 0;
    artG_eventData.mouseRelY = 0;
    artG_eventData.resizeWidth = 0;
    artG_eventData.resizeHeight = 0;
}

void _art_updateMouseButton(Art_MouseButton button, int val)
{
    switch (button)
    {
    case ART_BUTTON_LEFT:
        artG_eventData.leftButton = val;
        break;
    case ART_BUTTON_MIDDLE:
        artG_eventData.middleButton = val;
        break;
    case ART_BUTTON_RIGHT:
        artG_eventData.rightButton = val;
        break;
    }
}

Art_EventType art_getEventType()
{
    return artG_eventData.type;
}

Art_KeyCode art_getKeyCode()
{
    return artG_eventData.keyCode;
}

unsigned int art_getKeyChar()
{
    return artG_eventData.keyChar;
}

Art_MouseButton art_getMouseButton()
{
    return artG_eventData.mouseButton;
}

int art_getMousePosX()
{
    return artG_eventData.mousePosX;
}

int art_getMousePosY()
{
    return artG_eventData.mousePosY;
}

int art_getMouseRelX()
{
    return artG_eventData.mouseRelX;
}

int art_getMouseRelY()
{
    return artG_eventData.mouseRelY;
}

int art_getLeftButton()
{
    return artG_eventData.leftButton;
}

int art_getMiddleButton()
{
    return artG_eventData.middleButton;
}

int art_getRightButton()
{
    return artG_eventData.rightButton;
}

int art_getCtrl()
{
    return artG_eventData.ctrl;
}

int art_getShift()
{
    return artG_eventData.shift;
}

int art_getAlt()
{
    return artG_eventData.alt;
}

int art_getMeta()
{
    return artG_eventData.meta;
}

int art_getCaps()
{
    return artG_eventData.caps;
}

int art_getNum()
{
    return artG_eventData.num;
}

