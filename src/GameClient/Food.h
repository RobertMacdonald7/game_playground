#pragma once
#include <random>

#include "GameDefinitions.h"
#include "ICollidable.h"
#include "IDrawable.h"
#include "Keys.h"

namespace GameClient::GameObjects
{
	class Food final : public Engine::IDrawable, public Collision::ICollidable
	{
	private:
		std::pair<UINT, UINT> _coordinates;
		ID2D1SolidColorBrush* _foodBrush = nullptr;
		bool _eaten = false;
		std::mt19937 _rng{std::random_device{}()};
		std::uniform_int_distribution<int> _xDistribution{ 1, game_width_units - 2 };
		std::uniform_int_distribution<int> _yDistribution{ 1, game_height_units - 2 };

	public:
		Food();
		~Food() override;
		void OnUpdate();
		bool OnInput(Input::Keys keysDown);

		Food(Food& copyOther) = delete;
		Food operator=(Food& copyOther) = delete;

		Food(Food&& moveOther) = delete;
		Food operator=(Food&& moveOther) = delete;

		void Reset();

		// IDrawable
		void Draw(ID2D1HwndRenderTarget* renderTarget) override;
		HRESULT CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) override;
		void DiscardDeviceResources() override;

		// ICollidable
		Collision::CollidableName GetCollidableName() override;
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		void PlaceFoodAtValidCoordinates();
	};
}


