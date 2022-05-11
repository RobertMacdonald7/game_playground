#pragma once

#include <d2d1.h>

namespace GameClient::Utility {
	class Direct2dUtility {
	public:
		static D2D1_RECT_F CreateUnitRectangle(FLOAT xOffset, FLOAT yOffset, FLOAT x, FLOAT y, FLOAT xScale, FLOAT yScale);
	};
}
