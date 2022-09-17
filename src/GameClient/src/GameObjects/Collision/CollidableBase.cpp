#include "CollidableBase.h"

std::shared_ptr<GameClient::GameObjects::Collision::CollisionDetector>
GameClient::GameObjects::Collision::CollidableBase::GetCollisionDetector() const
{
	return _collisionDetector;
}

GameClient::GameObjects::Collision::CollidableBase::CollidableBase(
	std::shared_ptr<CollisionDetector> collisionDetector) :
	_collisionDetector(std::move(collisionDetector))
{
}
