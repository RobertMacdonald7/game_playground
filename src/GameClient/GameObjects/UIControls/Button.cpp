#include "Button.h"

void GameClient::GameObjects::UIControls::Button::Draw(Engine::IRender& renderEngine)
{
	if (selected)
	{
		renderEngine.DrawRectangle(location, size, 10.0f, Engine::Colour::Blue);
	}
	else
	{
		renderEngine.DrawRectangle(location, size, 1.0f, Engine::Colour::Black);

	}

	renderEngine.DrawString(text, location, size, Engine::Colour::Black);
}
