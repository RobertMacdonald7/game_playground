#pragma once
#include "Food.h"
#include "GameStateBase.h"
#include "Snake.h"

namespace GameClient::State
{
	class Playing final : public GameStateBase
	{
	private:
		std::shared_ptr<GameObjects::PlayArea> _playArea;
		std::shared_ptr<GameObjects::Food> _food;
		std::shared_ptr<GameObjects::Snake> _snake;

		bool _blockInputUntilNextUpdate = false;

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
		void OnInput(Input::Keys input) override;
	};
}
