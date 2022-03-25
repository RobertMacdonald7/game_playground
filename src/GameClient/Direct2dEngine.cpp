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

HRESULT GameClient::Engine::Direct2dEngine::Draw()
{
	auto result = S_OK;
	result = CreateDeviceResources();

	RETURN_FAILED_HRESULT(result);

	_pRenderTarget->BeginDraw();
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	const auto [sWidth, sHeight] = _pRenderTarget->GetSize();

	// Draw a Grid
	const auto width = static_cast<int>(sWidth);
	const auto height = static_cast<int>(sHeight);

	for (auto x = 0; x < width; x += 10)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), sHeight),
			_pLightSlateGrayBrush,
			0.5f);
	}

	for (auto y = 0; y < height; y += 10)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(sWidth, static_cast<FLOAT>(y)),
			_pCornflowerBlueBrush,
			0.5f);
	}

	result = _pRenderTarget->EndDraw();

	if (result == D2DERR_RECREATE_TARGET)
	{
		// Resources will be recreated next Draw()
		result = S_OK;
		DiscardDeviceResources();
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
	GetClientRect(_windowHandle, &rect);

	const D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

	result = _pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_windowHandle, size),
		&_pRenderTarget);

	RETURN_FAILED_HRESULT(result);

	result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &_pCornflowerBlueBrush);

	RETURN_FAILED_HRESULT(result);

	result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &_pLightSlateGrayBrush);

	return result;
}

void GameClient::Engine::Direct2dEngine::DiscardDeviceIndependentResources()
{
	SafeRelease(&_pDirect2dFactory);
}

void GameClient::Engine::Direct2dEngine::DiscardDeviceResources()
{
	SafeRelease(&_pRenderTarget);
	SafeRelease(&_pCornflowerBlueBrush);
	SafeRelease(&_pLightSlateGrayBrush);
}
