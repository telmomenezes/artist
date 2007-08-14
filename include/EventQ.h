/*
 * Pycasso
 * Copyright (C) 2007 Telmo Menezes.
 * telmo@telmomenezes.com
 *
 * This program is free software, released under the zlib/libpng
 * license. The license text is available in the file COPYING.
 */

#if !defined(__INCLUDE_PYCASSO_EVENT_Q_H)
#define __INCLUDE_PYCASSO_EVENT_Q_H

#include "pyc_types.h"

namespace pyc
{

class EventQ
{
public:
	EventQ();
	virtual ~EventQ();

	virtual bool init()=0;
	virtual bool next()=0;

	virtual void enableKeyChar(bool enable=true)=0;

	EventType getType(){return mType;}
	KeyCode getKeyCode(){return mKeyCode;}
	unsigned int getKeyChar(){return mKeyChar;}
	MouseButton getMouseButton(){return mMouseButton;}
	int getMousePosX(){return mMousePosX;}
	int getMousePosY(){return mMousePosY;}
	int getMouseRelX(){return mMouseRelX;}
	int getMouseRelY(){return mMouseRelY;}
	bool getLeftButton(){return mLeftButton;}
	bool getMiddleButton(){return mMiddleButton;}
	bool getRightButton(){return mRightButton;}
	bool getCtrl(){return mCtrl;}
	bool getShift(){return mShift;}
	bool getAlt(){return mAlt;}
	bool getMeta(){return mMeta;}
	bool getCaps(){return mCaps;}
	bool getNum(){return mNum;}

protected:
	void resetValues();
	void updateMouseButton(MouseButton button, bool val);

	EventType mType; 
	KeyCode mKeyCode;
	unsigned int mKeyChar;
	bool mCtrl;
	bool mShift;
	bool mAlt;
	bool mMeta;
	bool mCaps;
	bool mNum;
	MouseButton mMouseButton;
	int mMousePosX;
	int mMousePosY;
	int mMouseRelX;
	int mMouseRelY;
	int mResizeWidth;
	int mResizeHeight;
	bool mLeftButton;
	bool mMiddleButton;
	bool mRightButton;
};

}

#endif

