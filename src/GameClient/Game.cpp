#include "Game.h"

#include <string>

GameClient::Game::Game(std::unique_ptr<Engine::IEngine> engine):
_engine(std::move(engine))
{
	const HRESULT result = _engine->Initialize();

	if (FAILED(result))
	{
		const auto message = "Engine failed to initialize: " + std::to_string(result);
		throw std::exception(message.c_str());
	}

	_snake = std::make_shared<GameObjects::Snake>();
}

GameClient::Game::~Game() = default;

void GameClient::Game::OnResize(const UINT width, const UINT height) const
{
	_engine->Resize(width, height);
}

// TODO - use the message loop for this instead?
void GameClient::Game::HandleInput()
{
	auto pressedKey = Input::Keys::None;
	if (GetAsyncKeyState(VK_UP))
	{
		pressedKey = Input::Keys::UpArrow;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		pressedKey = Input::Keys::DownArrow;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		pressedKey = Input::Keys::LeftArrow;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		pressedKey = Input::Keys::RightArrow;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		pressedKey = Input::Keys::SpaceBar;
	}

	_snake->OnInput(pressedKey);

	_previousKey = pressedKey;
}

void GameClient::Game::ProcessFrame()
{
	const auto currentTime = std::chrono::steady_clock::now();
	const auto frameTime = currentTime - _lastUpdateTime;
	_accumulatedFrameTime += frameTime;
	_lastUpdateTime = currentTime;
	unsigned short numberOfUpdates = 0;

	// TODO - Input buffering
	HandleInput();

	while (numberOfUpdates < _maxUpdatesPerFrame && _accumulatedFrameTime > _timeStep)
	{
		_accumulatedFrameTime -= _timeStep;
		_snake->OnUpdate();
		++numberOfUpdates;
	}
	
	_engine->Draw(_snake);
}
