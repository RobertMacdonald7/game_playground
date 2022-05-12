#include "PlayArea.h"

#include <stdexcept>

#include "../Macros.h"

GameClient::GameObjects::PlayArea::PlayArea()
{
	CreatePlayArea();
}

GameClient::GameObjects::PlayArea::~PlayArea()
{
}

void GameClient::GameObjects::PlayArea::Draw(const std::shared_ptr<Engine::IRenderTarget>& renderTarget)
{
	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			const auto colour = GetPlayAreaColour(_playArea[x][y]);
			renderTarget->DrawUnitRectangle({ 0,0 }, { x, y }, { 0, 0 }, colour);
		}
	}

	for (auto x = 0; x < game_width_pixels; x+=unit_size_pixels)
	{
		renderTarget->DrawLine(
			{ static_cast<float>(x), 0.0f },
			{ static_cast<float>(x), static_cast<float>(game_height_pixels) },
			0.2f, Engine::Colour::Gray
		);
	}

	for (auto y = 0; y < game_height_pixels; y+=unit_size_pixels)
	{
		renderTarget->DrawLine(
			{0.0f, static_cast<float>(y) },
			{ static_cast<float>(game_width_pixels), static_cast<float>(y) },
			0.2f, Engine::Colour::Gray
		);
	}
}

GameClient::GameObjects::Collision::CollidableName GameClient::GameObjects::PlayArea::GetCollidableName()
{
	return Collision::CollidableName::PlayArea;
}

bool GameClient::GameObjects::PlayArea::IsColliding(const int x, const int y, Collision::CollidableName source)
{
	// Out of bounds
	if (x < 0 || y < 0 || x > game_width_units || y > game_height_units)
		return true;

	// Wall collision
	if (_playArea[x][y] == PlayAreaTile::Wall)
		return true;

	return false;
}

void GameClient::GameObjects::PlayArea::CreatePlayArea()
{
	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			const auto isBoundary = IsBoundary(x, y);
			_playArea[x][y] = isBoundary ? PlayAreaTile::Wall : PlayAreaTile::BackGround;
		}
	}
}

bool GameClient::GameObjects::PlayArea::IsBoundary(const int x, const int y)
{
	return x == 0 || x == game_width_units - 1 || y == 0 || y == game_height_units - 1;
}

GameClient::Engine::Colour GameClient::GameObjects::PlayArea::GetPlayAreaColour(const PlayAreaTile area)
{
	switch (area)
	{
	case PlayAreaTile::BackGround:
		return Engine::Colour::White;
	case PlayAreaTile::Wall:
		return Engine::Colour::DarkRed;
	default:
		throw std::out_of_range("PlayArea was not a handled value");
	}
}
