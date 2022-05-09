#include "Snake.h"

#include <chrono>

#include "Macros.h"
#include "Direct2dUtility.h"
#include "GameStateMachine.h"

GameClient::GameObjects::Snake::Snake(std::shared_ptr<PlayArea> playArea) :
	_playArea(std::move(playArea))
{
	CreatePlayer();
}

GameClient::GameObjects::Snake::~Snake()
{
	DiscardDeviceResources();
}

void GameClient::GameObjects::Snake::OnInput(const Input::Keys pressedKey)
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

void GameClient::GameObjects::Snake::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	for (const auto& segment : _segments)
	{
		auto rectangle = Utility::Direct2dUtility::CreateUnitRectangle(0, 0, static_cast<FLOAT>(segment.x), static_cast<FLOAT>(segment.y));
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

	return result;
}

void GameClient::GameObjects::Snake::DiscardDeviceResources()
{
	SafeRelease(&_snakeBrush);
}

void GameClient::GameObjects::Snake::Reset()
{
	_segments.clear();

	CreatePlayer();

	_direction = Direction::Right;
	_growSnake = 0;
	_directionInputReceived = false;
}

void GameClient::GameObjects::Snake::MoveSnake()
{
	_directionInputReceived = false;


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

	// Calculate the new head position
	const auto& [x, y] = _segments.front();
	const auto newHead = Position{ x + deltaX, y + deltaY };

	// Check collision
	if (IsColliding(newHead.x, newHead.y))
	{
		State::GameStateMachine::GetInstance().ChangeState(State::GameStateType::GameOver);
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

void GameClient::GameObjects::Snake::CreatePlayer()
{
	constexpr auto initialX = 10;
	constexpr auto initialSnakeHead = Position{ initialX, game_height_units / 2 };
	_segments.push_back(initialSnakeHead);

	for (auto x = initialX - 1; x > initialX - 5; --x)
	{
		auto segment = Position{ x, game_height_units / 2 };
		_segments.push_back(segment);
	}
}

bool GameClient::GameObjects::Snake::IsColliding(const int x, const int y)
{
	// PlayArea collision
	if (_playArea->IsColliding(x, y))
	{
		return true;
	}

	// Self collision
	if (const auto findIt = std::ranges::find(_segments, Position{ x, y }); findIt != _segments.end())
		return true;

	return false;
}
