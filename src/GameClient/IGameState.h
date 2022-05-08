#pragma once
#include "Keys.h"
#include "Snake.h"

namespace GameClient::GameState
{
	class IGameState  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	protected:
		explicit IGameState() = default;

	public:
		virtual ~IGameState() = default;

		virtual void OnUpdate() = 0;
		virtual void OnInput(Input::Keys input) = 0;

		// TODO - Make IDrawable
		virtual std::shared_ptr<GameObjects::Snake> GetDrawableEntities() = 0;
	};
}
