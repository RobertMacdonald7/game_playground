#pragma once

#include "Colour.h"
#include "Coordinate2d.h"
#include "Size.h"
#include "../Macros.h"

namespace GameClient::Engine
{
	class IRenderTarget // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IRenderTarget() = default;

		virtual HRESULT CreateDeviceResources() = 0;
		virtual void DrawUnitRectangle(Coordinate2d offset, Coordinate2d position, Coordinate2dF scale,
		                               Colour colour) = 0;
		virtual void DrawLine(Coordinate2dF p0, Coordinate2dF p1, float strokeWidth, Colour colour) = 0;
		virtual void Resize(Size size) = 0;
		virtual void BeginDraw() = 0;
		virtual HRESULT EndDraw() = 0;
	};
}
