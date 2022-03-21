#pragma once
#include <d2d1.h>

namespace GameClient
{
	class Engine
	{
	private:
		HWND _windowHandle = nullptr;
		ID2D1Factory* _pDirect2dFactory = nullptr;
		ID2D1HwndRenderTarget* _pRenderTarget = nullptr;
		ID2D1SolidColorBrush* _pLightSlateGrayBrush = nullptr;
		ID2D1SolidColorBrush* _pCornflowerBlueBrush = nullptr;

	public:
		explicit Engine(HWND windowHandle);
		~Engine();
		void Resize(UINT width, UINT height) const;

		Engine(Engine& copyOther) = delete;
		Engine operator=(Engine& copyOther) = delete;

		Engine operator=(Engine&& moveOther) = delete;
		Engine(Engine&& moveOther) = delete;

		HRESULT Initialize();
		HRESULT Draw();

	private:
		HRESULT CreateDeviceResources();
		void DiscardDeviceIndependentResources();
		void DiscardDeviceResources();
	};
}

