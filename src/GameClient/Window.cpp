#include "Window.h"

#include <cmath>
#pragma comment(lib, "d2d1")

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
		// Create the Engine here
		_engine = std::make_unique<Engine>(_hwnd);
		result = _engine->Initialize();

		RETURN_NON_SUCCEEDED(result);

		ShowWindow(_hwnd, SW_SHOWNORMAL);
		UpdateWindow(_hwnd);
	}

	return result;
}

void GameClient::Window::Run() const
{
	MSG message;

	bool running = true;
	while (running)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				running = false;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			// _gameLogic->Update();
			_engine->Draw();
			//Sleep(15);
		}
	}
}

void GameClient::Window::OnResize(const UINT width, const UINT height) const
{
	if (_engine)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		_engine->Resize(width, height);
	}
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
