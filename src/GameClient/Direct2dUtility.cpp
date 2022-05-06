#include "Direct2dUtility.h"

namespace GameClient::Utility {
	D2D1_RECT_F Direct2dUtility::CreateUnitRectangle(FLOAT xOffset, FLOAT yOffset, FLOAT x, FLOAT y)
	{
		const auto rectangle = D2D1::RectF(
			xOffset + (unit_size_pixels * x),
			yOffset + (unit_size_pixels * y),
			xOffset + (unit_size_pixels * x) + unit_size_pixels,
			yOffset + (unit_size_pixels * y) + unit_size_pixels);

		return rectangle;
	}
}