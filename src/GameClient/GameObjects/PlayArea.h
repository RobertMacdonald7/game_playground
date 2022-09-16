#pragma once
#include <vector>

#include "../GameDefinitions.h"
#include "IDrawable.h"
#include "Collision/CollidableBase.h"

namespace GameClient::GameObjects
{
	/**
	 * \brief The type of play area.
	 */
	enum class PlayAreaTile
	{
		BackGround,
		Wall
	};

	/**
	 * \brief Defines the play area the snake can move inside of.
	 */
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

		/**
		 * \copydoc Engine::IDrawable::Draw
		 */
		void Draw(Engine::IRender& renderEngine) override;

		/**
		 * \copydoc Collision::CollidableBase::GetCollidableName
		 */
		Collision::CollidableName GetCollidableName() override;

		/**
		 * \copydoc Collision::CollidableBase::IsColliding
		 */
		[[nodiscard]] bool IsColliding(int x, int y, Collision::CollidableName source) override;

	private:
		/**
		 * \brief Creates the play area.
		 */
		void CreatePlayArea();

		/**
		 * \brief Tests if the given coordinates lie on the boundary of the play area.
		 * \param x The X coordinate to check.
		 * \param y The Y coordinate to check.
		 * \return Whether X,Y lie on the boundary.
		 */
		static bool IsBoundary(int x, int y);

		/**
		 * \brief Transforms the type of play area into a desired colour.
		 * \param area The type of area.
		 * \return The colour the tile should be.
		 */
		[[nodiscard]] static Engine::Colour GetPlayAreaColour(PlayAreaTile area);
	};
}
