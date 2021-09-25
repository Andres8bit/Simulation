#pragma once
#include<d3d9.h>
#include"Utils.h"

#define SAFE_RELEASE(ptr) { if(ptr)(ptr)->Release(); (ptr)=NULL;  }
#define SAFE_DELETE(ptr){ if(ptr)delete (ptr); (ptr)=NULL;  }

#define DEVICEPOINTER LPDIRECT3DDEVICE9
#define DIRECTPOINTER LPDIRECT3D9

class Graphics {
public:
	Graphics();
	virtual ~Graphics();
	void releaseAll();
	void initilize(HWND hw, int width, int height, bool fullscreen);

	HRESULT showBackbuffer();

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