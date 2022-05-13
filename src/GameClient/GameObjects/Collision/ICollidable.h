#pragma once

namespace GameClient::GameObjects::Collision
{
	enum class CollidableName : int
	{
		PlayArea = 1 << 0,
		Snake = 1 << 1,
		Food = 1 << 2
	};

	inline CollidableName operator|(CollidableName lhs, CollidableName rhs)
	{
		return static_cast<CollidableName>(
			static_cast<std::underlying_type_t<CollidableName>>(lhs) |
			static_cast<std::underlying_type_t<CollidableName>>(rhs)
		);
	}

	inline CollidableName operator&(CollidableName lhs, CollidableName rhs)
	{
		return static_cast<CollidableName>(
			static_cast<std::underlying_type_t<CollidableName>>(lhs) &
			static_cast<std::underlying_type_t<CollidableName>>(rhs)
		);
	}

	class ICollidable // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~ICollidable() = default;

		virtual CollidableName GetCollidableName() = 0;
		[[nodiscard]] virtual bool IsColliding(int x, int y, CollidableName source) = 0;
	};
}
