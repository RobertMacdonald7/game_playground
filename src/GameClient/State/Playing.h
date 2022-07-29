#pragma once
#include "GameStateBase.h"
#include "../GameObjects/GameObjects.h"

namespace GameClient::State
{
	/**
	 * \brief Defines the IGameState when the game is in progress, and the player can move the snake.
	 */
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

		/**
		 * \copydoc GameStateBase::GetType
		 */
		GameStateType GetType() override;

		/**
		 * \copydoc GameStateBase::Enter
		 */
		void Enter(std::shared_ptr<IGameState> previousState) override;

		/**
		 * \copydoc GameStateBase::Leave
		 */
		void Leave() override;

		/**
		 * \copydoc GameStateBase::OnUpdate
		 */
		void OnUpdate(IStateMachine& context) override;

		/**
		 * \copydoc GameStateBase::OnInput
		 */
		void OnInput(IStateMachine& context, Input::Input input) override;

		/**
		 * \copydoc GameStateBase::GetScore
		 */
		int GetScore() override;
	};
}
