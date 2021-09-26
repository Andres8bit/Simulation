#include "Events.h"
Events::Events() {
	clearKeys();
	clearMouse();
}

Events::~Events() {
	if (mouseCaptured) ReleaseCapture();
}

void Events::init(HWND windowHandle, bool capture) {
	try {
		mouseCaptured = capture;
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsagePage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = windowHandle;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
		if (mouseCaptured) SetCapture(windowHandle);
	}catch (...) {
		throw(EventExceptions(ErrorType::FATAL_ERROR));
	}
}

void Events::keyDown(WPARAM wParam) {
	if (wParam < 255) {
		keysDown[wParam] = true;
		keysPressed[wParam] = true;
	}
}

void Events::keyUP(WPARAM wParam) {
	if (wParam < 255) {
		keysDown[wParam] = false;
	}
}

bool Events::isKeyDown(UCHAR vKey)const {
	return vKey < 255 ? keysDown[vKey] : false;
}

bool Events::wasKeyPressed(UCHAR vKey)const {
	return vKey < 255 ? keysPressed[vKey] :false;
}

bool Events::anyKeyPressed()const {
	for (size_t i = 0; i < 255; i++) {
		if (keysPressed[i]) return true;
	}
	return false;
}

void Events::mouseIn(LPARAM lParam) {
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

void Events::mouseRawIn(LPARAM lParam) {
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
	RAWINPUT* raw = (RAWINPUT*)lpb;
	if (raw->header.dwType == RIM_TYPEMOUSE) {
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}


void Events::setMouseSecondary(WPARAM wParam) {
	mouse1 = (wParam & MK_XBUTTON1) ? true : false;
	mouse2 = (wParam & MK_XBUTTON2) ? true : false;
}

void Events::clearKeys() {
	for (int i = 0; i < 255; i++) {
		keysPressed[i] = false;
		keysDown[i] = false;
	}
}

void Events::clearKeyPressed(UCHAR vkey) {
	for (size_t i = 0; i < 255; i++) {
		keysPressed[i] = false;
	}
}



void Events::clearAll(){
	clearKeys();
	clearMouse();
}


void Events::clearMouse() {
	mouseX = 0;
	mouseY = 0;
	mouseRawX = 0;
	mouseRawY = 0;
	mouseLeft = false;
	mouseRight = false;
	mouseMid = false;
	mouse1 = false;
	mouse2 = false;
}
void Events::clear(EventType what) {
	if (what == EventType::KEYS_DOWN) {
		for (size_t i = 0; i < 255; i++) {
			keysDown[i] = false;
		}
		return;
	}

	if (what == EventType::KEYS_PRESSED) {
		for (size_t i = 0; i < 255; i++) {
			keysPressed[i] = false;
		}
		return;
	}

	if (what == EventType::MOUSE) {
		clearMouse();
		return;
	}

}