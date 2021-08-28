#pragma once
#include "framework.h"
#include<string>

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

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


float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;

D2D1::ColorF::Enum colors[] = { D2D1::ColorF::Yellow, D2D1::ColorF::Salmon, D2D1::ColorF::LimeGreen };
class MainWindow : public BaseWindow<MainWindow>
{
private:
    enum Mode {
        DrawMode,
        SelectMode,
        DragMode,
        PlayMode
    };

   
    Mode mode;
    size_t nextColor;
    HCURSOR hCursor;
    // List of Spheres in scene
    std::list<std::shared_ptr<Sphere>> spheres;
    // list of selectio iterators.
    std::list<std::shared_ptr<Sphere>>::iterator selection;
    // Factory Pointer
    ID2D1Factory* pFactory;
    // Poionter to interface that represents render target.
    ID2D1HwndRenderTarget* pRenderTarget;
    // Pointer to interface that represents the brush.
    ID2D1SolidColorBrush* pBrush;
    // Ellipse pointer
    D2D1_ELLIPSE           ellipse;
    // Mouse Pointer
    D2D1_POINT_2F          ptMouse;

    std::shared_ptr<Sphere> Selection() {
        if (selection == spheres.end()) {
            return nullptr;
        }
        else {
            return(*selection);
        }
    }

    void ClearSelection() { selection = spheres.end(); }
    HRESULT InsertSphere(float x, float y);
    
    BOOL HitTest(float x, float y);
    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void OnRButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX, int pixelY, DWORD flags);
    void onSpaceDown(); 
    void SetMode(Mode m);



public:
    Engine eng;
    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL),
        ptMouse(D2D1::Point2F()), nextColor(0), selection(spheres.end())
    {
    }
    void Update();
    void Render();
    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

void MainWindow::Update() {
    eng.step();
}

void MainWindow::Render() {
    pRenderTarget->BeginDraw();
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
    eng.render(pRenderTarget,pBrush);
    pRenderTarget->EndDraw();
}

void MainWindow::SetMode(Mode m)
{
    mode = m;

    LPWSTR cursor = NULL;
    switch (mode)
    {
    case DrawMode:
        cursor = IDC_CROSS;
        break;

    case SelectMode:
        cursor = IDC_HAND;
        break;

    case DragMode:
        cursor = IDC_SIZEALL;
        break;
    }

    hCursor = LoadCursor(NULL, cursor);
    SetCursor(hCursor);
}
// Recalculate drawing layout when the size of the window changes.
void MainWindow::CalculateLayout()
{

}
HRESULT MainWindow::InsertSphere(float x, float y) {
    try
    {
        selection = spheres.insert(
            spheres.end(),
            std::shared_ptr<Sphere>(new Sphere())
        );
        ptMouse = D2D1::Point2F(x, y);
        Selection()->set_center(Vec(x,y));
        Selection()->set_raduis(2.0f);
        Selection()->set_color(D2D1::ColorF(colors[nextColor]));
        eng.add_obj(*Selection());
        nextColor = (nextColor + 1) % ARRAYSIZE(colors);
    }
    catch (std::bad_alloc)
    {
        return E_OUTOFMEMORY;
    }
    return S_OK;
}

BOOL MainWindow::HitTest(float x, float y) {
    for (auto i = spheres.rbegin(); i != spheres.rend(); ++i) {
        if ((*i)->HitTest(x, y)) {
            selection = (++i).base();
            return TRUE;
        }
    }
    return FALSE;
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
        
        for (auto i = spheres.begin(); i != spheres.end(); ++i) {
            (*i)->Draw(pRenderTarget, pBrush);
        }
        if (Selection()) {
            pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
            pRenderTarget->DrawEllipse(Selection()->get_ui(), pBrush, 2.0f);
        }
      
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

    MSG msg;
    msg.message = WM_NULL;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            DispatchMessage(&msg);
        }
        else {
            win.Update();
            win.Render();
        }
    }
    return msg.wParam;
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
    case WM_RBUTTONDOWN:
        onSpaceDown();
        //if (mode == SelectMode) SetMode(DrawMode);
        //if (mode == DragMode ) SetMode(DrawMode);
        //if (mode == DrawMode) SetMode(DragMode);
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
                onSpaceDown();
            }
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags) {
    const float dipX = DPIScale::PixelsToDipsX(pixelX);
    const float dipY = DPIScale::PixelsToDipsY(pixelY);   

    if (mode == DrawMode) {
        POINT pt = { pixelX, pixelY };

        if (DragDetect(m_hwnd, pt)) {
            SetCapture(m_hwnd);
            InsertSphere(dipX, dipY);
        }
    }
    else {
        ClearSelection();
        if (HitTest(dipX, dipY)) {
            SetCapture(m_hwnd);
            Vec pos = Selection()->get_center();
            ptMouse = D2D1::Point2F(pos.x, pos.y);
            ptMouse.x -= dipX;
            ptMouse.y -= dipY;
           // SetMode(DragMode);
        }
    }
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp()
{
    if ((mode == DrawMode) && Selection()) {
        ClearSelection();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
    else if (mode == DragMode) {
        SetMode(SelectMode);
    }
    ReleaseCapture();
}
void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    const float dipX = DPIScale::PixelsToDipsX(pixelX);
    const float dipY = DPIScale::PixelsToDipsY(pixelY);
    
    if ((flags & MK_LBUTTON) && Selection())
    {
        if (mode == DrawMode) {
            const float width = (dipX - ptMouse.x) / 2;
            const float height = (dipY - ptMouse.y) / 2;
            const float x1 = ptMouse.x + width;
            const float y1 = ptMouse.y + height;
            Selection()->set_center(Vec(x1, y1)); 
            Selection()->set_raduis(width);
        }
        else if (mode == DragMode) {
            Selection()->set_center(Vec(dipX + double(ptMouse.x), dipY + double(ptMouse.y)));
        }
       InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::onSpaceDown() {
   // mode = PlayMode;
    InvalidateRect(m_hwnd, NULL, FALSE);
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
   // for (auto i = spheres.begin(); i != spheres.end(); ++i) {
      // (*i)->Redraw(pRenderTarget, pBrush);
    //}

    MessageBox(NULL, L"step", L"mainwindow", NULL);
}

void MainWindow::OnRButtonDown(int pixelX, int pixelY, DWORD flags) {
    if (mode == DrawMode) {
        mode = DragMode;
    }
    if (mode == DragMode) {
        mode = DrawMode;
    }
}