#pragma once

#include <memory>
#include <vector>
#include <Windows.h>

#include "IDrawable.h"

namespace GameClient::Engine
{
	class IEngine
	{
	private:
		HWND _windowHandle = nullptr;

	protected:
		[[nodiscard]] HWND GetWindowHandle() const;

		// ReSharper disable once CppParameterMayBeConst
		explicit IEngine(HWND windowHandle) :
			_windowHandle(windowHandle)
		{ }

	public:
		virtual ~IEngine() = default;

		virtual HRESULT Initialize() = 0;
		virtual void Resize(UINT width, UINT height) const = 0;
		virtual HRESULT Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables) = 0;
	};

	inline HWND IEngine::GetWindowHandle() const
	{
		return _windowHandle;
	}
}
