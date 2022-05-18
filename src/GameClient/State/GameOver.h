#pragma once
#include "GameStateBase.h"

namespace GameClient::State
{
	/**
	 * \brief Defines the state when the game is over, and the player cannot move the snake anymore.
	 */
	class GameOver final : public GameStateBase
	{
	private:
		std::shared_ptr<IGameState> _previousPlayingState;
	public:
		GameStateType GetType() override;
		void Enter(std::shared_ptr<IGameState> previousState) override;
		void Leave() override;
		void OnInput(IStateMachine& context, Input::Input input) override;
	};
}
