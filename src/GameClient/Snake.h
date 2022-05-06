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

		int _growSnake = 5;

		bool _directionInputReceived = false;

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

	private:
		static bool IsBoundary(int x, int y);
		ID2D1SolidColorBrush* GetPlayAreaBrush(PlayArea area) const;
	};
	
}
