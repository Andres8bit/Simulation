#pragma once
#include<d3d12.h>
#include<d3d12sdklayers.h>
#include<d3dcompiler.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<dxgi.h>
#include"Utils.h"
#include"GraphicsException.h"


using namespace Microsoft::WRL;
struct SpriteData {
	int width;
	int height;
	float x;
	float y;
	float scale;
	float angle;
	RECT rect;

	bool flipHorizontal;
	bool flipVertical;


};

class Graphics {
public:
	Graphics();
	virtual      ~Graphics();
	virtual void OnInit();
	virtual void OnUpdate();
	virtual void onRender();
	virtual void onDestroy();


private:
	//LPD3DXSPRITE sprite;

	HRESULT result;
	HWND windowHandler;
	static const UINT FrameCount = 2;


	D3D12_VIEWPORT	                  viewport;
	D3D12_RECT                        canvas;
	ComPtr<IDXGIFactory4>             factory;
	ComPtr<IDXGISwapChain3>           swapChain;
	ComPtr<ID3D12Device>              graphics_device;
	ComPtr<ID3D12Resource>            renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator>    commandAllocator;
	ComPtr<ID3D12CommandQueue>        commandQueue;
	ComPtr<ID3D12RootSignature>       rootSignature; // collection of descriptor tables.
	ComPtr<ID3D12DescriptorHeap>      descriptorHeap; // heap of objects a.k.a desctricptor to draw
	ComPtr<ID3D12PipelineState>       pipelineState;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12Resource>            vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW          vertexBufferView;
	UINT                              frameIndex;
	HANDLE                            fenceEvent;
	ComPtr<ID3D12Fence>               fence;
	UINT64                            fenceVal;
	UINT                              renderTargetDescriptorSize;


	bool fullscreen;
	int width;
	int height;
	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
	void WaitForFrame();
	void GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter);
	void CreateFactory();
	void CreateHardwareAdapter();
	void CreateCommandQueue();
	void CreateSwapChain();
	void CreateRenderTarget();
	void CreateCommandAllocator();
};