#include <windows.h>
#include<windowsx.h>
#include<WinUser.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"
#include "Engine.h"

class DPIScale
{
    static float scaleX;
    static float scaleY;

public:
    static void Initialize(HWND hwnd)
    {
        FLOAT dpiX, dpiY;
       // LogicalDpi{ get; }
        auto x = GetDpiForWindow(hwnd);
        scaleX = x / 96.0f;
        scaleY = x / 96.0f;
    }

    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y)
    {
        return D2D1::Point2F(static_cast<float>(x) / scaleX, static_cast<float>(y) / scaleY);
    }
};


float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class MainWindow : public BaseWindow<MainWindow>
{
private:
    // Physics Engine:
    Engine engine;
    // Factory Pointer
    ID2D1Factory*          pFactory;
    // Poionter to interface that represents render target.
    ID2D1HwndRenderTarget* pRenderTarget;
    // Pointer to interface that represents the brush.
    ID2D1SolidColorBrush*  pBrush;
    // Ellipse pointer
    D2D1_ELLIPSE           ellipse;
    // Mouse Pointer
    D2D1_POINT_2F          ptMouse;


    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX, int pixelY, DWORD flags);
    void onSpaceDown();



public:

    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL),
                   ellipse(D2D1::Ellipse(D2D1::Point2F(),0,0)),
                   ptMouse(D2D1::Point2F())
    {
    }

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

// Recalculate drawing layout when the size of the window changes.
void MainWindow::CalculateLayout()
{

}

// Creates pRenderTager and pBrush interfaces pointers.
HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        //Creates a render target window:
        //      D2D1::RenderTargetProperties -> specifies options 
        //                                      that are common to any type of  
        //                                      render target.
        //      D2D1::HwndRenderTargetProperties -> Specifies handle to window 
        //                                          + size of render target in px  
        //      &pRenderTarget -> pointer to ID21HwndRenderTarget
        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
            // creates solid-color brush:
            //              color    ->  Specifies color to be used in brush
            //              pBrush   ->  Given address of the pointer to the new brush.  
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

            if (SUCCEEDED(hr))
            {
                CalculateLayout();
            }
        }
    }
    return hr;
}

// Releases pointers.
void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

// Draws circle
void MainWindow::OnPaint()
{
    // creates render target and brush resources.
    //      sets up pRenderTarget & pBrush
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);
        //signal start of drawing.
        pRenderTarget->BeginDraw();
        //fills whole render with a single color.
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        //drawas a filled ellipse.
        pRenderTarget->FillEllipse(ellipse, pBrush);
        //signals the end of drawing.
        hr = pRenderTarget->EndDraw(); // returns failure or success of rendering.
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

void MainWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    wchar_t msg[32];
    switch (uMsg)
    {
    case WM_CREATE:
        // Factory creation for single thread drawing
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        DPIScale::Initialize(m_hwnd);
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        Resize();
        return 0;
    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;
    case WM_LBUTTONUP:
        OnLButtonUp();
        return 0;
    case WM_MOUSEMOVE:
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;
    case WM_KEYDOWN:
        if (wParam & 0x20) {
            swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
            OutputDebugString(msg);
        }

        
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags) {
    SetCapture(m_hwnd);
    ellipse.point = ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
    ellipse.radiusX = ellipse.radiusY = 1.0f;
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp()
{
    ReleaseCapture(); 
}
void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    if (flags & MK_LBUTTON)
    {

        const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);

        const float radius = (dips.x - ptMouse.x) / 2;
        const float height = (dips.y - ptMouse.y) / 2;
        const float x1 = ptMouse.x + radius;
        const float y1 = ptMouse.y + radius;
        Sphere new_obj(x1, y1, radius);
        engine.add(new_obj);
        ellipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), radius, radius);
      

        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}


