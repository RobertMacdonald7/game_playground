#pragma once

#include <d2d1.h>

#include "../Engine/Coordinate2d.h"

namespace GameClient::Utility {
	class Direct2dUtility {
	public:
		static D2D1_RECT_F CreateUnitRectangle(Engine::Coordinate2d offset, Engine::Coordinate2d position, Engine::Coordinate2dF scale);
	};
}
