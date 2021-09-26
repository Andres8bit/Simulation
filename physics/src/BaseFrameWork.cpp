#include "BaseFrameWork.h"

BaseFrameWork::BaseFrameWork() {
    paused = false;
    graphics = NULL;
    initialized = false;
}

BaseFrameWork::~BaseFrameWork() {
  //  deleteAll();
    ShowCursor(true);
}

LRESULT BaseFrameWork::msgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (initialized) {
        switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN: case WM_SYSKEYDOWN:
            return 0;
        }
    }

}

void BaseFrameWork::HandleLostDevice() {
    HRESULT result = graphics->getDeviceState();

    if (FAILED(result)) {

        if (result == D3DERR_DEVICELOST) {
            Sleep(100);
            return;
        }
        else if (result == D3DERR_DEVICELOST) {
            graphics->releaseAll();
            result = graphics->reset();
            if (FAILED(result))
                return;
            resetAll();

        }
        else
            return;
    }
}


void BaseFrameWork::renderScene() {
    HRESULT  result = graphics->beginScene();

    if (SUCCEEDED(result)) {
        render();
        graphics->endScene();
    }

    HandleLostDevice();
    graphics->showBackbuffer();
}

void BaseFrameWork::run(HWND windowHandle) {
    if (graphics == NULL) return;
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) /
        (float)(timerFreq.QuadPart);

    if (frameTime < MIN_FRAME_TIME) {
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime) * 1000);
        timeBeginPeriod(1);
        Sleep(sleepTime);
        timeEndPeriod(1);
        return;
    }
    if (frameTime > 0.0) {
        fps = (fps * 0.99f) + (0.01f / frameTime);   
    }

    if (frameTime > MAX_FRAME_TIME)
        frameTime = MAX_FRAME_TIME;
    
    timeStart = timeEnd;
    //read controlls calling controls class

    if (!paused) {
    // run state
        update();
       
    }
    render();
    //clear inputs
}