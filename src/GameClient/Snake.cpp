#include "Snake.h"

#include <chrono>

#include "GameDefinitions.h"
#include "Macros.h"

GameClient::GameObjects::Snake::Snake()
{
	constexpr auto initialSnake = Position{ 2, 2 };
	_segments.push_back(initialSnake);
}

GameClient::GameObjects::Snake::~Snake()
{
	DiscardDeviceResources();
}

void GameClient::GameObjects::Snake::OnUpdate()
{
	// Game speed dependent updates!
	const auto now = std::chrono::steady_clock::now();
	if (const auto nextUpdate = _lastUpdateTime + _tickRateMs; now > nextUpdate)
	{
		MoveSnake();
		_lastUpdateTime = now;
	}

	// Game speed independent updates!
	// CHECK COLLISION HERE
}

void GameClient::GameObjects::Snake::MoveSnake()
{
	const Position& headPosition = _segments.front();

	int deltaX = 0;
	int deltaY = 0;
	switch (_direction)
	{
	case Direction::Right:
		++deltaX;
		break;
	case Direction::Down:
		++deltaY;
		break;
	case Direction::Left:
		--deltaX;
		break;
	case Direction::Up:
		--deltaY;
		break;
	}

	const auto newHead = Position{ headPosition.x + deltaX, headPosition.y + deltaY };
	_segments.insert(_segments.begin(), newHead);

	// If we need to grow the snake don't pop the back element.
	if (_growSnake > 0)
	{
		--_growSnake;
	}
	else
	{
		_segments.pop_back();
	}
}

void GameClient::GameObjects::Snake::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	for (auto x = 0; x < GRID_SIZE; ++x)
	{
		for (auto y = 0; y < GRID_SIZE; ++y)
		{
			auto rectangle = D2D1::RectF(UNIT_SIZE * x, UNIT_SIZE * y, UNIT_SIZE * x + UNIT_SIZE, UNIT_SIZE * y + UNIT_SIZE);
			renderTarget->FillRectangle(&rectangle, _playAreaBrush);
		}
	}

	for (const auto& segment : _segments)
	{
		auto rectangle = D2D1::RectF(UNIT_SIZE * segment.x, UNIT_SIZE * segment.y, UNIT_SIZE * segment.x + UNIT_SIZE, UNIT_SIZE * segment.y + UNIT_SIZE);
		renderTarget->FillRectangle(&rectangle, _snakeBrush);
	}
}

HRESULT GameClient::GameObjects::Snake::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	HRESULT result = S_OK;
	if (!_snakeBrush)
	{
		result = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &_snakeBrush);
		RETURN_FAILED_HRESULT(result);
	}

	if (!_playAreaBrush)
	{
		result = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &_playAreaBrush);
		RETURN_FAILED_HRESULT(result);
	}

	return result;
}

void GameClient::GameObjects::Snake::DiscardDeviceResources()
{
	SafeRelease(&_snakeBrush);
}
