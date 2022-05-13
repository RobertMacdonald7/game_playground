#pragma once
#include <map>

#include "ICollidable.h"

namespace GameClient::GameObjects::Collision
{
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

		void AddCollidable(CollidableName name, ICollidable* collidable);
		void RemoveCollidable(CollidableName name);
		bool IsColliding(int x, int y, CollidableName source, CollidableName target);
	};
}
