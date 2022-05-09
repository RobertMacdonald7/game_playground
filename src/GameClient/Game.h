#pragma once
#include <memory>
#include <chrono>

#include "IEngine.h"
#include "IGameState.h"

namespace GameClient
{
	class Game
	{
	private:
		std::unique_ptr<Engine::IEngine> _engine;

		Input::Keys _previousKey = Input::Keys::None;

		std::chrono::steady_clock::time_point _lastUpdateTime = std::chrono::steady_clock::now();
		std::chrono::nanoseconds _accumulatedFrameTime = std::chrono::nanoseconds(0);
		unsigned short _maxUpdatesPerFrame = 1;
		std::chrono::milliseconds _timeStep = std::chrono::milliseconds(200);

	public:
		explicit Game(std::unique_ptr<Engine::IEngine> engine);
		~Game();
		void OnResize(UINT width, UINT height) const;
		void HandleInput();

		Game(Game& copyOther) = delete;
		Game operator=(Game& copyOther) = delete;

		Game(Game&& moveOther) = delete;
		Game operator=(Game&& moveOther) = delete;

		void ProcessFrame();
	};
}

