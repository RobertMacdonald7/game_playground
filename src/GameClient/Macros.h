#pragma once

// Windows Header Files:
#include <Windows.h>

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

#ifndef RETURN_FAILED_HRESULT
#define RETURN_FAILED_HRESULT(result) if(FAILED((HRESULT)(result))) return result
#endif

#ifndef RETURN_TUPLE_ON_FAILED_HRESULT
#define RETURN_TUPLE_ON_FAILED_HRESULT(result) if(FAILED((HRESULT)(std::get<0>(result)))) return result
#endif
