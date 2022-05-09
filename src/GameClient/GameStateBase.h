#pragma once
#include "IGameState.h"

namespace GameClient::State
{
	class GameStateBase : public IGameState
	{
	private:
		std::vector<std::shared_ptr<Engine::IDrawable>> _drawables = {};

	public:
		GameStateBase() = default;
		~GameStateBase() override = default;

		GameStateBase(GameStateBase& copyOther) = delete;
		GameStateBase operator=(GameStateBase& copyOther) = delete;

		GameStateBase operator=(GameStateBase&& moveOther) = delete;
		GameStateBase(GameStateBase&& moveOther) = delete;

		GameStateType GetType() override;
		void Enter(std::shared_ptr<IGameState> previousState) override;
		void Leave() override;
		void OnUpdate() override;
		void OnInput(Input::Keys input) override;
		std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawables() override;
	};
}
