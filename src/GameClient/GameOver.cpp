#include "GameOver.h"

#include "GameStateMachine.h"

void GameClient::State::GameOver::OnInput(const Input::Keys input)
{
	switch (input)
	{
	case Input::Keys::SpaceBar:
		GameStateMachine::GetInstance().ChangeState(GameStateType::Playing);
		break;
	case Input::Keys::None:
	case Input::Keys::UpArrow:
	case Input::Keys::DownArrow:
	case Input::Keys::LeftArrow:
	case Input::Keys::RightArrow:
	default:
		break;
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
	for (auto const& drawableEntity : _previousPlayingState->GetDrawableEntities())
	{
		GetDrawables().push_back(drawableEntity);
	}
}

void GameClient::State::GameOver::Leave()
{
	GetDrawables().clear();

}
