#pragma once

#include <memory>

#include "IRenderTarget.h"

namespace GameClient::Engine
{
	class IDrawable
	{
	public:
		virtual ~IDrawable() = default;

		virtual void Draw(const std::shared_ptr<IRenderTarget>& renderTarget) = 0;
	};
}
