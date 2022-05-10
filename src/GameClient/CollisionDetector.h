#pragma once
#include <memory>
#include <vector>

#include "ICollidable.h"

namespace GameClient::GameObjects::Collision
{
	class CollisionDetector
	{
	private:
		static CollisionDetector _instance;
		CollisionDetector() = default;

		std::vector<std::shared_ptr<ICollidable>> _collidables;

	public:
		~CollisionDetector() = default;

		CollisionDetector(CollisionDetector& copyOther) = delete;
		CollisionDetector operator=(CollisionDetector& copyOther) = delete;

		CollisionDetector(CollisionDetector&& moveOther) = delete;
		CollisionDetector operator=(CollisionDetector&& moveOther) = delete;

		static CollisionDetector& GetInstance();

		void AddCollidable(const std::shared_ptr<ICollidable>& collidable);
		bool IsColliding(int x, int y, CollidableName source, CollidableName target);
	};
}
