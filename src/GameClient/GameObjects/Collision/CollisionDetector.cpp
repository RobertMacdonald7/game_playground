#include "CollisionDetector.h"

#include <algorithm>

GameClient::GameObjects::Collision::CollisionDetector GameClient::GameObjects::Collision::CollisionDetector::_instance;


GameClient::GameObjects::Collision::CollisionDetector& GameClient::GameObjects::Collision::CollisionDetector::GetInstance()
{
	return _instance;
}

void GameClient::GameObjects::Collision::CollisionDetector::AddCollidable(const std::shared_ptr<ICollidable>& collidable)
{
	_collidables.push_back(collidable);
}

bool GameClient::GameObjects::Collision::CollisionDetector::IsColliding(int x, int y, CollidableName source, CollidableName target)
{
	const auto isColliding = std::ranges::any_of(_collidables, [x, y, source, target](const std::shared_ptr<ICollidable>& collidable) {
		// Don't check collision with collidables that aren't part of the target
		if (const auto collidableName = collidable->GetCollidableName(); !static_cast<bool>(target & collidableName))
		{
			return false;
		}

		return collidable->IsColliding(x, y, source);
	});

	return isColliding;
}
