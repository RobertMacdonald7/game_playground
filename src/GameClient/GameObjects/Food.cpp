#include "Food.h"

GameClient::GameObjects::Food::Food(std::shared_ptr<Collision::CollisionDetector> collisionDetector) :
	CollidableBase(std::move(collisionDetector))
{
	// Add this instance to the CollisionDetector
	GetCollisionDetector()->AddCollidable(GetCollidableName(), this);

	// Place a new food
	PlaceFoodAtValidCoordinates();
}

GameClient::GameObjects::Food::~Food()
{
	// Remove this instance from the CollisionDetector
	GetCollisionDetector()->RemoveCollidable(GetCollidableName());
}

bool GameClient::GameObjects::Food::OnInput(const Input::Input input)
{
	if (input == Input::Input::SpaceBar)
	{
		// Reset if space bar was pressed
		Reset();
		return true;
	}
	return false;
}

void GameClient::GameObjects::Food::OnUpdate()
{
	// Place new food if the last one was eaten
	if (_eaten)
	{
		PlaceFoodAtValidCoordinates();
		_eaten = false;
	}
}

void GameClient::GameObjects::Food::Reset()
{
	// Place new food
	PlaceFoodAtValidCoordinates();

	// Reset eaten status
	_eaten = false;
}

void GameClient::GameObjects::Food::Draw(Engine::IRender& renderEngine)
{
	// Draw a simple square to represent food
	renderEngine.FillUnitRectangle({0, 0}, _coordinates, {0.1f, 0.1f}, Engine::Colour::Green);
}

GameClient::GameObjects::Collision::CollidableName GameClient::GameObjects::Food::GetCollidableName()
{
	return Collision::CollidableName::Food;
}

bool GameClient::GameObjects::Food::IsColliding(const int x, const int y, const Collision::CollidableName source)
{
	const auto isColliding = x == _coordinates.x && y == _coordinates.y;

	if (isColliding && static_cast<bool>(source & Collision::CollidableName::Snake))
	{
		// If the snake is colliding, the food has been eaten
		_eaten = true;
	}
	return isColliding;
}

void GameClient::GameObjects::Food::PlaceFoodAtValidCoordinates()
{
	auto validCoordinates = false;
	auto x = 0;
	auto y = 0;

	// Generate random coordinates until it no longer collides with anything
	while (!validCoordinates)
	{
		x = _xDistribution(_rng);
		y = _yDistribution(_rng);

		validCoordinates = !GetCollisionDetector()->IsColliding(
			x, y, GetCollidableName(),
			Collision::CollidableName::PlayArea | Collision::CollidableName::Snake
		);
	}

	_coordinates = {x, y};
}
