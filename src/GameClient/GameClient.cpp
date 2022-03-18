#include "GameClient.h"
#include <iostream>

#pragma comment(lib, "d2d1")

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	if (!(SUCCEEDED(CoInitialize(nullptr))))
	{
		return -1;
	}

	GameClient::GameClient client;

	if (SUCCEEDED(client.Initialize()))
	{
		client.RunMessageLoop();
	}
	CoUninitialize();

	return 0;
}

GameClient::GameClient::GameClient() = default;

GameClient::GameClient::~GameClient()
{
	SafeRelease(&_pDirect2dFactory);
	SafeRelease(&_pRenderTarget);
	SafeRelease(&_pCornflowerBlueBrush);
	SafeRelease(&_pLightSlateGrayBrush);
}

HRESULT GameClient::GameClient::Initialize()
{
	// Initialize device-independent resources, such
	// as the Direct2D factory.
	HRESULT result = CreateDeviceIndependentResources();

	if (SUCCEEDED(result))
	{
		// Register the window class.
		WNDCLASSEX windowClassEx = { };
		windowClassEx.cbSize = sizeof(WNDCLASSEX);
		windowClassEx.style = CS_HREDRAW | CS_VREDRAW;
		windowClassEx.lpfnWndProc = GameClient::WndProc;
		windowClassEx.cbClsExtra = 0;
		windowClassEx.cbWndExtra = sizeof(LONG_PTR);
		windowClassEx.hInstance = HINST_THISCOMPONENT;
		windowClassEx.hbrBackground = nullptr;
		windowClassEx.lpszMenuName = nullptr;
		windowClassEx.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
		windowClassEx.lpszClassName = L"GameClient";

		RegisterClassEx(&windowClassEx);


		// Because the CreateWindow function takes its size in pixels,
		// obtain the system DPI and use it to scale the window size.
		const auto dpiX = static_cast<FLOAT>(GetDpiForWindow(GetDesktopWindow()));
		const FLOAT dpiY = dpiX;

		// Create the window.
		_hwnd = CreateWindowEx(
			0,
			L"GameClient",
			L"Direct2D Game Client",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<int>(ceil(640.f * dpiX / 96.f)),
			static_cast<int>(ceil(480.f * dpiY / 96.f)),
			nullptr,
			nullptr,
			HINST_THISCOMPONENT,
			this
		);
		auto t = GetLastError();
		result = _hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(result))
		{
			ShowWindow(_hwnd, SW_SHOWNORMAL);
			UpdateWindow(_hwnd);
		}
	}

	return result;
}

void GameClient::GameClient::RunMessageLoop() const
{
	MSG message;

	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

HRESULT GameClient::GameClient::CreateDeviceIndependentResources()
{
	auto result = S_OK;

	// Create a Direct2D factory
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pDirect2dFactory);

	return result;
}

HRESULT GameClient::GameClient::CreateDeviceResources()
{
	auto result = S_OK;
	if (_pRenderTarget)
	{
		return result;
	}

	RECT rect;
	GetClientRect(_hwnd, &rect);

	const D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);

	result = _pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hwnd, size),
		&_pRenderTarget);

	if (!SUCCEEDED(result))
	{
		return result;
	}

	result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &_pCornflowerBlueBrush);

	if (!SUCCEEDED(result))
	{
		return result;
	}

	result = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &_pLightSlateGrayBrush);

	return result;
}

void GameClient::GameClient::DiscardDeviceResources()
{
	SafeRelease(&_pRenderTarget);
	SafeRelease(&_pCornflowerBlueBrush);
	SafeRelease(&_pLightSlateGrayBrush);
}

HRESULT GameClient::GameClient::OnRender()
{
	auto result = S_OK;
	result = CreateDeviceResources();

	if (!SUCCEEDED(result))
	{
		return result;
	}

	_pRenderTarget->BeginDraw();
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	D2D1_SIZE_F rectSize = _pRenderTarget->GetSize();

	// Draw a Grid
	const auto width = static_cast<int>(rectSize.width);
	const auto height = static_cast<int>(rectSize.height);

	for (auto x = 0; x < width; x += 10)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
			D2D1::Point2F(static_cast<FLOAT>(x), rectSize.height),
			_pLightSlateGrayBrush,
			0.5f);
	}

	for (auto y = 0; y < height; y += 10)
	{
		_pRenderTarget->DrawLine(
			D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
			D2D1::Point2F(rectSize.width, static_cast<FLOAT>(y)),
			_pLightSlateGrayBrush,
			0.5f);
	}

	result = _pRenderTarget->EndDraw();

	if (result == D2DERR_RECREATE_TARGET)
	{
		// Resources will be recreated next WM_PAINT or WM_DISPLAYCHANGE
		result = S_OK;
		DiscardDeviceResources();
	}

	return result;
}

void GameClient::GameClient::OnResize(const UINT width, const UINT height) const
{
	if (_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}

LRESULT CALLBACK GameClient::GameClient::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		const auto pcs = std::bit_cast<LPCREATESTRUCT>(lParam);
		const auto pClient = static_cast<GameClient*>(pcs->lpCreateParams);

		::SetWindowLongPtrW(hWnd, GWLP_USERDATA, std::bit_cast<LONG_PTR>(pClient));

		result = 0;
	}
	else
	{
		const auto pClient = std::bit_cast<GameClient*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		auto wasHandled = false;

		if (pClient)
		{
			switch (message)
			{
			case WM_SIZE:
				{
					const UINT width = LOWORD(lParam);
					const UINT height = HIWORD(lParam);
					pClient->OnResize(width, height);
					result = 0;
					wasHandled = true;
					break;
				}
			case WM_DISPLAYCHANGE:
				{
					InvalidateRect(hWnd, nullptr, false);
					result = 0;
					wasHandled = true;
					break;
				}
			case WM_PAINT:
				{
					pClient->OnRender();
					ValidateRect(hWnd, nullptr);
					result = 0;
					wasHandled = true;
					break;
				}
			case WM_DESTROY:
				{
					PostQuitMessage(0);
					result = 0;
					wasHandled = true;
					break;
				}
			default:
				{
					wasHandled = false;
				}
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return result;
}
