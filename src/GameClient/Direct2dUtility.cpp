#include "Direct2dUtility.h"

#include <stdexcept>

#include "GameDefinitions.h"

	D2D1_RECT_F GameClient::Utility::Direct2dUtility::CreateUnitRectangle(FLOAT xOffset, FLOAT yOffset, FLOAT x, FLOAT y, FLOAT xScale, FLOAT yScale)
	{
		// TODO - Make scale actually "scale" rather than add/subtract a multiple of unit_size_pixels;
		if (!(xScale >= 0 && xScale < .5f) || !(yScale >= 0 && yScale < .5f))
		{
			throw std::out_of_range("Scaling factor was not valid");
		}

		const auto left = xOffset + (unit_size_pixels * x);
		const auto top = yOffset + (unit_size_pixels * y);
		const auto right = left + unit_size_pixels;
		const auto bottom = top + unit_size_pixels;

		const auto leftScaled = left + xScale * unit_size_pixels;
		const auto topScaled = top + yScale * unit_size_pixels;
		const auto rightScaled = right - xScale * unit_size_pixels;
		const auto bottomScaled = bottom - yScale * unit_size_pixels;

		const auto rectangle = D2D1::RectF(leftScaled, topScaled, rightScaled, bottomScaled);

		return rectangle;
	}
