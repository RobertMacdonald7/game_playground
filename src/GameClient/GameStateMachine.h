#pragma once
#include "GameOver.h"
#include "GameStateType.h"
#include "IGameState.h"
#include "Playing.h"

namespace GameClient::State
{
	class GameStateMachine
	{
	private:
		static GameStateMachine _instance;

		std::shared_ptr<IGameState> _currentState = nullptr;
		std::shared_ptr<Playing> _playingState = nullptr;
		std::shared_ptr<GameOver> _gameOverState = nullptr;

		GameStateMachine();

	public:
		~GameStateMachine() = default;

		GameStateMachine(GameStateMachine& copyOther) = delete;
		GameStateMachine operator=(GameStateMachine& copyOther) = delete;

		GameStateMachine(GameStateMachine&& moveOther) = delete;
		GameStateMachine operator=(GameStateMachine&& moveOther) = delete;

		static GameStateMachine& GetInstance();

		void ChangeState(GameStateType state);

		void OnInput(Input::Keys keysDown) const;
		void OnUpdate() const;
		[[nodiscard]] std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawableEntities() const;
	};
}
