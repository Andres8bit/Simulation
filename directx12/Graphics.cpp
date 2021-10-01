#include"pch.h"
#include "Graphics.h"
Graphics::Graphics() {

}

Graphics:: ~Graphics() {

}

void Graphics::OnInit() {
	LoadPipeline();
	LoadAssets();
}

void Graphics::OnUpdate() {

}


void Graphics::onRender() {

}

void Graphics::onDestroy() {

}


void Graphics::LoadPipeline() {
	CreateFactory();
	CreateHardwareAdapter();
	CreateCommandQueue();
	CreateSwapChain();
	CreateRenderTarget();
	CreateCommandAllocator();
	//disable fullscreen:
	Utils::ThrowIfFailed(factory->MakeWindowAssociation(windowHandler, DXGI_MWA_NO_ALT_ENTER),GraphicsException(ErrorType::FATAL_ERROR));
	//get cur frame index;
	frameIndex = swapChain->GetCurrentBackBufferIndex();
}

void Graphics::LoadAssets() {

}

void Graphics::PopulateCommandList() {

}

void Graphics::WaitForFrame() {

}

void Graphics::GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter) {
	*ppAdapter = nullptr;
	for (UINT adapterIndex = 0;; ++adapterIndex) {
		IDXGIAdapter1* pAdapter = nullptr;
		if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(adapterIndex, &pAdapter)) {
			break;
		}
		if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
			*ppAdapter = pAdapter;
			return;
		}
		pAdapter->Release();
	}
}

void Graphics::CreateFactory() {
	//Creates factory:
	Utils::ThrowIfFailed(CreateDXGIFactory1(
		IID_PPV_ARGS(&factory)),
		GraphicsException(ErrorType::FATAL_ERROR)
	);
}

void Graphics::CreateHardwareAdapter() {
	ComPtr<IDXGIAdapter1>      hardwareAdapter;
	//sets up hardware adapter for creation:
	GetHardwareAdapter(factory.Get(), &hardwareAdapter);
	// create hardware adapter:
	Utils::ThrowIfFailed(D3D12CreateDevice(
		hardwareAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&graphics_device)
	), GraphicsException(ErrorType::FATAL_ERROR));
}

void Graphics::CreateCommandQueue() {
	D3D12_COMMAND_QUEUE_DESC   commandQueueDescriptor = {};
	//create Command Queue:
	commandQueueDescriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQueueDescriptor.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	Utils::ThrowIfFailed(
		graphics_device->CreateCommandQueue(&commandQueueDescriptor, IID_PPV_ARGS(&commandQueue)),
		GraphicsException(ErrorType::FATAL_ERROR)
	);
}

void Graphics::CreateSwapChain() {
	ComPtr<IDXGISwapChain>     swapChainPtr;
	DXGI_SWAP_CHAIN_DESC       swapChainDesc = {};
	// create swap chain Descriptor:
	swapChainDesc.BufferCount = FrameCount;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = windowHandler;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;

	//Create Swap Chain:
	Utils::ThrowIfFailed(factory->CreateSwapChain(
		commandQueue.Get(),
		&swapChainDesc,
		&swapChainPtr
	), GraphicsException(ErrorType::FATAL_ERROR));

	Utils::ThrowIfFailed(swapChainPtr.As(&swapChain), GraphicsException(ErrorType::FATAL_ERROR));
}

void Graphics::CreateRenderTarget() {
	D3D12_DESCRIPTOR_HEAP_DESC renderTargetHeapDescriptor = {};
	//Describe and Create RenderTargetView Heap:
	renderTargetHeapDescriptor.NumDescriptors = FrameCount;
	renderTargetHeapDescriptor.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	renderTargetHeapDescriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	Utils::ThrowIfFailed(graphics_device->CreateDescriptorHeap(
		&renderTargetHeapDescriptor,
		IID_PPV_ARGS(&descriptorHeap)
	), GraphicsException(ErrorType::FATAL_ERROR));

	renderTargetDescriptorSize = graphics_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	CD3DX12_CPU_DESCRIPTOR_HANDLE renderTargetHandle(descriptorHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < FrameCount; i++) {
		Utils::ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i])), GraphicsException(ErrorType::FATAL_ERROR));
		graphics_device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, renderTargetHandle);
		renderTargetHandle.Offset(1, renderTargetDescriptorSize);
	}
}

void Graphics::CreateCommandAllocator() {
	Utils::ThrowIfFailed(graphics_device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator)
	), GraphicsException(ErrorType::FATAL_ERROR));
}