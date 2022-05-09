#pragma once
#include <d2d1.h>

namespace GameClient::Engine
{
	class IDrawable
	{
	public:
		virtual ~IDrawable() = default;

		virtual void Draw(ID2D1HwndRenderTarget* renderTarget) = 0;

		virtual HRESULT CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) = 0;

		virtual void DiscardDeviceResources() = 0;
	};
}
