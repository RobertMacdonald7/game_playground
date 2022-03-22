#pragma once
#include <memory>

#include "IEngine.h"

namespace GameClient
{
	class Game
	{
	private:
		std::unique_ptr<Engine::IEngine> _engine;

	public:
		explicit Game(std::unique_ptr<Engine::IEngine> engine);
		~Game();
		void OnResize(UINT width, UINT height) const;

		Game(Game& copyOther) = delete;
		Game operator=(Game& copyOther) = delete;

		Game operator=(Game&& moveOther) = delete;
		Game(Game&& moveOther) = delete;

		void Update();
	};
}

