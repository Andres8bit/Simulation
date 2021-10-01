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
	ComPtr<IDXGIFactory4> factory;
	ComPtr<IDXGIAdapter1> hardwareAdapter;
	D3D12_COMMAND_QUEUE_DESC commandQueueDescriptor = {};
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	Utils::ThrowIfFailed(CreateDXGIFactory1(
		IID_PPV_ARGS(&factory)),
		GraphicsException(ErrorType::FATAL_ERROR)
	);

	GetHardwareAdapter(factory.Get(), &hardwareAdapter);
	
	// create hardware adapter:
	Utils::ThrowIfFailed( D3D12CreateDevice(
		hardwareAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&graphics_device)
	),GraphicsException(ErrorType::FATAL_ERROR));

	//create Command Queue:
	commandQueueDescriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQueueDescriptor.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	Utils::ThrowIfFailed(
		graphics_device->CreateCommandQueue(&commandQueueDescriptor, IID_PPV_ARGS(&commandQueue)),
		GraphicsException(ErrorType::FATAL_ERROR)
	);

	// create swap chain:
	swapChainDesc.BufferCount = FrameCount;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = windowHandler;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;

	
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