#include "Scoreboard.h"

#include "../GameDefinitions.h"

GameClient::UI::Scoreboard::Scoreboard()
{
	_scoreLabel = std::make_unique<Controls::Label>();
	_highScoreLabel = std::make_unique<Controls::Label>();
	_restartPromptLabel = std::make_unique<Controls::Label>();

	_scoreLabel->text = L"SCORE";
	_scoreLabel->size = { 300, 100 };
	_scoreLabel->location = {
		game_width_pixels / 2 - _scoreLabel->size.width / 2,
		game_height_pixels / 4 - _scoreLabel->size.height / 2
	};

	_highScoreLabel->text = L"HIGH SCORE";
	_highScoreLabel->size = { 300, 100 };
	_highScoreLabel->location = {
		_scoreLabel->location.x,
		game_height_pixels * 2 / 4 - _scoreLabel->size.height / 2 };

	_restartPromptLabel->text = L"Press space-bar to start a new game...";
	_restartPromptLabel->size = { 800, 100 };
	_restartPromptLabel->location = {
		game_width_pixels / 2 - _restartPromptLabel->size.width / 2,
		game_height_pixels * 3 / 4 - _scoreLabel->size.height / 2 };
}

void GameClient::UI::Scoreboard::Draw(Engine::IRender& renderEngine)
{
	renderEngine.FillRectangle({ 0, 0 }, { game_width_pixels, game_height_pixels }, Engine::Colour::WhiteAlpha);
	_scoreLabel->Draw(renderEngine);
	_highScoreLabel->Draw(renderEngine);
	_restartPromptLabel->Draw(renderEngine);
}
