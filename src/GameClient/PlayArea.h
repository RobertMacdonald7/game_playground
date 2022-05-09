#pragma once
#include <vector>

#include "GameDefinitions.h"
#include "IDrawable.h"

namespace GameClient::GameObjects
{
	enum class PlayAreaTile {
		BackGround,
		Wall
	};

	class PlayArea final : public Engine::IDrawable
	{
	private:
		std::vector<std::vector<PlayAreaTile>> _playArea{ game_width_units, std::vector<PlayAreaTile>(game_height_units) };
		ID2D1SolidColorBrush* _playAreaBrush = nullptr;
		ID2D1SolidColorBrush* _playAreaBoundaryBrush = nullptr;

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
		[[nodiscard]] bool IsColliding(int x, int y) const;

	private:
		void CreatePlayArea();
		static bool IsBoundary(int x, int y);
		[[nodiscard]] ID2D1SolidColorBrush* GetPlayAreaBrush(const PlayAreaTile area) const;
	};
}
