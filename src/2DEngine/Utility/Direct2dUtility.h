#pragma once

#include <d2d1.h>

#include "../Engine/Coordinate2d.h"

namespace GameClient::Utility
{
	/**
	 * \brief %Utility methods used by the Direct2D engine.
	 */
	class Direct2dUtility
	{
	public:
		/**
		 * \brief Creates a unit rectangle
		 * \param offset X,Y offset from the rectangle's position.
		 * \param position X,Y position of the rectangle's top-left corner.
		 * \param scale How much vertical/horizontal space to shrink the rectangle.
		 * \param unitSizePixels The size of a unit in pixels.
		 * \return A unit rectangle.
		 */
		static D2D1_RECT_F CreateUnitRectangle(Engine::Coordinate2d offset, Engine::Coordinate2d position,
		                                       Engine::Coordinate2dF scale, int unitSizePixels);
	};
}
