#pragma once
#include "GameStateBase.h"
#include "../GameObjects/GameObjects.h"

namespace GameClient::State
{
	class Playing final : public GameStateBase
	{
	private:
		std::shared_ptr<GameObjects::PlayArea> _playArea;
		std::shared_ptr<GameObjects::Food> _food;
		std::shared_ptr<GameObjects::Snake> _snake;

		bool _blockInputUntilNextUpdate = false;
		Input::Input _cachedInput = Input::Input::None;

	public:
		explicit Playing();
		~Playing() override = default;

		Playing(Playing& copyOther) = delete;
		Playing operator=(Playing& copyOther) = delete;

		Playing operator=(Playing&& moveOther) = delete;
		Playing(Playing&& moveOther) = delete;

		GameStateType GetType() override;
		void Enter(std::shared_ptr<IGameState> previousState) override;
		void Leave() override;
		void OnUpdate() override;
		void OnInput(Input::Input input) override;
	};
}
