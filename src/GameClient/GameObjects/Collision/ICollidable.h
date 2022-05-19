#pragma once

namespace GameClient::GameObjects::Collision
{
	/**
	 * \brief Names of each collidable object. Uses enum flag notation/values.
	 */
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

	/**
	 * \brief Interface for game objects with collision.
	 */
	class ICollidable // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~ICollidable() = default;

		/**
		 * \brief Gets the name of the collidable object.
		 * \return The name of the collidable object.
		 */
		virtual CollidableName GetCollidableName() = 0;

		/**
		 * \brief Checks if the given coordinates collide with this ICollidable object.
		 * \param x The X coordinate to check collision.
		 * \param y The Y coordinate to check collision.
		 * \param source The source's name making the request.
		 * \return Whether X,Y is colliding.
		 */
		[[nodiscard]] virtual bool IsColliding(int x, int y, CollidableName source) = 0;
	};
}
