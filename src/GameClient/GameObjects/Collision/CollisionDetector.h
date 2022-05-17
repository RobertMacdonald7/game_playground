#pragma once
#include <map>

#include "ICollidable.h"

namespace GameClient::GameObjects::Collision
{
	/**
	 * \brief Class that provides functionality to test collision between multiple ICollidable objects.
	 */
	class CollisionDetector
	{
	private:
		std::map<CollidableName, ICollidable*> _collidables;

	public:
		CollisionDetector() = default;
		~CollisionDetector() = default;

		CollisionDetector(CollisionDetector& copyOther) = delete;
		CollisionDetector operator=(CollisionDetector& copyOther) = delete;

		CollisionDetector(CollisionDetector&& moveOther) = delete;
		CollisionDetector operator=(CollisionDetector&& moveOther) = delete;

		/**
		 * \brief Adds an ICollidable.
		 * \param name The unique name of the ICollidable object.
		 * \param collidable Non-owning pointer to the ICollidable object.
		 */
		void AddCollidable(CollidableName name, ICollidable* collidable);

		/**
		 * \brief Removes an ICollidable.
		 * \param name The name of the ICollidable to remove.
		 */
		void RemoveCollidable(CollidableName name);

		/**
		 * \brief Tests collision of the provided coordinates and the target's coordinates.
		 * \param x The X coordinate of the object requesting the collision check.
		 * \param y The Y coordinate of the object requesting the collision check.
		 * \param source The name of the ICollidable object requesting the collision check.
		 * \param target The ICollidable to check collision with (can be multiple).
		 * \return Whether X,Y is colliding with the target.
		 */
		bool IsColliding(int x, int y, CollidableName source, CollidableName target);
	};
}
