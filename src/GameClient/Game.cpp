#include "Game.h"

#include <string>

GameClient::Game::Game(std::unique_ptr<Engine::IEngine> engine):
_engine(std::move(engine))
{
	const HRESULT result = _engine->Initialize();

	if (FAILED(result))
	{
		const auto message = "Engine failed to initialize: " + std::to_string(result);
		// TODO - More precise exception
		throw std::exception(message.c_str());
	}

	_snake = std::make_shared<GameObjects::Snake>();
}

GameClient::Game::~Game() = default;

void GameClient::Game::OnResize(const UINT width, const UINT height) const
{
	_engine->Resize(width, height);
}

void GameClient::Game::Update()
{
	_snake->OnUpdate();
	_engine->Draw(_snake);
}
