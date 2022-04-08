#include "Direct2dUtility.h"

namespace GameClient::Utility {
	D2D1_RECT_F Direct2dUtility::CreateUnitRectangle(FLOAT xOffset, FLOAT yOffset, FLOAT x, FLOAT y)
	{
		const auto rectangle = D2D1::RectF(
			xOffset + (UNIT_SIZE * x),
			yOffset + (UNIT_SIZE * y),
			xOffset + (UNIT_SIZE * x) + UNIT_SIZE,
			yOffset + (UNIT_SIZE * y) + UNIT_SIZE);

		return rectangle;
	}
}