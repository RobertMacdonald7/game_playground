#pragma once

#include <memory>

#include "Game.h"
#include "Macros.h"

namespace GameClient
{
	/**
	 * \brief The module associated with the window handle. Processes and dispatches messages.
	 */
	class Window
	{
	private:
		HWND _hwnd = nullptr;
		std::unique_ptr<Game> _game = nullptr;
		std::unique_ptr<std::thread> _rpcThread = nullptr;
		const float _defaultDpi = 96.f;

	public:
		Window();
		Window(Window& copyOther) = delete;
		Window operator=(Window& copyOther) = delete;

		Window operator=(Window&& moveOther) = delete;
		Window(Window&& moveOther) = delete;

		~Window();

		/**
		 * \brief Registers the window class and creates the game.
		 * \param hInstance The module handle.
		 * \return The result of the operation.
		 */
		HRESULT Initialize(HINSTANCE hInstance);

		/**
		 * \brief Message loop for processing and dispatching messages.
		 */
		void Run() const;

		/**
		 * \brief Forwards the pressed key to the game.
		 * \param pressedKey The pressed key.
		 */
		void OnKeyDown(Input::Input pressedKey) const;

	private:
		/**
		 * \brief Resizes the render target.
		 * \param width The width of the new size.
		 * \param height The height of the new size.
		 */
		void OnResize(int width, int height) const;

		/**
		 * \brief Handles the WM_SIZE message.
		 * \param pClient The window class instance.
		 * \param lParam The message parameters.
		 * \return A tuple of the result of the operation and whether the message was handled.
		 */
		static std::tuple<LRESULT, bool> OnSize(const Window& pClient, LPARAM lParam);

		/**
		 * \brief Handles the WM_DISPLAYCHANGE message.
		 * \param hWnd The window handle.
		 * \return A tuple of the result of the operation and whether the message was handled.
		 */
		static std::tuple<LRESULT, bool> OnDisplayChange(HWND hWnd);

		/**
		 * \brief Handles the WM_PAINT message.
		 * \param hWnd The window handle.
		 * \return A tuple of the result of the operation and whether the message was handled.
		 */
		static std::tuple<LRESULT, bool> OnPaint(HWND hWnd);

		/**
		 * \brief Handles the WM_DESTROY message.
		 * \return A tuple of the result of the operation and whether the message was handled.
		 */
		static std::tuple<LRESULT, bool> OnDestroy();

		/**
		 * \brief Handles the WM_KEYDOWN message.
		 * \param pClient The window class instance.
		 * \param wParam The message parameters.
		 * \return A tuple of the result of the operation and whether the message was handled.
		 */
		static std::tuple<LRESULT, bool> OnKeyDown(const Window& pClient, WPARAM wParam);

		/**
		 * \brief Handles messages.
		 * \param hWnd The window handle.
		 * \param message The message to process.
		 * \param wParam Message parameters.
		 * \param lParam Message parameters.
		 * \return The result of the operation.
		 */
		static LRESULT CALLBACK WndProc(
			HWND hWnd,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);
	};
}
