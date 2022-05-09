#pragma once
#include <chrono>
#include <d2d1.h>
#include <vector>

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

	class Snake final : public Engine::IDrawable
	{
	private:
		Direction _direction = Direction::Right;
		std::vector<Position> _segments;
		ID2D1SolidColorBrush* _snakeBrush = nullptr;

		const std::shared_ptr<PlayArea> _playArea;

		int _growSnake = 0;
		bool _directionInputReceived = false;

	public:
		explicit Snake(std::shared_ptr<PlayArea> playArea);
		~Snake() override;

		Snake(Snake& copyOther) = delete;
		Snake operator=(Snake& copyOther) = delete;

		Snake(Snake&& moveOther) = delete;
		Snake operator=(Snake&& moveOther) = delete;

		void OnInput(Input::Keys pressedKey);
		void OnUpdate();

		void Draw(ID2D1HwndRenderTarget* renderTarget) override;
		HRESULT CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) override;
		void DiscardDeviceResources() override;

		void Reset();

	private:
		void MoveSnake();
		void CreatePlayer();
		bool IsColliding(int x, int y);
	};
	
}
