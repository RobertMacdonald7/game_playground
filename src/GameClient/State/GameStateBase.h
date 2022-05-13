#pragma once
#include "IGameState.h"

namespace GameClient::State
{
	class GameStateBase : public IGameState  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	private:
		std::vector<std::shared_ptr<Engine::IDrawable>> _drawables = {};

	public:
		~GameStateBase() override = default;

		GameStateType GetType() override = 0;
		void Enter(std::shared_ptr<IGameState> previousState) override;
		void Leave() override;
		void OnUpdate(IStateMachine& context) override;
		void OnInput(IStateMachine& context, Input::Input input) override;
		std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawables() override;

	protected:
		GameStateBase() = default;
	};
}
