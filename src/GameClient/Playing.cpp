#include "Playing.h"

GameClient::GameState::Playing::Playing()
{
	_snake = std::make_unique<GameObjects::Snake>();
	_drawables.push_back(_snake);
};

void GameClient::GameState::Playing::OnUpdate()
{
	_snake->OnUpdate();
}

void GameClient::GameState::Playing::OnInput(const Input::Keys input)
{
	_snake->OnInput(input);
}

std::vector<std::shared_ptr<GameClient::Engine::IDrawable>>& GameClient::GameState::Playing::GetDrawableEntities()
{
	return _drawables;
}
