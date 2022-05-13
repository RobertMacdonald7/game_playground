#include <memory>

#include "Window.h"

HRESULT RunGameLoop(HINSTANCE hInstance)
{
	const auto gameWindow = std::make_unique<GameClient::Window>();

	const auto result = gameWindow->Initialize(hInstance);

	RETURN_FAILED_HRESULT(result);

	gameWindow->Run();

	return result;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
{
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	if (!(SUCCEEDED(CoInitialize(nullptr))))
	{
		return -1;
	}

	const auto result = RunGameLoop(hInstance);

	CoUninitialize();

	return result;
}


