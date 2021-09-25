#pragma once

#include<d2d1.h>


#define SAFE_RELEASE(ptr) { if(ptr)(ptr)->Release(); (ptr)=NULL;  }
#define SAFE_DELETE(ptr){ if(ptr)delete (ptr); (ptr)=NULL;  }

const bool FULLSCREEN = false;
// still needs to be finalized:
// Default size for physics sim scene:
const UINT SCENE_WIDTH = 400; 
const UINT SCENE_HEIGHT = 400;
// Default size of the client:
const UINT CLIENT_WIDTH = 800;
const UINT CLIENT_HEIGHT = 800;
// Default mainwindow size:
const UINT WINDOW_WIDTH = 800;
const UINT WINDOW_HEIGHT = 800;


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