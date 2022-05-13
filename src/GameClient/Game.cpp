#include "Game.h"

#include <string>

#include "State/GameStateMachine.h"

GameClient::Game::Game(std::unique_ptr<Engine::IEngine> engine, std::unique_ptr<State::GameStateMachine> stateMachine):
_engine(std::move(engine)),
_stateMachine(std::move(stateMachine))
{
	if (const HRESULT result = _engine->Initialize(); FAILED(result))
	{
		const auto message = "Engine failed to initialize: " + std::to_string(result);
		throw std::exception(message.c_str());
	}
}

GameClient::Game::~Game() = default;

void GameClient::Game::OnResize(const int width, const int height) const
{
	_engine->Resize(width, height);
}

void GameClient::Game::OnInput(const Input::Input input)
{
	switch (input)
	{
	case Input::Input::One:
		_timeStep = std::chrono::milliseconds(_slow);
		break;
	case Input::Input::Two:
		_timeStep = std::chrono::milliseconds(_normal);

		break;
	case Input::Input::Three:
		_timeStep = std::chrono::milliseconds(_fast);
		break;
	default:
		break;
	}
	_stateMachine->OnInput(input);
}

void GameClient::Game::ProcessFrame()
{
	const auto currentTime = std::chrono::steady_clock::now();
	const auto frameTime = currentTime - _lastUpdateTime;
	_accumulatedFrameTime += frameTime;
	_lastUpdateTime = currentTime;
	int numberOfUpdates = 0;

	while (numberOfUpdates < _maxUpdatesPerFrame && _accumulatedFrameTime > _timeStep)
	{
		_accumulatedFrameTime -= _timeStep;
		_stateMachine->OnUpdate();
		++numberOfUpdates;
	}

	_engine->Draw(_stateMachine->GetDrawableEntities());
}
