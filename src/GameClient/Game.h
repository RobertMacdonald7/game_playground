#pragma once
#include <memory>
#include <chrono>

#include "GameDefinitions.h"
#include "IEngine.h"

namespace GameClient
{
	class Game
	{
	private:
		std::unique_ptr<Engine::IEngine> _engine;
		std::shared_ptr<GameObjects::Snake> _snake;

	public:
		explicit Game(std::unique_ptr<Engine::IEngine> engine);
		~Game();
		void OnResize(UINT width, UINT height) const;

		Game(Game& copyOther) = delete;
		Game operator=(Game& copyOther) = delete;

		Game(Game&& moveOther) = delete;
		Game operator=(Game&& moveOther) = delete;

		void Update();
	};
}

