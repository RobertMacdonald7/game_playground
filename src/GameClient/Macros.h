#pragma once

// Windows Header Files:
#include <Windows.h>

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

template<class Interface>
void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = nullptr;
	}
}

#ifndef ASSERT
#if defined( DEBUG ) || defined( _DEBUG )
#define ASSERT(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define ASSERT(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#ifndef RETURN_NON_SUCCEEDED
#define RETURN_NON_SUCCEEDED(result) if(!SUCCEEDED((HRESULT)(result))) return result
#endif

