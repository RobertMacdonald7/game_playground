#include "GameStateMachine.h"

#include <stdexcept>

GameClient::State::GameStateMachine::GameStateMachine()
{
	// TODO - Inject these
	_playingState = std::make_shared<Playing>();
	_gameOverState = std::make_shared<GameOver>();

	GameStateMachine::ChangeState(static_cast<int>(GameStateType::Playing));
}

void GameClient::State::GameStateMachine::OnInput(const Input::Input input)
{
	_currentState->OnInput(*this, input);
}

void GameClient::State::GameStateMachine::OnUpdate()
{
	_currentState->OnUpdate(*this);
}

std::vector<std::shared_ptr<GameClient::Engine::IDrawable>>&
GameClient::State::GameStateMachine::GetDrawableEntities() const
{
	return _currentState->GetDrawables();
}

void GameClient::State::GameStateMachine::ChangeState(int state)
{
	// Leave the current state if there is one
	if (_currentState != nullptr)
	{
		_currentState->Leave();
	}

	// Determine which state to enter
	const std::shared_ptr<IGameState> previousState = _currentState;
	switch (static_cast<GameStateType>(state))
	{
	case GameStateType::Playing:
		_currentState = _playingState;
		break;
	case GameStateType::GameOver:
		_currentState = _gameOverState;
		break;
	default:
		// This indicates a serious issue with the code if we're attempting to enter a state this state machine can't handle
		throw std::out_of_range("GameStateType was out of range");
	}

	// Enter the new state
	_currentState->Enter(previousState);
}
