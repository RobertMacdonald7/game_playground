#pragma once

#include "IRender.h"

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
		 * \param renderEngine The engine's render target
		 */
		virtual void Draw(IRender& renderEngine) = 0;
	};
}
