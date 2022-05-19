#pragma once

#include <memory>

#include "IRenderTarget.h"

namespace GameClient::Engine
{
	/**
	 * \brief Interface for drawable game objects.
	 */
	class IDrawable // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~IDrawable() = default;

		/**
		 * \brief Draws the object
		 * \param renderTarget The engine's render target
		 */
		virtual void Draw(std::shared_ptr<IRenderTarget>& renderTarget) = 0;
	};
}
