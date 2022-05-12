#pragma once

#include "../Colour.h"
#include <d2d1helper.h>

namespace GameClient::Engine::Direct2D
{
	class Direct2dColour
	{
	public:
		static D2D1::ColorF GetDirect2dColour(Colour colour);
	};
}
