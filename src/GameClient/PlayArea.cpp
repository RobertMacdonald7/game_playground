#include "PlayArea.h"

#include <stdexcept>

#include "Direct2dUtility.h"
#include "Macros.h"

GameClient::GameObjects::PlayArea::PlayArea()
{
	CreatePlayArea();
}

GameClient::GameObjects::PlayArea::~PlayArea()
{
	DiscardDeviceResources();
}

void GameClient::GameObjects::PlayArea::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			auto rectangle = Utility::Direct2dUtility::CreateUnitRectangle(
				0, 0, static_cast<FLOAT>(x), static_cast<FLOAT>(y), 0, 0);
			const auto brush = GetPlayAreaBrush(_playArea[x][y]);
			renderTarget->FillRectangle(&rectangle, brush);
		}
	}
}

HRESULT GameClient::GameObjects::PlayArea::CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget)
{
	auto result = S_OK;
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

void GameClient::GameObjects::PlayArea::DiscardDeviceResources()
{
	SafeRelease(&_playAreaBrush);
	SafeRelease(&_playAreaBoundaryBrush);
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

ID2D1SolidColorBrush* GameClient::GameObjects::PlayArea::GetPlayAreaBrush(const PlayAreaTile area) const
{
	switch (area)
	{
	case PlayAreaTile::BackGround:
		return _playAreaBrush;
	case PlayAreaTile::Wall:
		return _playAreaBoundaryBrush;
	default:
		throw std::out_of_range("PlayArea was not a handled value");
	}
}
