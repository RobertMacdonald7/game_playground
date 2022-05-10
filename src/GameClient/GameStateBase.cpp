#include "GameStateBase.h"

GameClient::State::GameStateType GameClient::State::GameStateBase::GetType()
{
	throw std::exception("GameStateBase does not have a type");
}

void GameClient::State::GameStateBase::Enter(const std::shared_ptr<IGameState> previousState)
{
	// NoOp
}

void GameClient::State::GameStateBase::Leave()
{
	// NoOp
}

void GameClient::State::GameStateBase::OnUpdate()
{
	// NoOp
}

void GameClient::State::GameStateBase::OnInput(const Input::Keys keysDown)
{
	// NoOp
}

std::vector<std::shared_ptr<GameClient::Engine::IDrawable>>& GameClient::State::GameStateBase::GetDrawables()
{
	return _drawables;
}