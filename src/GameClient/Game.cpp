#include "Game.h"

#include <string>

GameClient::Game::Game(std::unique_ptr<Engine::IEngine> engine):
_engine(std::move(engine))
{
	const HRESULT result = _engine->Initialize();

	if (FAILED(result))
	{
		const auto message = "Engine failed to initialize: " + std::to_string(result);
		// TODO - More precise exception
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

	const auto keyChanged = _previousKey != pressedKey;
	_snake->OnInput(pressedKey, keyChanged);

	_previousKey = pressedKey;
}

void GameClient::Game::ProcessFrame()
{
	const auto currentTime = std::chrono::steady_clock::now();
	const auto frameTime = currentTime - _lastUpdateTime;
	_accumulatedFrameTime += frameTime;
	_lastUpdateTime = currentTime;
	unsigned short numberOfUpdates = 0;

	while (numberOfUpdates < _maxUpdatesPerFrame && _accumulatedFrameTime > _timeStep)
	{
		_accumulatedFrameTime -= _timeStep;

		HandleInput();
		_snake->OnUpdate();

		++numberOfUpdates;
	}
	
	_engine->Draw(_snake);
}
