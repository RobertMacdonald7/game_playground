#pragma once
#include "Keys.h"
#include "Snake.h"
#include "IDrawable.h"

namespace GameClient::State
{
	class IGameState
	{
	public:
		virtual ~IGameState() = default;

		virtual void OnUpdate() = 0;
		virtual void OnInput(Input::Keys input) = 0;

		virtual std::vector<std::shared_ptr<Engine::IDrawable>>& GetDrawableEntities() = 0;
	};
}
