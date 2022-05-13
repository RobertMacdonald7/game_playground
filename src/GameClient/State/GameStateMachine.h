#pragma once
#include "IGameState.h"
#include "GameStates.h"
#include "IStateMachine.h"

namespace GameClient::State
{
	class GameStateMachine final : public IStateMachine
	{
	private:
		std::shared_ptr<IGameState> _currentState = nullptr;
		std::shared_ptr<Playing> _playingState = nullptr;
		std::shared_ptr<GameOver> _gameOverState = nullptr;

	public:
		GameStateMachine();
		~GameStateMachine() override = default;

		GameStateMachine(GameStateMachine& copyOther) = delete;
		GameStateMachine operator=(GameStateMachine& copyOther) = delete;

		GameStateMachine(GameStateMachine&& moveOther) = delete;
		GameStateMachine operator=(GameStateMachine&& moveOther) = delete;

		void ChangeState(int state) override;
		void OnInput(Input::Input input) override;
		void OnUpdate() override;
		[[nodiscard]] std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawableEntities() const;
	};
}
