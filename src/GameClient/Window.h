#pragma once

#include <memory>
#include <Windows.h>

#include "Game.h"
#include "Macros.h"

namespace GameClient
{
	class Window
	{
	private:
		HWND _hwnd = nullptr;
		std::unique_ptr<Game> _game = nullptr;
		const FLOAT _defaultDpi = 96.f;

	public:
		Window();
		Window(Window& copyOther) = delete;
		Window operator=(Window& copyOther) = delete;

		Window operator=(Window&& moveOther) = delete;
		Window(Window&& moveOther) = delete;

		~Window();

		// Register the window class and call methods for instantiating drawing resources
		HRESULT Initialize();

		// Process and dispatch messages
		void Run() const;

	private:
		// Resize the render target.
		void OnResize(
			UINT width,
			UINT height
		) const;

		// The windows procedure.
		static LRESULT CALLBACK WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);
	};
}
