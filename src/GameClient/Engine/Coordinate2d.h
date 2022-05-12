#pragma once

namespace GameClient::Engine {
	struct Coordinate2d
	{
		int x;
		int y;

		bool operator==(const Coordinate2d& rhs) const = default;
	};

	struct Coordinate2dF
	{
		float x;
		float y;

		bool operator==(const Coordinate2dF& rhs) const = default;
	};
}
