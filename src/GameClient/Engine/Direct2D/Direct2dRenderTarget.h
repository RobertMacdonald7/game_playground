#pragma once

#include <d2d1.h>
#include <map>

#include "../IRenderTarget.h"

namespace GameClient::Engine::Direct2D
{
	/**
	 * \brief %Direct2D implementation of IRenderTarget
	 */
	class Direct2dRenderTarget final : public IRenderTarget
	{
	private:
		ID2D1HwndRenderTarget* _pRenderTarget = nullptr;
		std::map<Colour, ID2D1SolidColorBrush*> _brushes = {};

	public:
		explicit Direct2dRenderTarget(ID2D1HwndRenderTarget* renderTarget);
		~Direct2dRenderTarget() override;

		Direct2dRenderTarget() = delete;

		Direct2dRenderTarget(Direct2dRenderTarget& copyOther) = delete;
		Direct2dRenderTarget operator=(Direct2dRenderTarget& copyOther) = delete;

		Direct2dRenderTarget(Direct2dRenderTarget&& moveOther) = delete;
		Direct2dRenderTarget operator=(Direct2dRenderTarget&& moveOther) = delete;

		/**
		 * \copydoc IRenderTarget::CreateDeviceResources
		 */
		HRESULT CreateDeviceResources() override;

		/**
		 * \copydoc IRenderTarget::BeginDraw
		 */
		void BeginDraw() override;

		/**
		 * \copydoc IRenderTarget::EndDraw
		 */
		HRESULT EndDraw() override;

		/**
		 * \copydoc IRenderTarget::DrawUnitRectangle
		 */
		void DrawUnitRectangle(Coordinate2d offset, Coordinate2d position, Coordinate2dF scale, Colour colour) override;

		/**
		 * \copydoc IRenderTarget::DrawLine
		 */
		void DrawLine(Coordinate2dF p0, Coordinate2dF p1, float strokeWidth, Colour colour) override;

		/**
		 * \copydoc IRenderTarget::Resize
		 */
		void Resize(Size size) override;

	private:
		/**
		 * \brief Creates and adds a Direct2D colour brush to _brushes.
		 * \param colour The colour of brush to create.
		 * \return The result of the operation.
		 */
		HRESULT CreateAndAddBrush(Colour colour);
	};
}
