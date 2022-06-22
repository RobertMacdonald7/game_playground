#pragma once

#include "GameStateBase.h"
#include "../GameObjects/StartMenu.h"

namespace GameClient::State
{
	class StartMenuState final : public GameStateBase
	{
	private:
		std::shared_ptr<GameObjects::StartMenu> _menu;

	public:
		explicit StartMenuState(std::shared_ptr<GameObjects::StartMenu> menu);
		StartMenuState() = delete;

		GameStateType GetType() override;
		void Enter(std::shared_ptr<IGameState> previousState) override;
		void Leave() override;
		void OnUpdate(IStateMachine& context) override;
		void OnInput(IStateMachine& context, Input::Input input) override;
	};
}
