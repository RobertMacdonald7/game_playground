#pragma once

#include "Direct2D/Direct2dEngine.h"

#ifdef ENGINE_2D_EXPORTS
#define ENGINE_2D_API __declspec(dllexport)
#else
#define ENGINE_2D_API __declspec(dllimport)
#endif

namespace GameClient::Engine
{
	class ENGINE_2D_API IEngineFactory  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IEngineFactory() = default;
		virtual std::unique_ptr<IEngine> CreateEngine(HWND windowHandle) const = 0;
	};

	class ENGINE_2D_API Direct2DEngineFactory final : IEngineFactory
	{
	public:
		std::unique_ptr<IEngine> CreateEngine(HWND windowHandle) const override;
	};
}
