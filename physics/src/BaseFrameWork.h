#pragma once
#include<Windows.h>
#include"Graphics.h"
#include<timeapi.h>
class BaseFrameWork
{
public:
	BaseFrameWork();
	virtual ~BaseFrameWork();
	LRESULT msgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void renderScene();
	void run(HWND windowHandle);
	virtual void init(HWND hwnd) = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
	//virtual void deleteAll();
	virtual void HandleLostDevice();
	Graphics* getGraphics() { return graphics; }
	void exit() { PostMessage(hwnd, WM_DESTROY, 0, 0); }
	virtual void update() = 0;
	virtual void render() = 0;
protected:
	Graphics* graphics;
	HWND hwnd;
	HRESULT result;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;
	float frameTime;
	float fps;
	DWORD sleepTime;
	bool paused;
	bool initialized;
private:

};

