#pragma once
#include <memory>

#include "CollisionDetector.h"
#include "ICollidable.h"

namespace GameClient::GameObjects::Collision
{
	/**
	 * \brief Base class of ICollidable.
	 */
	class CollidableBase : public ICollidable // NOLINT(cppcoreguidelines-special-member-functions)
	{
	private:
		std::shared_ptr<CollisionDetector> _collisionDetector;

	protected:
		[[nodiscard]] std::shared_ptr<CollisionDetector> GetCollisionDetector() const;

	public:
		explicit CollidableBase(std::shared_ptr<CollisionDetector> collisionDetector);
		~CollidableBase() override = default;

		CollidableBase() = delete;
		CollidableBase(CollidableBase&) = delete;
		CollidableBase(CollidableBase&&) = delete;

		CollidableName GetCollidableName() override = 0;
		[[nodiscard]] bool IsColliding(int x, int y, CollidableName source) override = 0;
	};
}
