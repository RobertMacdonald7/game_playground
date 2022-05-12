#include "Direct2dUtility.h"

#include <stdexcept>

#include "../GameDefinitions.h"

	D2D1_RECT_F GameClient::Utility::Direct2dUtility::CreateUnitRectangle(const Engine::Coordinate2d offset, const Engine::Coordinate2d position, const Engine::Coordinate2dF scale)
	{
		if (!(scale.x >= 0 && scale.x < .5f) || !(scale.y >= 0 && scale.y < .5f))
		{
			throw std::out_of_range("Scaling factor was not valid");
		}

		const auto left = static_cast<float>(offset.x + (unit_size_pixels * position.x));
		const auto top = static_cast<float>(offset.y + (unit_size_pixels * position.y));
		const auto right = left + unit_size_pixels;
		const auto bottom = top + unit_size_pixels;

		const auto leftScaled = left + scale.x * unit_size_pixels;
		const auto topScaled = top + scale.y * unit_size_pixels;
		const auto rightScaled = right - scale.x * unit_size_pixels;
		const auto bottomScaled = bottom - scale.y * unit_size_pixels;

		const auto rectangle = D2D1::RectF(leftScaled, topScaled, rightScaled, bottomScaled);

		return rectangle;
	}
