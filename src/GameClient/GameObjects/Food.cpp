#include "Food.h"

GameClient::GameObjects::Food::Food(std::shared_ptr<Collision::CollisionDetector> collisionDetector) :
CollidableBase(std::move(collisionDetector))
{
	GetCollisionDetector()->AddCollidable(GetCollidableName(), this);
	PlaceFoodAtValidCoordinates();
}

GameClient::GameObjects::Food::~Food()
{
	GetCollisionDetector()->RemoveCollidable(GetCollidableName());
}

void GameClient::GameObjects::Food::OnUpdate()
{
	if (_eaten)
	{
		PlaceFoodAtValidCoordinates();
	}
}

bool GameClient::GameObjects::Food::OnInput(const Input::Input input)
{
	if (input == Input::Input::SpaceBar)
	{
		Reset();
		return true;
	}
	return false;
}

void GameClient::GameObjects::Food::Reset()
{
	PlaceFoodAtValidCoordinates();
}

void GameClient::GameObjects::Food::Draw(const std::shared_ptr<Engine::IRenderTarget>& renderTarget)
{
	renderTarget->DrawUnitRectangle({ 0,0 }, _coordinates, { 0.1f, 0.1f }, Engine::Colour::Green);
}

GameClient::GameObjects::Collision::CollidableName GameClient::GameObjects::Food::GetCollidableName()
{
	return Collision::CollidableName::Food;
}

bool GameClient::GameObjects::Food::IsColliding(const int x, const int y, const Collision::CollidableName source)
{
	const auto isColliding = x == _coordinates.x && y == _coordinates.y;

	// Check if the snake has eaten me
	if (isColliding && static_cast<bool>(source & Collision::CollidableName::Snake))
	{
		_eaten = true;
	}
	return isColliding;
}

void GameClient::GameObjects::Food::PlaceFoodAtValidCoordinates()
{
	auto validCoordinates = false;

	auto x = 0;
	auto y = 0;
	while (!validCoordinates)
	{
		x = _xDistribution(_rng);
		y = _yDistribution(_rng);

		validCoordinates = !GetCollisionDetector()->IsColliding(
			x, y, GetCollidableName(),
			Collision::CollidableName::PlayArea | Collision::CollidableName::Snake
		);
	}
	
	_coordinates = { x, y };
	_eaten = false;
}
