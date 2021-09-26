#pragma once
#include<d3d9.h>
#include"Utils.h"
#include"GraphicsExceptions.h"




class Graphics {
public:
	Graphics();
	virtual ~Graphics();
	void releaseAll();
	void initilize(HWND hw, int width, int height, bool fullscreen);
	HRESULT beginScene();
	HRESULT endScene();
	HRESULT reset();
	HRESULT showBackbuffer();
	HRESULT getDeviceState();
private:
	DIRECTPOINTER direct3d;
	DEVICEPOINTER device3d;
	D3DPRESENT_PARAMETERS d3dpp;
	HRESULT result;
	HWND windowHandler;
	bool fullscreen;
	int width;
	int height;
	void init();
};