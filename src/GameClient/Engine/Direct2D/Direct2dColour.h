#pragma once

#include "../Colour.h"
#include <d2d1helper.h>

namespace GameClient::Engine::Direct2D
{
	/**
	 * \brief Converter from generic colour to Direct2D colours
	 */
	class Direct2dColour
	{
	public:
		/**
		 * \brief Converts a colour to its Direct2D equivalent.
		 * \param colour The basic colour
		 * \return The direct2D colour.
		 */
		static D2D1::ColorF GetDirect2dColour(Colour colour);
	};
}
