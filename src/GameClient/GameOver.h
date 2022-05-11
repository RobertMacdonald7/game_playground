#pragma once
#include "GameStateBase.h"

namespace GameClient::State
{
	class GameOver final : public GameStateBase
	{
	private:
		std::shared_ptr<IGameState> _previousPlayingState;
	public:
		GameStateType GetType() override;
		void Enter(std::shared_ptr<IGameState> previousState) override;
		void Leave() override;
		void OnInput(Input::Input input) override;
	};
}


