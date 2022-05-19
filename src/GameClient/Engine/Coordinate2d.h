#pragma once

namespace GameClient::Engine
{
	/**
	 * \brief 2D integer coordinate.
	 */
	struct Coordinate2d
	{
		int x;
		int y;

		bool operator==(const Coordinate2d& rhs) const = default;
	};

	/**
	 * \brief 2D floating point coordinate.
	 */
	struct Coordinate2dF
	{
		float x;
		float y;

		bool operator==(const Coordinate2dF& rhs) const = default;
	};
}
