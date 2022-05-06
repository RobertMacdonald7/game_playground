#include "Window.h"

#include <cmath>
#include <chrono>

#include "Direct2dEngine.h"

GameClient::Window::Window() = default;

GameClient::Window::~Window() = default;

HRESULT GameClient::Window::Initialize()
{
	// Register the window class.
	WNDCLASSEX windowClassEx = { };
	windowClassEx.cbSize = sizeof(WNDCLASSEX);
	windowClassEx.style = CS_HREDRAW | CS_VREDRAW;
	windowClassEx.lpfnWndProc = Window::WndProc;
	windowClassEx.cbClsExtra = 0;
	windowClassEx.cbWndExtra = sizeof(LONG_PTR);
	windowClassEx.hInstance = HINST_THISCOMPONENT;
	windowClassEx.hbrBackground = nullptr;
	windowClassEx.lpszMenuName = nullptr;
	windowClassEx.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
	windowClassEx.lpszClassName = L"Window";

	RegisterClassEx(&windowClassEx);


	// Because the CreateWindow function takes its size in pixels,
	// obtain the system DPI and use it to scale the window size.
	const auto dpiX = static_cast<FLOAT>(GetDpiForWindow(GetDesktopWindow()));
	const auto dpiY = dpiX;

	// Create the window.
	_hwnd = CreateWindowEx(
		0,
		L"Window",
		L"Direct2D Game Client",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<int>(ceil(640.f * dpiX / _defaultDpi)),
		static_cast<int>(ceil(480.f * dpiY / _defaultDpi)),
		nullptr,
		nullptr,
		HINST_THISCOMPONENT,
		this
	);

	auto result = _hwnd ? S_OK : E_FAIL;
	if (SUCCEEDED(result))
	{
		try
		{
			_game = std::make_unique<Game>(std::make_unique<Engine::Direct2dEngine>(_hwnd));

		}
		catch (std::exception)
		{
			result = E_FAIL;
		}

		RETURN_FAILED_HRESULT(result);

		ShowWindow(_hwnd, SW_SHOWNORMAL);
		UpdateWindow(_hwnd);
	}

	return result;
}

void GameClient::Window::Run() const
{
	MSG message{};
	message.message = WM_NULL;
	auto nextFrame = std::chrono::steady_clock::now();
	nextFrame += std::chrono::milliseconds(1);

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			
			_game->ProcessFrame();
		}
	}
}

void GameClient::Window::OnResize(const UINT width, const UINT height) const
{
	if (_game)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		_game->OnResize(width, height);
	}
}

std::tuple<LRESULT, bool> GameClient::Window::OnSize(const Window& pClient, const LPARAM lParam)
{
	const UINT width = LOWORD(lParam);
	const UINT height = HIWORD(lParam);
	pClient.OnResize(width, height);

	return std::make_tuple(0, true);
}

std::tuple<LRESULT, bool> GameClient::Window::OnDisplayChange(HWND hWnd)
{
	InvalidateRect(hWnd, nullptr, false);
	return std::make_tuple(0, true);
}

std::tuple<LRESULT, bool> GameClient::Window::OnPaint(HWND hWnd)
{
	ValidateRect(hWnd, nullptr);
	return std::make_tuple(0, true);
}

std::tuple<LRESULT, bool> GameClient::Window::OnDestroy()
{
	PostQuitMessage(0);
	return std::make_tuple(0, true);
}

LRESULT CALLBACK GameClient::Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		const auto pcs = std::bit_cast<LPCREATESTRUCT>(lParam);
		const auto pClient = static_cast<Window*>(pcs->lpCreateParams);

		::SetWindowLongPtrW(hWnd, GWLP_USERDATA, std::bit_cast<LONG_PTR>(pClient));

		result = 0;
	}
	else
	{
		const auto pClient = std::bit_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		auto wasHandled = false;

		if (pClient)
		{
			std::tuple<LRESULT, bool> ret;
			switch (message)
			{
			case WM_SIZE:
				ret = OnSize(*pClient, lParam);
				break;
			case WM_DISPLAYCHANGE:
				ret = OnDisplayChange(hWnd);
				break;
			case WM_PAINT:
				ret = OnPaint(hWnd);
				break;
			case WM_DESTROY:
				ret = OnDestroy();
				break;
			default:
				ret = std::make_tuple(0, false);
			}

			result = std::get<0>(ret);
			wasHandled = std::get<1>(ret);
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return result;
}
