#include "Direct2dRenderTarget.h"

#include <stdexcept>

#include "Direct2dColour.h"
#include "../../Utility/Direct2dUtility.h"

GameClient::Engine::Direct2D::Direct2dRenderTarget::Direct2dRenderTarget(ID2D1HwndRenderTarget* renderTarget):
	_pRenderTarget(renderTarget)
{
}

GameClient::Engine::Direct2D::Direct2dRenderTarget::~Direct2dRenderTarget()
{
	// Release the underlying render target
	SafeRelease(&_pRenderTarget);

	// Release all the brushes
	for (auto& [colour, brush] : _brushes)
	{
		SafeRelease(&brush);
	}

	_brushes.clear();
}

HRESULT GameClient::Engine::Direct2D::Direct2dRenderTarget::CreateDeviceResources()
{
	auto result = S_OK;

	// Create a brush for each possible colour
	for (auto c = 0; c < static_cast<int>(Colour::Last); ++c)
	{
		result = CreateAndAddBrush(static_cast<Colour>(c));
		RETURN_FAILED_HRESULT(result);
	}

	return result;
}

void GameClient::Engine::Direct2D::Direct2dRenderTarget::BeginDraw()
{
	_pRenderTarget->BeginDraw();
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

HRESULT GameClient::Engine::Direct2D::Direct2dRenderTarget::EndDraw()
{
	return _pRenderTarget->EndDraw();
}

void GameClient::Engine::Direct2D::Direct2dRenderTarget::DrawUnitRectangle(
	const Coordinate2d offset, const Coordinate2d position, const Coordinate2dF scale, const Colour colour)
{
	// Create and draw
	const auto rectangle = Utility::Direct2dUtility::CreateUnitRectangle(offset, position, scale);
	_pRenderTarget->FillRectangle(&rectangle, _brushes[colour]);
}

void GameClient::Engine::Direct2D::Direct2dRenderTarget::DrawLine(const Coordinate2dF p0, const Coordinate2dF p1,
                                                                  const float strokeWidth, const Colour colour)
{
	// Create and draw
	const auto d2Point0 = D2D1::Point2F(p0.x, p0.y);
	const auto d2Point1 = D2D1::Point2F(p1.x, p1.y);
	_pRenderTarget->DrawLine(d2Point0, d2Point1, _brushes[colour], strokeWidth);
}

void GameClient::Engine::Direct2D::Direct2dRenderTarget::Resize(const Size size)
{
	const auto d2Size = D2D1::SizeU(size.width, size.height);
	_pRenderTarget->Resize(d2Size);
}

HRESULT GameClient::Engine::Direct2D::Direct2dRenderTarget::CreateAndAddBrush(const Colour colour)
{
	// Convert the colour
	const auto brushColour = Direct2dColour::GetDirect2dColour(colour);

	// Create the brush
	ID2D1SolidColorBrush* brush = nullptr;
	const auto result = _pRenderTarget->CreateSolidColorBrush(brushColour, &brush);

	RETURN_FAILED_HRESULT(result);

	// Store the brush
	_brushes[colour] = brush;
	return result;
}
