#pragma once
#include <chrono>
#include <d2d1.h>
#include <vector>

#include "Food.h"
#include "ICollidable.h"
#include "IDrawable.h"
#include "Keys.h"
#include "PlayArea.h"

namespace GameClient::GameObjects
{
	struct Position
	{
		int x;
		int y;

		bool operator==(const Position& rhs) const = default;
	};

	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	class Snake final : public Engine::IDrawable, public Collision::ICollidable
	{
	private:
		Direction _direction = Direction::Right;
		std::vector<Position> _segments;
		ID2D1SolidColorBrush* _snakeBrush = nullptr;

		bool _growNextUpdate = false;
		int _growSnake = 0;

	public:
		Snake();
		~Snake() override;

		Snake(Snake& copyOther) = delete;
		Snake operator=(Snake& copyOther) = delete;

		Snake(Snake&& moveOther) = delete;
		Snake operator=(Snake&& moveOther) = delete;

		bool OnInput(Input::Keys pressedKey);
		void OnUpdate();

		void Draw(ID2D1HwndRenderTarget* renderTarget) override;
		HRESULT CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) override;
		void DiscardDeviceResources() override;

		void Reset();

		Collision::CollidableName GetCollidableName() override;
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		bool AteFood(int x, int y);
		void MoveSnake();
		void CreatePlayer();
	};
	
}
