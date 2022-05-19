#include "Direct2dEngine.h"

#include "Direct2dRenderTarget.h"

GameClient::Engine::Direct2D::Direct2dEngine::Direct2dEngine(HWND windowHandle): IEngine(windowHandle)
{
}

GameClient::Engine::Direct2D::Direct2dEngine::~Direct2dEngine()
{
	DiscardDeviceIndependentResources();
	DiscardDeviceResources();
}

HRESULT GameClient::Engine::Direct2D::Direct2dEngine::Initialize()
{
	// Create a Direct2D factory
	const auto result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pDirect2dFactory);

	return result;
}

void GameClient::Engine::Direct2D::Direct2dEngine::Resize(const int width, const int height) const
{
	if (!_renderTarget)
	{
		// Can't resize without a render target!
		return;
	}

	const auto size = Size{ width, height };
	_renderTarget->Resize(size);
}

HRESULT GameClient::Engine::Direct2D::Direct2dEngine::Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables)
{
	// Create any resources needed before drawing
	auto result = CreateDeviceResources();
	RETURN_FAILED_HRESULT(result);

	_renderTarget->BeginDraw();

	// Draw each IDrawable
	for (auto& drawable : drawables)
	{
		drawable->Draw(_renderTarget);
	}

	result = _renderTarget->EndDraw();

	if (result == D2DERR_RECREATE_TARGET)
	{
		// Discard, resources will be recreated next Draw()
		result = S_OK;
		DiscardDeviceResources();
	}

	return result;
}

HRESULT GameClient::Engine::Direct2D::Direct2dEngine::CreateDeviceResources()
{
	auto result = S_OK;

	if (_renderTarget)
	{
		// render target is already created, no need to re-create
		return result;
	}

	// Make the render target buffer equal to the window size
	RECT rect;
	GetClientRect(GetWindowHandle(), &rect);
	const D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

	// Create the render target
	ID2D1HwndRenderTarget* renderTarget = nullptr;
	result = _pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetWindowHandle(), size),
		&renderTarget);

	// Assumes renderTarget is nullptr if CreateHwndRenderTarget fails
	RETURN_FAILED_HRESULT(result);

	// Wrap the render target and create all brushes
	_renderTarget = std::make_shared<Direct2dRenderTarget>(renderTarget);
	result = _renderTarget->CreateDeviceResources();

	return result;
}

void GameClient::Engine::Direct2D::Direct2dEngine::DiscardDeviceIndependentResources()
{
	SafeRelease(&_pDirect2dFactory);
}

void GameClient::Engine::Direct2D::Direct2dEngine::DiscardDeviceResources()
{
	// Safe discard of the underlying render target happens in Direct2dRenderTarget's destructor
	_renderTarget = nullptr;
}
