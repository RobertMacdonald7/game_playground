#pragma once
#include <chrono>
#include <d2d1.h>
#include <vector>

#include "GameDefinitions.h"
#include "Keys.h"

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

	enum class PlayArea {
		BackGround,
		Wall
	};

	class Snake
	{
	private:
		std::vector<std::vector<PlayArea>> _playArea{game_width_units, std::vector<PlayArea>(game_height_units)};

		Direction _direction = Direction::Right;
		std::vector<Position> _segments;

		ID2D1SolidColorBrush* _snakeBrush = nullptr;
		ID2D1SolidColorBrush* _playAreaBrush = nullptr;
		ID2D1SolidColorBrush* _playAreaBoundaryBrush = nullptr;

		int _growSnake = 0;

		bool _directionInputReceived = false;
		bool _gameOver = false;

	public:
		Snake();
		~Snake();
		void OnInput(Input::Keys pressedKey);

		Snake(Snake& copyOther) = delete;
		Snake operator=(Snake& copyOther) = delete;

		Snake(Snake&& moveOther) = delete;
		Snake operator=(Snake&& moveOther) = delete;

		void OnUpdate();

		//TEMP, use an interface for "Updatable"
		void MoveSnake();

		void Draw(ID2D1HwndRenderTarget* renderTarget);

		HRESULT CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget);

		void DiscardDeviceResources();

		void Reset();

	private:
		void CreatePlayer();
		void CreatePlayArea();
		static bool IsBoundary(int x, int y);
		[[nodiscard]] ID2D1SolidColorBrush* GetPlayAreaBrush(PlayArea area) const;
		bool IsColliding(int x, int y);
	};
	
}
