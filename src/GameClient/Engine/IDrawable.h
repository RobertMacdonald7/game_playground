#pragma once

#include <memory>

#include "IRenderTarget.h"

namespace GameClient::Engine
{
	class IDrawable // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IDrawable() = default;

		virtual void Draw(const std::shared_ptr<IRenderTarget>& renderTarget) = 0;
	};
}
