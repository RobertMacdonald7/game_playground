#include <memory>

#include "Window.h"

HRESULT RunMessageLoop(HINSTANCE hInstance)
{
	// Create our window
	const auto window = std::make_unique<GameClient::Window>();
	const auto result = window->Initialize(hInstance);

	RETURN_FAILED_HRESULT(result);

	// Run the loop
	window->Run();

	return result;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/,
                   _In_ int /*nCmdShow*/)
{
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	if (!(SUCCEEDED(CoInitialize(nullptr))))
	{
		return -1;
	}

	HRESULT result;
	try
	{
		result = RunMessageLoop(hInstance);
	}
	catch (...)
	{
		// Something bad happened that means the app has to close
		result = E_FAIL;
	}

	CoUninitialize();

	return result;
}
