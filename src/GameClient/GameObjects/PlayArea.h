#pragma once
#include <vector>

#include "../GameDefinitions.h"
#include "../Engine/IDrawable.h"
#include "Collision/CollidableBase.h"

namespace GameClient::GameObjects
{
	enum class PlayAreaTile
	{
		BackGround,
		Wall
	};

	class PlayArea final : public Engine::IDrawable, public Collision::CollidableBase
	{
	private:
		std::vector<std::vector<PlayAreaTile>> _playArea{
			game_width_units, std::vector<PlayAreaTile>(game_height_units)
		};

	public:
		explicit PlayArea(std::shared_ptr<Collision::CollisionDetector> collisionDetector);
		~PlayArea() override;

		PlayArea() = delete;
		PlayArea(PlayArea& copyOther) = delete;
		PlayArea operator=(PlayArea& copyOther) = delete;

		PlayArea(PlayArea&& moveOther) = delete;
		PlayArea operator=(PlayArea&& moveOther) = delete;

		void Draw(const std::shared_ptr<Engine::IRenderTarget>& renderTarget) override;

		Collision::CollidableName GetCollidableName() override;
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		void CreatePlayArea();
		static bool IsBoundary(int x, int y);
		[[nodiscard]] static Engine::Colour GetPlayAreaColour(PlayAreaTile area);
	};
}
