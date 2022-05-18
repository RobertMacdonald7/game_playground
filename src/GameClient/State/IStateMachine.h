#pragma once
#include "../Input/Input.h"

namespace GameClient::State
{
	class IStateMachine // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IStateMachine() = default;

		/**
		 * \brief Changes the state.
		 * \param state The state to change to.
		 */
		virtual void ChangeState(int state) = 0;

		/**
		 * \brief Forwards input to the current state.
		 * \param input The input to forward.
		 */
		virtual void OnInput(Input::Input input) = 0;

		/**
		 * \brief Forwards OnUpdate to the current state.
		 */
		virtual void OnUpdate() = 0;
	};
}
