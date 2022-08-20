#include "EngineFactory.h"

std::unique_ptr<GameClient::Engine::IEngine> GameClient::Engine::Direct2DEngineFactory::CreateEngine(HWND windowHandle) const
{
	return std::make_unique<Direct2D::Direct2dEngine>(windowHandle);
}