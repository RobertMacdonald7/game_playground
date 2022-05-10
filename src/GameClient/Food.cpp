#include "Food.h"

#include "CollisionDetector.h"
#include "Direct2dUtility.h"
#include "Macros.h"

GameClient::GameObjects::Food::Food()
{
	PlaceFoodAtValidCoordinates();
}

GameClient::GameObjects::Food::~Food()
{
	DiscardDeviceResources();
}

void GameClient::GameObjects::Food::OnUpdate()
{
	if (_eaten)
	{
		PlaceFoodAtValidCoordinates();
	}
}

bool GameClient::GameObjects::Food::OnInput(const Input::Keys keysDown)
{
	if (static_cast<int>(keysDown) & static_cast<int>(Input::Keys::SpaceBar))
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

void GameClient::GameObjects::Food::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	const auto x = static_cast<FLOAT>(_coordinates.first);
	const auto y = static_cast<FLOAT>(_coordinates.second);
	const auto rectangle = Utility::Direct2dUtility::CreateUnitRectangle(0, 0, x, y, .1f, .1f);
	renderTarget->FillRectangle(&rectangle, _foodBrush);
}

HRESULT GameClient::GameObjects::Food::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	auto result = S_OK;
	if (!_foodBrush)
	{
		result = renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &_foodBrush);
		RETURN_FAILED_HRESULT(result);
	}

	return result;
}

void GameClient::GameObjects::Food::DiscardDeviceResources()
{
	SafeRelease(&_foodBrush);
}

GameClient::GameObjects::Collision::CollidableName GameClient::GameObjects::Food::GetCollidableName()
{
	return Collision::CollidableName::Food;
}

bool GameClient::GameObjects::Food::IsColliding(const int x, const int y, const Collision::CollidableName source)
{
	const auto isColliding = x == _coordinates.first && y == _coordinates.second;

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

	UINT x = 0;
	UINT y = 0;
	while (!validCoordinates)
	{
		x = _xDistribution(_rng);
		y = _yDistribution(_rng);

		validCoordinates = !Collision::CollisionDetector::GetInstance()
		.IsColliding(
			x, y, GetCollidableName(),
			Collision::CollidableName::PlayArea | Collision::CollidableName::Snake
		);
	}
	
	_coordinates = { x, y };
	_eaten = false;
}
