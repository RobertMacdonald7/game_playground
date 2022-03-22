#pragma once

#include <Windows.h>

namespace GameClient::Engine
{
	class IEngine // NOLINT(cppcoreguidelines-special-member-functions)
	{
	protected:
		HWND _windowHandle = nullptr;

		// ReSharper disable once CppParameterMayBeConst
		explicit IEngine(HWND windowHandle) :
			_windowHandle(windowHandle)
		{ }

	public:
		virtual ~IEngine() = default;

		virtual HRESULT Initialize() = 0;
		virtual void Resize(UINT width, UINT height) const = 0;
		virtual HRESULT Draw() = 0;
	};
}
