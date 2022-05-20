#pragma once

#include <string>

#include "../../Engine/IDrawable.h"

namespace GameClient::GameObjects::UIControls
{
	template <typename T>
	class Property
	{
	private:
		T _value;
	public:
		T& operator=(const T& newValue) { return _value = newValue; }  // NOLINT(misc-unconventional-assign-operator)
		const T& operator() () const { return _value; }
		T& operator()(const T& newValue) { return _value = newValue; }
	};

	class Button final : public Engine::IDrawable
	{
	public:
		std::wstring text;
		Engine::Coordinate2d location = {0,0};
		Engine::Size size = {0,0};
		bool selected = false;

		/**
		 * \copydoc Engine::IDrawable::Draw
		 */
		void Draw(Engine::IRender& renderEngine) override;
	};
}
