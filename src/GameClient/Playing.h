#pragma once
#include "IGameState.h"
#include "Snake.h"

namespace GameClient::GameState
{
	class Playing final : public IGameState
	{
	private:
		std::shared_ptr<GameObjects::Snake> _snake;

	public:
		explicit Playing();
		~Playing() override = default;

		Playing(Playing& copyOther) = delete;
		Playing operator=(Playing& copyOther) = delete;

		Playing operator=(Playing&& moveOther) = delete;
		Playing(Playing&& moveOther) = delete;

		void OnUpdate() override;
		void OnInput(Input::Keys input) override;
		std::shared_ptr<GameObjects::Snake> GetDrawableEntities() override;
	};
}
