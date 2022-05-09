#include "Playing.h"

GameClient::State::Playing::Playing()
{
	_snake = std::make_unique<GameObjects::Snake>();
	_drawables.push_back(_snake);
};

void GameClient::State::Playing::OnUpdate()
{
	_snake->OnUpdate();
}

void GameClient::State::Playing::OnInput(const Input::Keys input)
{
	_snake->OnInput(input);
}

std::vector<std::shared_ptr<GameClient::Engine::IDrawable>>& GameClient::State::Playing::GetDrawableEntities()
{
	return _drawables;
}
