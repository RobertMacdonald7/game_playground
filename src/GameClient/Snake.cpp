#include "Snake.h"

#include <chrono>

#include "Macros.h"
#include "Direct2dUtility.h"

GameClient::GameObjects::Snake::Snake()
{
	CreatePlayer();
	CreatePlayArea();
}

GameClient::GameObjects::Snake::~Snake()
{
	DiscardDeviceResources();
}

void GameClient::GameObjects::Snake::OnInput(GameClient::Input::Keys pressedKey)
{
	if (pressedKey == Input::Keys::SpaceBar)
	{
		Reset();
	}

	// Can't change the snake's direction if it has already been changed and hasn't moved yet.
	if (_directionInputReceived)
		return;

	switch (pressedKey)  // NOLINT(clang-diagnostic-switch-enum)
	{
	case Input::Keys::UpArrow:
		if (_direction == Direction::Down) break;
		_direction = Direction::Up;
		_directionInputReceived = true;
		break;
	case Input::Keys::DownArrow:
		if (_direction == Direction::Up) break;
		_direction = Direction::Down;
		_directionInputReceived = true;
		break;
	case Input::Keys::LeftArrow:
		if (_direction == Direction::Right) break;
		_direction = Direction::Left;
		_directionInputReceived = true;
		break;
	case Input::Keys::RightArrow:
		if (_direction == Direction::Left) break;
		_direction = Direction::Right;
		_directionInputReceived = true;
		break;
	default:
		break;
	}
}

void GameClient::GameObjects::Snake::OnUpdate()
{
	MoveSnake();
}

void GameClient::GameObjects::Snake::MoveSnake()
{
	_directionInputReceived = false;

	// TODO - replace this with a "game over" state.
	if (_gameOver)
	{
		return;
	}
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
	default:
		throw std::out_of_range("Direction was not a handled value");
	}

	const auto newHead = Position{ headPosition.x + deltaX, headPosition.y + deltaY };

	if (const auto isColliding = IsColliding(newHead.x, newHead.y))
	{
		_gameOver = true;
		return;
	}

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
	// TODO - Move "PlayArea" into its own "Drawable" class
	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			auto rectangle = GameClient::Utility::Direct2dUtility::CreateUnitRectangle(
				0, 0, static_cast<FLOAT>(x), static_cast<FLOAT>(y));
			const auto brush = GetPlayAreaBrush(_playArea[x][y]);
			renderTarget->FillRectangle(&rectangle, brush);
		}
	}

	for (const auto& segment : _segments)
	{
		auto rectangle = GameClient::Utility::Direct2dUtility::CreateUnitRectangle(0, 0, static_cast<FLOAT>(segment.x), static_cast<FLOAT>(segment.y));
		renderTarget->FillRectangle(&rectangle, _snakeBrush);
	}
}

HRESULT GameClient::GameObjects::Snake::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	auto result = S_OK;
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

	if (!_playAreaBoundaryBrush)
	{
		result = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &_playAreaBoundaryBrush);
		RETURN_FAILED_HRESULT(result);
	}

	return result;
}

void GameClient::GameObjects::Snake::DiscardDeviceResources()
{
	SafeRelease(&_snakeBrush);
	SafeRelease(&_playAreaBrush);
	SafeRelease(&_playAreaBoundaryBrush);
}

void GameClient::GameObjects::Snake::Reset()
{
	_segments.clear();

	CreatePlayer();

	_direction = Direction::Right;
	_growSnake = 0;
	_directionInputReceived = false;
	_gameOver = false;
}

void GameClient::GameObjects::Snake::CreatePlayer()
{
	constexpr auto initialX = 10;
	constexpr auto initialSnakeHead = Position{ initialX, game_height_units/2 };
	_segments.push_back(initialSnakeHead);

	for(auto x = initialX - 1; x > initialX - 5; --x)
	{
		auto segment = Position{ x, game_height_units / 2 };
		_segments.push_back(segment);
	}
}

void GameClient::GameObjects::Snake::CreatePlayArea()
{
	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			const auto isBoundary = IsBoundary(x, y);
			_playArea[x][y] = isBoundary ? PlayArea::Wall : PlayArea::BackGround;
		}
	}
}

bool GameClient::GameObjects::Snake::IsBoundary(const int x, const int y)
{
	return x == 0 || x == game_width_units - 1 || y == 0 || y == game_height_units - 1;
}

ID2D1SolidColorBrush* GameClient::GameObjects::Snake::GetPlayAreaBrush(const PlayArea area) const
{
	switch (area)
	{
	case PlayArea::BackGround:
		return _playAreaBrush;
	case PlayArea::Wall:
		return _playAreaBoundaryBrush;
	default:
		throw std::out_of_range("PlayArea was not a handled value");
	}
}

bool GameClient::GameObjects::Snake::IsColliding(const int x, const int y)
{
	// Out of bounds
	if (x < 0 || y < 0 || x > game_width_units || y > game_height_units)
		return true;

	// Self collision
	const auto findIt = std::ranges::find(_segments, Position{x, y});
	if (auto isCollidingWithSelf = findIt != _segments.end())
		return true;

	// Wall collision
	if (_playArea[x][y] == PlayArea::Wall)
		return true;

	return false;
}
