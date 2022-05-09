#include "Playing.h"

GameClient::State::Playing::Playing()
{
	_playArea = std::make_shared<GameObjects::PlayArea>();
	_snake = std::make_shared<GameObjects::Snake>(_playArea);

	GameStateBase::GetDrawables().push_back(_playArea);
	GameStateBase::GetDrawables().push_back(_snake);
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
