#pragma once
#include <random>

#include "../GameDefinitions.h"
#include "../Engine/IDrawable.h"
#include "../Input/Input.h"
#include "Collision/CollidableBase.h"

namespace GameClient::GameObjects
{
	/**
	 * \brief Defines a "food" game object used for growing the snake and calculating game score.
	 */
	class Food final : public Engine::IDrawable, public Collision::CollidableBase
	{
	private:
		Engine::Coordinate2d _coordinates{0, 0};
		bool _eaten = false;
		std::mt19937 _rng{std::random_device{}()};
		std::uniform_int_distribution<int> _xDistribution{1, game_width_units - 2};
		std::uniform_int_distribution<int> _yDistribution{1, game_height_units - 2};

	public:
		explicit Food(std::shared_ptr<Collision::CollisionDetector> collisionDetector);
		~Food() override;
		void OnUpdate();
		bool OnInput(Input::Input input);

		Food() = delete;
		Food(Food& copyOther) = delete;
		Food operator=(Food& copyOther) = delete;

		Food(Food&& moveOther) = delete;
		Food operator=(Food&& moveOther) = delete;

		/**
		 * \brief Reset's the object's state.
		 */
		void Reset();

		void Draw(const std::shared_ptr<Engine::IRenderTarget>& renderTarget) override;

		Collision::CollidableName GetCollidableName() override;
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		/**
		 * \brief Generates a random, non-colliding, 2D coordinate to place the food at.
		 */
		void PlaceFoodAtValidCoordinates();
	};
}
