/*
 * Artist
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_ARTIST_EVENT_Q_H)
#define __INCLUDE_ARTIST_EVENT_Q_H

#include "artist_types.h"

typedef struct
{
    Art_EventType type; 
    Art_KeyCode keyCode;
    unsigned int keyChar;
    int ctrl;
    int shift;
    int alt;
    int meta;
    int caps;
    int num;
    Art_MouseButton mouseButton;
    int mousePosX;
    int mousePosY;
    int mouseRelX;
    int mouseRelY;
    int resizeWidth;
    int resizeHeight;
    int leftButton;
    int middleButton;
    int rightButton;
} Art_EventData;

Art_EventData artG_eventData;

int art_nextEvent();

void art_enableKeyChar(int enable);

Art_EventType art_getEventType();
Art_KeyCode art_getKeyCode();
unsigned int art_getKeyChar();
Art_MouseButton art_getMouseButton();
int art_getMousePosX();
int art_getMousePosY();
int art_getMouseRelX();
int art_getMouseRelY();
int art_getLeftButton();
int art_getMiddleButton();
int art_getRightButton();
int art_getCtrl();
int art_getShift();
int art_getAlt();
int art_getMeta();
int art_getCaps();
int art_getNum();

int _art_initEventQ();
void _art_initEventQData();
void _art_resetEventQValues();
void _art_updateMouseButton(Art_MouseButton button, int val);

#endif

