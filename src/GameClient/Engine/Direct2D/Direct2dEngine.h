#pragma once

#include <d2d1.h>

#include "../IEngine.h"

#pragma comment(lib, "d2d1")

namespace GameClient::Engine::Direct2D
{
	/**
	 * \brief %Direct2D implementation of IEngine
	 */
	class Direct2dEngine final : public IEngine
	{
	private:
		ID2D1Factory* _pDirect2dFactory = nullptr;
		std::shared_ptr<IRenderTarget> _renderTarget = nullptr;

	public:
		explicit Direct2dEngine(HWND windowHandle);
		~Direct2dEngine() override;

		Direct2dEngine(Direct2dEngine& copyOther) = delete;
		Direct2dEngine operator=(Direct2dEngine& copyOther) = delete;

		Direct2dEngine operator=(Direct2dEngine&& moveOther) = delete;
		Direct2dEngine(Direct2dEngine&& moveOther) = delete;

		/**
		 * \copydoc IEngine::Initialize
		 */
		HRESULT Initialize() override;

		/**
		 * \copydoc IEngine::Resize
		 */
		void Resize(int width, int height) const override;

		/**
		 * \copydoc IEngine::Draw
		 */
		HRESULT Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables) override;

	private:
		/**
		 * \brief Creates the render target and it's device resources.
		 * \return Result of the operation.
		 */
		HRESULT CreateDeviceResources();

		/**
		 * \brief Safely discards the Direct2D factory
		 */
		void DiscardDeviceIndependentResources();

		/**
		 * \brief Safely discards the render target
		 */
		void DiscardDeviceResources();
	};
}
