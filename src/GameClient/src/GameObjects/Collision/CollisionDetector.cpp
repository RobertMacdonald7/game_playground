#include "CollisionDetector.h"

#include <algorithm>

void GameClient::GameObjects::Collision::CollisionDetector::AddCollidable(
	const CollidableName name, ICollidable* collidable)
{
	_collidables[name] = collidable;
}

void GameClient::GameObjects::Collision::CollisionDetector::RemoveCollidable(const CollidableName name)
{
	_collidables.erase(name);
}

bool GameClient::GameObjects::Collision::CollisionDetector::IsColliding(int x, int y, CollidableName source,
                                                                        CollidableName target)
{
	// Check if we're colliding with ANY of the targets
	const auto isColliding = std::ranges::any_of(_collidables, [x, y, source, target](auto collidable)
	{
		// Don't check collision with collidables that aren't part of the target
		if (!static_cast<bool>(target & collidable.first))
		{
			return false;
		}

		// Ask if we're colliding with the target
		return collidable.second->IsColliding(x, y, source);
	});

	return isColliding;
}
