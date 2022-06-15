#include "GameStateMachine.h"

#include <stdexcept>

GameClient::State::GameStateMachine::GameStateMachine(const std::vector<std::shared_ptr<IGameState>>& states)
{
	for (const auto& state : states)
	{
		_states[static_cast<int>(state->GetType())] = state;
	}

	GameStateMachine::ChangeState(static_cast<int>(GameStateType::StartMenu));
}

void GameClient::State::GameStateMachine::OnInput(const Input::Input input)
{
	_currentState->OnInput(*this, input);
}

void GameClient::State::GameStateMachine::OnUpdate()
{
	_currentState->OnUpdate(*this);
}

std::list<std::shared_ptr<GameClient::Engine::IDrawable>>&
GameClient::State::GameStateMachine::GetDrawableEntities() const
{
	return _currentState->GetDrawables();
}

void GameClient::State::GameStateMachine::ChangeState(const int state)
{
	if (!_states.contains(state))
	{
		// This indicates a serious issue with the code if we're attempting to enter a state this state machine can't handle
		throw std::out_of_range("GameStateType was out of range");
	}

	// Leave the current state if there is one
	if (_currentState != nullptr)
	{
		_currentState->Leave();
	}

	// Save the previous state
	const std::shared_ptr<IGameState> previousState = _currentState;

	// Enter the new state
	_currentState = _states[state];
	_currentState->Enter(previousState);
}
