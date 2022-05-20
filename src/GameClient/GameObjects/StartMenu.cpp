#include "StartMenu.h"

#include "../GameDefinitions.h"
#include "../State/GameStateType.h"
#include "../Macros.h"

GameClient::GameObjects::StartMenu::StartMenu()
{
	_startButton = std::make_unique<UIControls::Button>();
	_exitButton = std::make_unique<UIControls::Button>();

	_startButton->text = L"Start";
	_startButton->size = {300, 100};
	_startButton->location = {
		game_width_pixels / 2 - _startButton->size.width / 2,
		game_height_pixels / 3 - _startButton->size.height / 2
	};
	_startButton->selected = true;

	_exitButton->text = L"Exit";
	_exitButton->size = {300, 100};
	_exitButton->location = {
		_startButton->location.x,
		game_height_pixels * 2 / 3 - _exitButton->size.height / 2};
}

void GameClient::GameObjects::StartMenu::OnInput(State::IStateMachine& context, const Input::Input input) const
{
	switch (input)
	{
	case Input::Input::Up:
	case Input::Input::Down:
		_exitButton->selected = !_exitButton->selected;
		_startButton->selected = !_startButton->selected;
		break;
	case Input::Input::SpaceBar:
		if (_startButton->selected)
		{
			context.ChangeState(static_cast<int>(State::GameStateType::Playing));
		}
		else
		{
			PostQuitMessage(0);
		}
	}
}

void GameClient::GameObjects::StartMenu::OnUpdate(State::IStateMachine& context)
{
}

void GameClient::GameObjects::StartMenu::Draw(Engine::IRender& renderEngine)
{
	_startButton->Draw(renderEngine);
	_exitButton->Draw(renderEngine);
}
