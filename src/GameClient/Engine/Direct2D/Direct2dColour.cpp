#include "Direct2dColour.h"
#include <stdexcept>

D2D1::ColorF GameClient::Engine::Direct2D::Direct2dColour::GetDirect2dColour(const Colour colour)
{
	switch (colour)
	{
	case Colour::White:
		return D2D1::ColorF::White;
	case Colour::Gray:
		return D2D1::ColorF::Gray;
	case Colour::DarkRed:
		return D2D1::ColorF::DarkRed;
	case Colour::Green:
		return D2D1::ColorF::Green;
	case Colour::Blue:
		return D2D1::ColorF::Blue;
	default:
		throw std::out_of_range("Colour not supported");
	}
}
