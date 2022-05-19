#pragma once
#include "IGameState.h"
#include "GameStates.h"
#include "IStateMachine.h"

namespace GameClient::State
{
	/**
	 * \brief An IStateMachine that defines the overall game state.
	 */
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

		/**
		 * \copydoc IStateMachine::ChangeState
		 */
		void ChangeState(int state) override;

		/**
		 * \copydoc IStateMachine::OnInput
		 */
		void OnInput(Input::Input input) override;

		/**
		 * \copydoc IStateMachine::OnUpdate
		 */
		void OnUpdate() override;

		/**
		 * \brief Gets the IDrawable objects.
		 * \return A vector of IDrawables.
		 */
		[[nodiscard]] std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawableEntities() const;
	};
}
