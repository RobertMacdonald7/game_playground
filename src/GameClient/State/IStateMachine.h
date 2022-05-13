#pragma once
#include "../Input/Input.h"

namespace GameClient::State
{
	class IStateMachine // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IStateMachine() = default;

		virtual void ChangeState(int state) = 0;

		virtual void OnInput(Input::Input input) = 0;
		virtual void OnUpdate() = 0;
	};
}
