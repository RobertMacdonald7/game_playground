#pragma once
#include <chrono>
#include <vector>

#include "../Engine/IDrawable.h"
#include "../Input/Input.h"
#include "../Engine/Coordinate2d.h"
#include "../State/IStateMachine.h"
#include "Collision/CollidableBase.h"

namespace GameClient::GameObjects
{
	class Snake final : public Engine::IDrawable, public Collision::CollidableBase
	{
	private:
		enum class Direction
		{
			Up,
			Down,
			Left,
			Right
		};

		Direction _direction = Direction::Right;
		std::vector<Engine::Coordinate2d> _segments;

		bool _growNextUpdate = false;
		int _growSnake = 0;

	public:
		explicit Snake(std::shared_ptr<Collision::CollisionDetector> collisionDetector);
		~Snake() override;

		Snake() = delete;
		Snake(Snake& copyOther) = delete;
		Snake operator=(Snake& copyOther) = delete;

		Snake(Snake&& moveOther) = delete;
		Snake operator=(Snake&& moveOther) = delete;

		bool OnInput(Input::Input input);
		void OnUpdate(State::IStateMachine& context);

		void Draw(const std::shared_ptr<Engine::IRenderTarget>& renderTarget) override;

		void Reset();

		Collision::CollidableName GetCollidableName() override;
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		bool AteFood(int x, int y);
		void MoveSnake(State::IStateMachine& context);
		void CreatePlayer();
	};
	
}
