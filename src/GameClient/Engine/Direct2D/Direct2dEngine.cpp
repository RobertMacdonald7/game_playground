#include "Direct2dEngine.h"

#include "Direct2dRenderTarget.h"

// ReSharper disable once CppParameterMayBeConst
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
		return;
	}

	const auto size = Size{ width, height };
	_renderTarget->Resize(size);
}

HRESULT GameClient::Engine::Direct2D::Direct2dEngine::Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables)
{
	auto result = CreateDeviceResources();
	RETURN_FAILED_HRESULT(result);

	_renderTarget->BeginDraw();

	for (auto& drawable : drawables)
	{
		drawable->Draw(_renderTarget);
	}

	result = _renderTarget->EndDraw();

	if (result == D2DERR_RECREATE_TARGET)
	{
		// Resources will be recreated next Draw()
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
		return result;
	}

	RECT rect;
	GetClientRect(GetWindowHandle(), &rect);

	const D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

	ID2D1HwndRenderTarget* renderTarget = nullptr;
	result = _pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetWindowHandle(), size),
		&renderTarget);

	// Assumes renderTarget is nullptr if CreateHwndRenderTarget fails.
	RETURN_FAILED_HRESULT(result);

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
	_renderTarget = nullptr;
}
