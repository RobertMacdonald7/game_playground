#pragma once
#include <vector>

#include "../GameDefinitions.h"
#include "../Engine/IDrawable.h"
#include "./Collision/ICollidable.h"

namespace GameClient::GameObjects
{
	enum class PlayAreaTile {
		BackGround,
		Wall
	};

	class PlayArea final : public Engine::IDrawable, public Collision::ICollidable
	{
	private:
		std::vector<std::vector<PlayAreaTile>> _playArea{ game_width_units, std::vector<PlayAreaTile>(game_height_units) };
		ID2D1SolidColorBrush* _playAreaBackgroundBrush = nullptr;
		ID2D1SolidColorBrush* _playAreaBoundaryBrush = nullptr;
		ID2D1SolidColorBrush* _playAreaGridBrush = nullptr;

	public:
		PlayArea();
		~PlayArea() override;

		PlayArea(PlayArea& copyOther) = delete;
		PlayArea operator=(PlayArea& copyOther) = delete;

		PlayArea(PlayArea&& moveOther) = delete;
		PlayArea operator=(PlayArea&& moveOther) = delete;

		void Draw(ID2D1HwndRenderTarget* renderTarget) override;
		HRESULT CreateDeviceResources(ID2D1HwndRenderTarget* renderTarget) override;
		void DiscardDeviceResources() override;

		Collision::CollidableName GetCollidableName() override;
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		void CreatePlayArea();
		static bool IsBoundary(int x, int y);
		[[nodiscard]] ID2D1SolidColorBrush* GetPlayAreaBrush(const PlayAreaTile area) const;
	};
}
