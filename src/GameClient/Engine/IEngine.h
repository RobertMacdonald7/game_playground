#pragma once

#include <memory>
#include <vector>

#include "IDrawable.h"
#include "../Macros.h"

namespace GameClient::Engine
{
	/**
	 * \brief Interface for the game engine.
	 */
	class IEngine // NOLINT(cppcoreguidelines-special-member-functions)
	{
	private:
		HWND _windowHandle = nullptr;

	protected:
		[[nodiscard]] HWND GetWindowHandle() const;

		explicit IEngine(HWND windowHandle) :
			_windowHandle(windowHandle)
		{
		}

	public:
		virtual ~IEngine() = default;

		/**
		 * \brief Initializes Engine resources.
		 * \return Result of the operation.
		 */
		virtual HRESULT Initialize() = 0;

		/**
		 * \brief Resizes the buffer underlying the render target. TODO - Expose render target through a getter.
		 * \param width width of available render area.
		 * \param height Height of available render area.
		 */
		virtual void Resize(int width, int height) const = 0;

		/**
		 * \brief Draws each object provided.
		 * \param drawables A list of drawable objects.
		 * \return Result of the operation.
		 */
		virtual HRESULT Draw(const std::vector<std::shared_ptr<IDrawable>>& drawables) = 0;
	};

	/**
	 * \brief Gets the window handle.
	 * \return The window handle.
	 */
	inline HWND IEngine::GetWindowHandle() const
	{
		return _windowHandle;
	}
}
