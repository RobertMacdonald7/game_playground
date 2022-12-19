#include "Scoreboard.h"

#include "GameDefinitions.h"

GameClient::UI::Scoreboard::Scoreboard(std::unique_ptr<Web::Client::ScoreClient> scoreClient) :
	_client(std::move(scoreClient))
{
	_scoreLabel = std::make_unique<Controls::Label>();
	_highScoreLabel = std::make_unique<Controls::Label>();
	_restartPromptLabel = std::make_unique<Controls::Label>();

	_scoreLabel->text = L"SCORE: ...";
	_scoreLabel->size = { game_width_pixels, 100 };
	_scoreLabel->location = {
		game_width_pixels / 2 - _scoreLabel->size.width / 2,
		game_height_pixels / 4 - _scoreLabel->size.height / 2
	};

	_highScoreLabel->text = L"HIGH SCORE: ...";
	_highScoreLabel->size = { game_width_pixels, 100 };
	_highScoreLabel->location = {
		_scoreLabel->location.x,
		game_height_pixels * 2 / 4 - _scoreLabel->size.height / 2
	};

	_restartPromptLabel->text = L"Press space-bar to start a new game...";
	_restartPromptLabel->size = { game_width_pixels, 100 };
	_restartPromptLabel->location = {
		game_width_pixels / 2 - _restartPromptLabel->size.width / 2,
		game_height_pixels * 3 / 4 - _scoreLabel->size.height / 2
	};
}

void GameClient::UI::Scoreboard::SetScore(const int score) const
{
	// Reset the displayed scores until we get a response from the server
	_scoreLabel->text = L"SCORE: " + std::to_wstring(score);
	_highScoreLabel->text = L"HIGH SCORE: ...";

	// Callback executes on a background thread!
	_client->SetScoreForUser(L"Robert Macdonald", score,
		[this, score](const bool success, const Web::Client::Score& currentScore, const Web::Client::Score& highScore)
		{
			if (success)
			{
				 _scoreLabel->text = L"SCORE: " + std::to_wstring(currentScore.score);
				_highScoreLabel->text = L"HIGH SCORE: " + std::to_wstring(highScore.score);
			}
			else
			{
				_highScoreLabel->text = L"HIGH SCORE: ???";
			}
		});
}

void GameClient::UI::Scoreboard::Draw(Engine::IRender& renderEngine)
{
	renderEngine.FillRectangle({ 0, 0 }, { game_width_pixels, game_height_pixels }, Engine::Colour::WhiteAlpha);
	_scoreLabel->Draw(renderEngine);
	_highScoreLabel->Draw(renderEngine);
	_restartPromptLabel->Draw(renderEngine);
}
