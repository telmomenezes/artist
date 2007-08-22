class EventQ
{

%TypeHeaderCode
#include "EventQ.h"
using namespace pyc;
%End


public:
	EventQ();
	virtual ~EventQ();

	virtual bool init()=0;
	virtual bool next()=0;

	virtual void enableKeyChar(bool enable=true)=0;

	EventType getType();
	KeyCode getKeyCode();
	unsigned int getKeyChar();
	MouseButton getMouseButton();
	int getMousePosX();
	int getMousePosY();
	int getMouseRelX();
	int getMouseRelY();
	bool getLeftButton();
	bool getMiddleButton();
	bool getRightButton();
	bool getCtrl();
	bool getShift();
	bool getAlt();
	bool getMeta();
	bool getCaps();
	bool getNum();
};
