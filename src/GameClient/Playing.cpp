#include "Playing.h"

GameClient::GameState::Playing::Playing()
{
	_snake = std::make_unique<GameObjects::Snake>();
};

void GameClient::GameState::Playing::OnUpdate()
{
	_snake->OnUpdate();
}

void GameClient::GameState::Playing::OnInput(const Input::Keys input)
{
	_snake->OnInput(input);
}

std::shared_ptr<GameClient::GameObjects::Snake> GameClient::GameState::Playing::GetDrawableEntities()
{
	return _snake;
}
