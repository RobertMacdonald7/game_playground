#pragma once
#include "Keys.h"
#include "Snake.h"
#include "IDrawable.h"

namespace GameClient::GameState
{
	class IGameState
	{
	public:
		virtual ~IGameState() = default;

		virtual void OnUpdate() = 0;
		virtual void OnInput(Input::Keys input) = 0;

		// TODO - Make IDrawable
		virtual std::vector<std::shared_ptr<GameClient::Engine::IDrawable>>& GetDrawableEntities() = 0;
	};
}
