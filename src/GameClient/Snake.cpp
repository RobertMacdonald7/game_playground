#include "Snake.h"

#include <chrono>

#include "CollisionDetector.h"
#include "Macros.h"
#include "Direct2dUtility.h"
#include "GameStateMachine.h"

GameClient::GameObjects::Snake::Snake()
{
	CreatePlayer();
}

GameClient::GameObjects::Snake::~Snake()
{
	DiscardDeviceResources();
}

bool GameClient::GameObjects::Snake::OnInput(const Input::Keys pressedKey)
{
	switch (pressedKey)
	{
	case Input::Keys::UpArrow:
		if (_direction == Direction::Down) return false;
		_direction = Direction::Up;
		break;
	case Input::Keys::DownArrow:
		if (_direction == Direction::Up) return false;
		_direction = Direction::Down;
		break;
	case Input::Keys::LeftArrow:
		if (_direction == Direction::Right) return false;
		_direction = Direction::Left;
		break;
	case Input::Keys::RightArrow:
		if (_direction == Direction::Left) return false;
		_direction = Direction::Right;
		break;
	case Input::Keys::SpaceBar:
		Reset();
		break;
	case Input::Keys::None:
	default:
		return false;
	}

	return true;
}

void GameClient::GameObjects::Snake::OnUpdate()
{
	if (_growNextUpdate)
	{
		++_growSnake;
		_growNextUpdate = false;
	}

	MoveSnake();
}

void GameClient::GameObjects::Snake::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	for (const auto& segment : _segments)
	{
		auto rectangle = Utility::Direct2dUtility::CreateUnitRectangle(0, 0, static_cast<FLOAT>(segment.x), static_cast<FLOAT>(segment.y), 0, 0);
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
}

GameClient::GameObjects::Collision::CollidableName GameClient::GameObjects::Snake::GetCollidableName()
{
	return Collision::CollidableName::Snake;
}

bool GameClient::GameObjects::Snake::AteFood(const int x, const int y)
{
	return Collision::CollisionDetector::GetInstance().IsColliding(x, y, GetCollidableName(), Collision::CollidableName::Food);
}

void GameClient::GameObjects::Snake::MoveSnake()
{
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
	if (Collision::CollisionDetector::GetInstance().IsColliding(newHead.x, newHead.y, GetCollidableName(), Collision::CollidableName::PlayArea | Collision::CollidableName::Snake))
	{
		State::GameStateMachine::GetInstance().ChangeState(State::GameStateType::GameOver);
		return;
	}

	if (AteFood(newHead.x, newHead.y))
	{
		_growNextUpdate = true;
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

bool GameClient::GameObjects::Snake::IsColliding(const int x, const int y, Collision::CollidableName source)
{
	if (const auto findIt = std::ranges::find(_segments, Position{ x, y }); findIt != _segments.end())
		return true;

	return false;
}
