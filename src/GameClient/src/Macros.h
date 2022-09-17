#pragma once

// Windows Header Files:
#include <Windows.h>

#include <wincodec.h>

#ifndef HINST_THISCOMPONENT
EXTERN_C const IMAGE_DOS_HEADER __ImageBase;
// NOLINT(clang-diagnostic-reserved-identifier, bugprone-reserved-identifier)
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#ifndef RETURN_FAILED_HRESULT
#define RETURN_FAILED_HRESULT(result) if(FAILED((HRESULT)(result))) return result
#endif
