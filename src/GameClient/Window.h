#pragma once

#include <memory>

#include "Game.h"
#include "Macros.h"

namespace GameClient
{
	class Window
	{
	private:
		HWND _hwnd = nullptr;
		std::unique_ptr<Game> _game = nullptr;
		const float _defaultDpi = 96.f;

	public:
		Window();
		Window(Window& copyOther) = delete;
		Window operator=(Window& copyOther) = delete;

		Window operator=(Window&& moveOther) = delete;
		Window(Window&& moveOther) = delete;

		~Window();

		// Register the window class and call methods for instantiating drawing resources
		HRESULT Initialize(HINSTANCE hInstance);

		// Process and dispatch messages
		void Run() const;

		void OnKeyDown(Input::Input pressedKey) const;

	private:
		// Resize the render target.
		void OnResize(const int width, const int height) const;

		static std::tuple<LRESULT, bool> OnSize(const Window& pClient, LPARAM lParam);
		static std::tuple<LRESULT, bool> OnDisplayChange(HWND hWnd);
		static std::tuple<LRESULT, bool> OnPaint(HWND hWnd);
		static std::tuple<LRESULT, bool> OnDestroy();
		static std::tuple<LRESULT, bool> OnKeyDown(const Window& pClient, WPARAM wParam);

		// The windows procedure.
		static LRESULT CALLBACK WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);
	};
}
