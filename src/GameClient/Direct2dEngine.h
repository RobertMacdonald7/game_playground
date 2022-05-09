#pragma once

#include <d2d1.h>

#include "IEngine.h"
#include "Snake.h"

#pragma comment(lib, "d2d1")

namespace GameClient::Engine
{
	class Direct2dEngine final : public IEngine
	{
	private:
		ID2D1Factory* _pDirect2dFactory = nullptr;
		ID2D1HwndRenderTarget* _pRenderTarget = nullptr;
		ID2D1SolidColorBrush* _pLightSlateGrayBrush = nullptr;
		ID2D1SolidColorBrush* _pCornflowerBlueBrush = nullptr;

	public:
		explicit Direct2dEngine(HWND windowHandle);
		~Direct2dEngine() override;

		Direct2dEngine(Direct2dEngine& copyOther) = delete;
		Direct2dEngine operator=(Direct2dEngine& copyOther) = delete;

		Direct2dEngine operator=(Direct2dEngine&& moveOther) = delete;
		Direct2dEngine(Direct2dEngine&& moveOther) = delete;

		HRESULT Initialize() override;
		void Resize(UINT width, UINT height) const override;
		HRESULT Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables) override;

	private:
		HRESULT CreateDeviceResources();
		void DiscardDeviceIndependentResources();
		void DiscardDeviceResources();
	};
}
