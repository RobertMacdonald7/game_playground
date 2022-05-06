#include <memory>

#include "Window.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
{
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	if (!(SUCCEEDED(CoInitialize(nullptr))))
	{
		return -1;
	}

	const auto gameWindow = std::make_unique<GameClient::Window>();

	const auto result = gameWindow->Initialize(hInstance);

	if (SUCCEEDED(result))
	{
		gameWindow->Run();
	}

	CoUninitialize();

	return result;
}
