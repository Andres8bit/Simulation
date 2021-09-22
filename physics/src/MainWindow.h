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

    Engine eng;
    Mode mode;
    TYPE obj_mode;
    size_t nextColor;
    HCURSOR hCursor;
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
    HRESULT InsertObj(float x, float y);
    HRESULT InsertSphere(float x, float y);
    HRESULT InsertRect(float x, float y);
    HRESULT InsertTriangle(float x, float y);
    BOOL HitTest(float x, float y);
    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void OnRButtonDown();
    void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX, int pixelY, DWORD flags);
    void onSpaceDown();
    void SetMode(Mode m);
    void SetObjType(WPARAM choice);
    void resizeObj(std::shared_ptr<Obj>& obj,Vec& pos,Vec& dims);

public:

    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL),
        ptMouse(D2D1::Point2F()), nextColor(0)
    {
        obj_mode = TYPE::SPHERE;
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

    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);
        //signal start of drawing.
        pRenderTarget->BeginDraw();
        //fills whole render with a single color.
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

        eng.render(pRenderTarget, pBrush);
        if (eng.Selection()) {
            (eng.Selection())->Draw(pRenderTarget,pBrush);
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
        Sphere temp;
        temp.set_pos(Vec(x, y));
        temp.set_color(D2D1::ColorF(colors[nextColor]));
        temp.set_radius(2.0f);
        eng.add_obj(temp);
        ((Sphere*)eng.Selection().get())->set_color(D2D1::ColorF(colors[nextColor]));
        ptMouse = D2D1::Point2F(x, y);
        nextColor = (nextColor + 1) % ARRAYSIZE(colors);
    }
    catch (std::bad_alloc)
    {
        return E_OUTOFMEMORY;
    }
    return S_OK;
}

BOOL MainWindow::HitTest(float x, float y) {
   return eng.hit_test(x, y);
}
// Creates pRenderTager and pBrush interfaces pointers.
HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        eng.set_bounds(rc.right, rc.bottom);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        //Creates a render target window:
        //      D2D1::RenderTargetProperties     ->  specifies options 
        //                                           that are common to any type of  
        //                                           render target.
        //      D2D1::HwndRenderTargetProperties -> Specifies handle to window 
        //                                          + size of render target in px  
        //      &pRenderTarget                   -> pointer to ID21HwndRenderTarget
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
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
        
        //Render scenes
        eng.render(pRenderTarget, pBrush);
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

    if (!win.Create(L"Collision Engine", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);


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
        OnRButtonDown();
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
 
        SetObjType(wParam);
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
            InsertObj(dipX, dipY);
        }
    }
    else {
        eng.clear_selection();
        if (HitTest(dipX, dipY)) {
            SetCapture(m_hwnd);
            Vec pos = eng.Selection()->get_pos();
            ptMouse = D2D1::Point2F(pos.x, pos.y);
            ptMouse.x -= dipX;
            ptMouse.y -= dipY;
        }
    }
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp()
{
    if ((mode == DrawMode) && eng.Selection()) {
        eng.clear_selection();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
    else if (mode == DragMode) {

    }
    ReleaseCapture();
}
void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    const float dipX = DPIScale::PixelsToDipsX(pixelX);
    const float dipY = DPIScale::PixelsToDipsY(pixelY);
    
    if ((flags & MK_LBUTTON) && eng.Selection())
    {
        if (mode == DrawMode) {
            Vec dims = Vec((dipX - ptMouse.x) / 2, (dipY - ptMouse.y) / 2);
            Vec posF = Vec(ptMouse.x + dims.x, ptMouse.y + dims.y);
            TYPE objType = eng.Selection()->get_type();

            eng.Selection()->set_pos(Vec(posF.x, posF.y));
            std::shared_ptr<Obj> temp = eng.Selection();
            resizeObj(temp,posF,dims);            
        }
        else if (mode == DragMode) {
            eng.Selection()->set_pos(Vec(dipX + float(ptMouse.x), dipY + float(ptMouse.y)));
        }
       InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::onSpaceDown() {
    if (mode == DrawMode) mode = DragMode;
    if (mode == DragMode) mode = DrawMode;
}

void MainWindow::OnRButtonDown() {
    
    mode = mode == DrawMode ? DragMode : DrawMode;
}

void MainWindow::SetObjType(WPARAM choice) {
    if (choice == 0x54) 
        obj_mode = TYPE::TRIANGLE;
    else {
        if (choice == 0x50) {
            obj_mode = TYPE::PLANE;

        }
        else {
            if (choice == 0x53) {
                obj_mode = TYPE::SPHERE;

            }
        }
    }
  
}

HRESULT MainWindow::InsertObj(float x, float y) {
    try {
        if (obj_mode == TYPE::SPHERE) {
            InsertSphere(x, y);
        }

        if (obj_mode == TYPE::PLANE) {
            InsertRect(x, y);
        }

        if (obj_mode == TYPE::TRIANGLE) {
            InsertSphere(x, y);
            MessageBox(NULL, L"should be triangle ", L"Msg title", MB_OK | MB_ICONQUESTION);

        }
    }
    catch (std::bad_alloc)
    {
        return E_OUTOFMEMORY;
    }
    return S_OK;
}

HRESULT MainWindow::InsertRect(float x, float y) {
    try
    {
        Plane temp(Vec((float)x,(float)y),Vec((float)x+2, (float)y+2));
        temp.set_pos(Vec(x,y));
        eng.add_obj(temp);
        eng.Selection().get()->set_color(D2D1::ColorF(colors[nextColor]));
        ptMouse = D2D1::Point2F(x, y);
        ((Plane*)eng.Selection().get())->set_dims(2.0f,2.0f);
        nextColor = (nextColor + 1) % ARRAYSIZE(colors);
    }
    catch (std::bad_alloc)
    {
        return E_OUTOFMEMORY;
    }
    return S_OK;
}

HRESULT MainWindow::InsertTriangle(float x, float y) {
    return S_OK;
}

void MainWindow::resizeObj(std::shared_ptr<Obj>& obj,Vec& pos,Vec& dims) {
    TYPE objType = obj->get_type();

    switch (objType) {
    case TYPE::SPHERE:
        ((Sphere*)obj.get())->set_radius(abs(dims.y));
        break;
    case TYPE::PLANE:
        ((Plane*)obj.get())->set_dims(dims.x,dims.y);
    default:
        break;
    }


}