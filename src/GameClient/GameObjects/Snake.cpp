#include "Snake.h"

#include <chrono>

#include "Collision/CollisionDetector.h"
#include "../State/GameStateMachine.h"

GameClient::GameObjects::Snake::Snake()
{
	CreatePlayer();
}

bool GameClient::GameObjects::Snake::OnInput(const Input::Input input)
{
	if (input == Input::Input::SpaceBar)
	{
		Reset();
		return true;
	}
#ifdef _DEBUG
	if (input == Input::Input::G)
	{
		_growNextUpdate = true;
	}
#endif
	const auto originalDirection = _direction;
	switch (input)
	{
	case Input::Input::Up:
		if (_direction == Direction::Down) return false;
		_direction = Direction::Up;
		break;
	case Input::Input::Down:
		if (_direction == Direction::Up) return false;
		_direction = Direction::Down;
		break;
	case Input::Input::Left:
		if (_direction == Direction::Right) return false;
		_direction = Direction::Left;
		break;
	case Input::Input::Right:
		if (_direction == Direction::Left) return false;
		_direction = Direction::Right;
		break;
	default:
		return false;
	}

	return _direction != originalDirection;
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

void GameClient::GameObjects::Snake::Draw(const std::shared_ptr<Engine::IRenderTarget>& renderTarget)
{
	for (const auto& segment : _segments)
	{
		renderTarget->DrawUnitRectangle({0, 0}, segment, {0, 0}, Engine::Colour::Blue);
	}
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
	const auto newHead = Engine::Coordinate2d{ x + deltaX, y + deltaY };

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
	constexpr auto initialSnakeHead = Engine::Coordinate2d{ initialX, game_height_units / 2 };
	_segments.push_back(initialSnakeHead);

	for (auto x = initialX - 1; x > initialX - 5; --x)
	{
		auto segment = Engine::Coordinate2d{ x, game_height_units / 2 };
		_segments.push_back(segment);
	}
}

bool GameClient::GameObjects::Snake::IsColliding(const int x, const int y, Collision::CollidableName source)
{
	if (const auto findIt = std::ranges::find(_segments, Engine::Coordinate2d{ x, y }); findIt != _segments.end())
		return true;

	return false;
}
