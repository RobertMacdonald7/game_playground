#include "Snake.h"

#include <chrono>

#include "Macros.h"
#include "Direct2dUtility.h"

GameClient::GameObjects::Snake::Snake()
{
	constexpr auto initialSnake = Position{ 2, 2 };
	_segments.push_back(initialSnake);

	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			const auto isBoundary = IsBoundary(x, y);
			_playArea[x][y] = isBoundary ? PlayArea::Wall : PlayArea::BackGround;
		}
	}
}

GameClient::GameObjects::Snake::~Snake()
{
	DiscardDeviceResources();
}

void GameClient::GameObjects::Snake::OnInput(GameClient::Input::Keys pressedKey)
{
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

	_directionInputReceived = false;
}

void GameClient::GameObjects::Snake::Draw(ID2D1HwndRenderTarget* renderTarget)
{
	// TODO - Move "PlayArea" into its own "Drawable" class
	for (auto x = 0; x < game_width_units; ++x)
	{
		for (auto y = 0; y < game_height_units; ++y)
		{
			auto rectangle = GameClient::Utility::Direct2dUtility::CreateUnitRectangle(0, 0, static_cast<FLOAT>(x), static_cast<FLOAT>(y));
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
