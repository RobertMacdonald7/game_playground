#include "Direct2dEngine.h"

#include "Macros.h"

// ReSharper disable once CppParameterMayBeConst
GameClient::Engine::Direct2dEngine::Direct2dEngine(HWND windowHandle): IEngine(windowHandle)
{ }

GameClient::Engine::Direct2dEngine::~Direct2dEngine()
{
	DiscardDeviceIndependentResources();
	DiscardDeviceResources();
}

HRESULT GameClient::Engine::Direct2dEngine::Initialize()
{
	// Create a Direct2D factory
	const auto result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pDirect2dFactory);

	return result;
}

void GameClient::Engine::Direct2dEngine::Resize(const UINT width, const UINT height) const
{
	if (!_pRenderTarget)
	{
		return;
	}

	const D2D1_SIZE_U size = D2D1::SizeU(width, height);
	_pRenderTarget->Resize(size);
}

HRESULT GameClient::Engine::Direct2dEngine::Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables)
{
	auto result = S_OK;
	result = CreateDeviceResources();
	RETURN_FAILED_HRESULT(result);

	for (auto& drawable : drawables)
	{
		result = drawable->CreateDeviceResources(_pRenderTarget);
		RETURN_FAILED_HRESULT(result);
	}

	RETURN_FAILED_HRESULT(result);

	_pRenderTarget->BeginDraw();
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	for (auto& drawable : drawables)
	{
		drawable->Draw(_pRenderTarget);
	}

	result = _pRenderTarget->EndDraw();

	if (result == D2DERR_RECREATE_TARGET)
	{
		// Resources will be recreated next Draw()
		result = S_OK;
		DiscardDeviceResources();
		for (auto& drawable : drawables)
		{
			drawable->DiscardDeviceResources();
		}
	}

	return result;
}

HRESULT GameClient::Engine::Direct2dEngine::CreateDeviceResources()
{
	auto result = S_OK;

	if (_pRenderTarget)
	{
		return result;
	}

	RECT rect;
	GetClientRect(GetWindowHandle(), &rect);

	const D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

	result = _pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetWindowHandle(), size),
		&_pRenderTarget);

	RETURN_FAILED_HRESULT(result);

	return result;
}

void GameClient::Engine::Direct2dEngine::DiscardDeviceIndependentResources()
{
	SafeRelease(&_pDirect2dFactory);
}

void GameClient::Engine::Direct2dEngine::DiscardDeviceResources()
{
	SafeRelease(&_pRenderTarget);
}
