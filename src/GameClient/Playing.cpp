#include "Playing.h"

GameClient::State::Playing::Playing()
{
	_snake = std::make_unique<GameObjects::Snake>();
	GetDrawables().push_back(_snake);
};

GameClient::State::GameStateType GameClient::State::Playing::GetType()
{
	return GameStateType::Playing;
}

void GameClient::State::Playing::Enter(const std::shared_ptr<IGameState> previousState)
{
	_snake->Reset();
}

void GameClient::State::Playing::OnUpdate()
{
	_snake->OnUpdate();
}

void GameClient::State::Playing::OnInput(const Input::Keys input)
{
	_snake->OnInput(input);
}
