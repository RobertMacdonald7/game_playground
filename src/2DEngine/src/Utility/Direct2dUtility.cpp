#include "Direct2dUtility.h"

#include <cassert>

D2D1_RECT_F GameClient::Utility::Direct2dUtility::CreateUnitRectangle(const Engine::Coordinate2d offset,
																	  const Engine::Coordinate2d position,
																	  const Engine::Coordinate2dF scale,
																	  const int unitSizePixels)
{
	// TODO - Make scale a "size" instead to control how many units are used to construct the rectangle
	assert((scale.x >= 0 && scale.x < .5f) && (scale.y >= 0 && scale.y < .5f));

	const auto left = offset.x + (unitSizePixels * position.x);
	const auto top = offset.y + (unitSizePixels * position.y);
	const auto right = left + unitSizePixels;
	const auto bottom = top + unitSizePixels;

	const auto leftScaled = left + scale.x * unitSizePixels;
	const auto topScaled = top + scale.y * unitSizePixels;
	const auto rightScaled = right - scale.x * unitSizePixels;
	const auto bottomScaled = bottom - scale.y * unitSizePixels;

	const auto rectangle = D2D1::RectF(leftScaled, topScaled, rightScaled, bottomScaled);

	return rectangle;
}
