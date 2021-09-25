#include"Graphics.h"

Graphics::Graphics() {
	direct3d = NULL;
	device3d = NULL;
	fullscreen = 800;
	width = 800;
}

Graphics:: ~Graphics() {
	releaseAll();
}
void Graphics::releaseAll() { 
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

void Graphics::initilize(HWND hw, int w, int h, bool fullscr) {
	windowHandler = hw;
	width = w;
	height = h;
	fullscreen = fullscr;
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	// need to create exception class to handle 
	// grapic class errors
	if (direct3d == NULL) throw;

	init();
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandler,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&device3d);
	if (FAILED(result))
		throw;
}

HRESULT Graphics::showBackbuffer() {
	result = E_FAIL;
	device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0);
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}

void Graphics::init() {
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		
		if (fullscreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = windowHandler;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...) {
		//custom exceptions needed
	}
}