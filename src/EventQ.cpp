/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#include "EventQ.h"

namespace pyc
{

EventQ::EventQ()
{
    mCtrl = false;
    mShift = false;
    mAlt = false;
    mMeta = false;
    mCaps = false;
    mNum = false;
    mMousePosX = 0;
    mMousePosY = 0;
    mLeftButton = false;
    mMiddleButton = false;
    mRightButton = false;

    resetValues();
}

EventQ::~EventQ()
{
}

void EventQ::resetValues()
{
    mType = EVENT_NULL;
    mKeyCode = KEY_NULL;
    mKeyChar = 0;
    mMouseButton = BUTTON_NULL;
    mMouseRelX = 0;
    mMouseRelY = 0;
    mResizeWidth = 0;
    mResizeHeight = 0;
}

void EventQ::updateMouseButton(MouseButton button, bool val)
{
    switch (button)
    {
    case BUTTON_LEFT:
        mLeftButton = val;
        break;
    case BUTTON_MIDDLE:
        mMiddleButton = val;
        break;
    case BUTTON_RIGHT:
        mRightButton = val;
        break;
    }
}

}

