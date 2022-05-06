#pragma once
namespace GameClient::Input
{
	enum class Keys : int
	{
		None = 0,
		UpArrow = 1 << 0,
		DownArrow = 1 << 1,
		LeftArrow = 1 << 2,
		RightArrow = 1 << 3,
		SpaceBar = 1 << 4
	};
}
