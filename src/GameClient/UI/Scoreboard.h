#pragma once

#include <memory>

#include "../Engine/IDrawable.h"
#include "Controls/Label.h"

namespace GameClient::UI
{
	class Scoreboard final : public Engine::IDrawable
	{
	private:
		std::unique_ptr<Controls::Label> _scoreLabel = nullptr;
		std::unique_ptr<Controls::Label> _highScoreLabel = nullptr;
		std::unique_ptr<Controls::Label> _restartPromptLabel = nullptr;
		int _highScore = 0;

	public:
		Scoreboard();
		~Scoreboard() override = default;
		void SetScore(int score);
		Scoreboard(Scoreboard& copyOther) = delete;
		Scoreboard operator=(Scoreboard& copyOther) = delete;

		Scoreboard(Scoreboard&& moveOther) = delete;
		Scoreboard operator=(Scoreboard&& moveOther) = delete;

		/**
		 * \copydoc Engine::IDrawable::Draw
		 */
		void Draw(Engine::IRender & renderEngine) override;
	};
}
