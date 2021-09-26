#pragma once
#include"EventExceptions.h"
#include <hidusage.h>
#include<d3d9.h>
#include<winuser.h>
#include<windowsx.h>
class Events
{
public:
	Events();
	~Events();
	void init(HWND windowHandle, bool capture);
	void keyDown(WPARAM wParam);
	void keyUP(WPARAM wParam);
	bool isKeyDown(UCHAR vkey)const;
	bool wasKeyPressed(UCHAR vkey)const;
	bool anyKeyPressed()const;
	void mouseIn(LPARAM lParam);
	void mouseRawIn(LPARAM lParam);
	void setMouseL(bool state) { mouseLeft = state; }
	void setMouseR(bool state) { mouseRight = state; }
	void setMouseMid(bool state) { mouseMid = state; }
	void setMouseSecondary(WPARAM wParam);
	int getMouseX()const { return mouseX; }
	int getMouseY()const { return mouseY; }
	int getMouseRawX()const { return mouseRawX; }
	int getMouseRawY()const { return mouseRawY; }
	bool getMouseLeft()const { return mouseLeft; }
	bool getMouseRight()const { return mouseRight; }
	bool getMouse1()const { return mouse1; }
	bool getMouse2()const { return mouse2; }

	void clearKeys();
	void clearMouse();
	void clearKeyPressed(UCHAR vkey);
	void clearAll();
	void clear(EventType what);

private:
	// boolean representing whether a key is currently pressed down.
	bool keysDown[255];
    // boolean representing whether a key was pressed durring last loop.
	bool keysPressed[255];
	int mouseX;
	int mouseY;
	int mouseRawX;
	int mouseRawY;
	RAWINPUTDEVICE Rid[1]; // HD mouse
	bool mouseCaptured;
	bool mouseLeft;
	bool mouseMid;
	bool mouseRight;
	bool mouse1;
	bool mouse2;
	

	


};

