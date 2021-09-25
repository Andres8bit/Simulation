#pragma once
#include "framework.h"
#include<string>


float Utils::DPIScale::scaleX = 1.0f;
float Utils::DPIScale::scaleY = 1.0f;

D2D1::ColorF::Enum colors[] = { D2D1::ColorF::Yellow, D2D1::ColorF::Salmon, D2D1::ColorF::LimeGreen };
class MainWindow : public BaseWindow<MainWindow>
{
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
    void resizeObj(std::shared_ptr<Obj>& obj, Vec& pos, Vec& dims);

};
