#pragma once

// Windows Header Files:
#include <Windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

template<class Interface>
void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = nullptr;
	}
}


#ifndef ASSERT
#if defined( DEBUG ) || defined( _DEBUG )
#define ASSERT(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define ASSERT(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

namespace GameClient
{
	class GameClient
	{
	private:
		HWND _hwnd = nullptr;
		ID2D1Factory* _pDirect2dFactory = nullptr;
		ID2D1HwndRenderTarget* _pRenderTarget = nullptr;
		ID2D1SolidColorBrush* _pLightSlateGrayBrush = nullptr;
		ID2D1SolidColorBrush* _pCornflowerBlueBrush = nullptr;

	public:
		GameClient();
		GameClient(GameClient& copyOther) = delete;
		GameClient operator=(GameClient& copyOther) = delete;

		GameClient operator=(GameClient&& moveOther) = delete;
		GameClient(GameClient&& moveOther) = delete;

		~GameClient();

		// Register the window class and call methods for instantiating drawing resources
		HRESULT Initialize();

		// Process and dispatch messages
		void RunMessageLoop() const;

	private:
		// Initialize device-independent resources.
		HRESULT CreateDeviceIndependentResources();

		// Initialize device-dependent resources.
		HRESULT CreateDeviceResources();

		// Release device-dependent resource.
		void DiscardDeviceResources();

		// Draw content.
		HRESULT OnRender();

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
