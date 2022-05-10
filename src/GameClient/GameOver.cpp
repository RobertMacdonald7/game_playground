#include "GameOver.h"

#include "GameStateMachine.h"

void GameClient::State::GameOver::OnInput(const Input::Keys keysDown)
{
	if (static_cast<int>(keysDown) & static_cast<int>(Input::Keys::SpaceBar))
	{
		GameStateMachine::GetInstance().ChangeState(GameStateType::Playing);
	}
}

GameClient::State::GameStateType GameClient::State::GameOver::GetType()
{
	return GameStateType::GameOver;
}

void GameClient::State::GameOver::Enter(const std::shared_ptr<IGameState> previousState)
{
	if (previousState->GetType() == GameStateType::Playing)
	{
		_previousPlayingState = previousState;
	}
	else
	{
		// This shouldn't ever occur!
		throw std::exception("Invalid state transition!");
	}

	// Save the last playing state's drawable entities so that they can be drawn in the background still.
	for (auto const& drawableEntity : _previousPlayingState->GetDrawables())
	{
		GetDrawables().push_back(drawableEntity);
	}
}

void GameClient::State::GameOver::Leave()
{
	GetDrawables().clear();

}
