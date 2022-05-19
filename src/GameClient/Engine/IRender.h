#pragma once

#include "Colour.h"
#include "Coordinate2d.h"

namespace GameClient::Engine
{
	/**
	 * \brief Interface for the engine's render methods.
	 */
	class IRender // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IRender() = default;

		/**
		 * \brief Draws a unit rectangle.
		 * \param offset X,Y offset from the rectangle's position.
		 * \param position X,Y position of the rectangle's top-left corner.
		 * \param scale How much vertical/horizontal space to shrink the rectangle.
		 * \param colour The colour of the filled rectangle.
		 */
		virtual void DrawUnitRectangle(Coordinate2d offset, Coordinate2d position, Coordinate2dF scale,
									   Colour colour) = 0;

		/**
		 * \brief Draws a line.
		 * \param p0 The first point of the line.0
		 * \param p1 The second point of the line.
		 * \param strokeWidth The width of the line.
		 * \param colour The colour of the line.
		 */
		virtual void DrawLine(Coordinate2dF p0, Coordinate2dF p1, float strokeWidth, Colour colour) = 0;

		virtual void DrawString() = 0;
	};
}
