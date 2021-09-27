#include "CollisionScene.h"
CollisionScene::CollisionScene() {

}

CollisionScene::~CollisionScene() {
	releaseAll();
}
void CollisionScene::initialize(HWND windowHandle) {
	BaseFrameWork::init(windowHandle);
}

void CollisionScene::update() {

}

void CollisionScene::render() {

}

void CollisionScene::releaseAll() {
	BaseFrameWork::releaseAll();
}

void CollisionScene::resetAll() {
	BaseFrameWork::releaseAll();
}


HRESULT CollisionScene::InsertObj(float x, float y) {

}

HRESULT CollisionScene::InsertSphere(float x, float y) {

}

HRESULT CollisionScene::InsertRect(float x, float y) {

}

HRESULT CollisionScene::InsertTriangle(float x, float y) {

}

BOOL CollisionScene::HitTest(float x, float y) {

}