#pragma once
#include<d2d1.h>
//#include"Vec.h"

#define DEVICEPOINTER LPDIRECT3DDEVICE9
#define DIRECTPOINTER LPDIRECT3D9
#define SAFE_RELEASE(ptr) { if(ptr)(ptr)->Release(); (ptr)=NULL;  }
#define SAFE_DELETE(ptr){ if(ptr)delete (ptr); (ptr)=NULL;  }




const float MIN_FRAME_TIME = 0.033;
const float MAX_FRAME_TIME = 0.016;
const float MAX_FRAME_RATE = 60;
const float MIN_FRAME_RATE = 30;
const D2D1::ColorF BCKGRDCOLOR = D2D1::ColorF::Black;
const bool FULLSCREEN = false;


// still needs to be finalized:
// Default size for physics sim scene:
const UINT SCENE_WIDTH = 400; 
const UINT SCENE_HEIGHT = 400;
// Default mainwindow size:
const UINT WINDOW_WIDTH = 800;
const UINT WINDOW_HEIGHT = 800;


enum class EventType { KEYS_DOWN, KEYS_PRESSED, MOUSE };
enum class ErrorType { FATAL_ERROR, LOST_DEVICE };





namespace Utils {
    class DPIScale
    {
        static float scaleX;
        static float scaleY;

    public:
        static void Initialize(HWND hwnd)

        {
            FLOAT dpiX, dpiY;
            auto x = GetDpiForWindow(hwnd);
            scaleX = x / 96.0f;
            scaleY = x / 96.0f;
        }

        template <typename T>
        static D2D1_POINT_2F PixelsToDips(T x, T y)
        {
            return D2D1::Point2F(static_cast<float>(x) / scaleX, static_cast<float>(y) / scaleY);
        }

        template <typename T>
        static  float PixelsToDipsX(T x)
        {
            return static_cast<float>(x) / scaleX;
        }

        template <typename T>
        static float PixelsToDipsY(T y)
        {
            return static_cast<float>(y) / scaleY;
        }

    };
}