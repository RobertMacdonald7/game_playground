#pragma once
#include <memory>
#include <vector>

#include "GameStateType.h"
#include "IStateMachine.h"
#include "../Engine/IDrawable.h"

namespace GameClient::State
{
	class IGameState // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IGameState() = default;

		/**
		 * \brief Gets the type of game state.
		 * \return The game state type.
		 */
		virtual GameStateType GetType() = 0;

		/**
		 * \brief Enters this state
		 * \param previousState The state we're leaving.
		 */
		virtual void Enter(std::shared_ptr<IGameState> previousState) = 0;

		/**
		 * \brief Leaves this state.
		 */
		virtual void Leave() = 0;

		/**
		 * \brief Updates all updatable objects.
		 * \param context The state machine context.
		 */
		virtual void OnUpdate(IStateMachine& context) = 0;

		/**
		 * \brief Sends input to all objects that can process it.
		 * \param context The state machine context.
		 * \param input The pressed key.
		 */
		virtual void OnInput(IStateMachine& context, Input::Input input) = 0;

		/**
		 * \brief Gets the IDrawable objects.
		 * \return A vector of IDrawables.
		 */
		virtual std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawables() = 0;
	};
}
