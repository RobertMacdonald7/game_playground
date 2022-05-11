#include "GameStateMachine.h"

#include <stdexcept>

GameClient::State::GameStateMachine GameClient::State::GameStateMachine::_instance;

GameClient::State::GameStateMachine::GameStateMachine()
{
	_playingState = std::make_shared<Playing>();
	_gameOverState = std::make_shared<GameOver>();

	ChangeState(GameStateType::Playing);
}

void GameClient::State::GameStateMachine::OnInput(const Input::Input input) const
{
	_currentState->OnInput(input);
}

void GameClient::State::GameStateMachine::OnUpdate() const
{
	_currentState->OnUpdate();
}

std::vector<std::shared_ptr<GameClient::Engine::IDrawable>>& GameClient::State::GameStateMachine::GetDrawableEntities() const
{
	return _currentState->GetDrawables();
}

GameClient::State::GameStateMachine& GameClient::State::GameStateMachine::GetInstance()
{
	return _instance;
}

void GameClient::State::GameStateMachine::ChangeState(const GameStateType state)
{
	if (_currentState != nullptr)
	{
		_currentState->Leave();
	}

	const std::shared_ptr<IGameState> previousState = _currentState;
	switch (state)
	{
	case GameStateType::Playing:
		_currentState = _playingState;
		break;
	case GameStateType::GameOver:
		_currentState = _gameOverState;
		break;
	default:
		throw std::out_of_range("GameStateType was out of range");
	}

	_currentState->Enter(previousState);
}
