#pragma once

#include <d2d1.h>

#include "GameDefinitions.h"

namespace GameClient::Utility {
	class Direct2dUtility {
	public:
		static D2D1_RECT_F CreateUnitRectangle(FLOAT xOffset, FLOAT yOffset, FLOAT x, FLOAT y);
	};
}
