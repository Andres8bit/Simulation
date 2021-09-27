#pragma once
#include "frameWork.h"
class CollisionScene : public BaseFrameWork
{
private:
	Engine engine;
	HRESULT InsertObj(float x, float y);
	HRESULT InsertSphere(float x, float y);
	HRESULT InsertRect(float x, float y);
	HRESULT InsertTriangle(float x, float y);
	BOOL HitTest(float x, float y);
public:
	CollisionScene();
	virtual ~CollisionScene();
	void initialize(HWND windowHandle);
	void update();
	void render();
	void releaseAll();
	void resetAll();
};

