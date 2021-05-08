#pragma once
#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include "targetver.h"

// Windows 헤더 파일
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>

#define TO_STRING(str) #str
#define SAFE_DELETE(p)				{ if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p)		{ if(p) { delete[] (p); (p) = nullptr; }}
#define SAFE_RELEASE(p)				{ if(p) { (p)->Release(); (p) = nullptr; }}

#if defined _DEBUG
#define HResult(hr)										\
{														\
	if (FAILED((HRESULT)hr)) {							\
		std::wstring filePath = __FILEW__;				\
		filePath = filePath.substr(filePath.find_last_of(L"/\\") + 1);	\
		wprintf(L"[%ls\t:\t%d]", filePath.c_str(), __LINE__);			\
		LPWSTR str = nullptr;							\
		FormatMessage(									\
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,	\
			nullptr,													\
			hr,															\
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),					\
			str,														\
			0,															\
			nullptr);													\
			MessageBox(nullptr, str, L"Error", MB_OK);					\
		return hr;														\
}	}																	\

#define HThrow(hr)										\
{														\
	HRESULT hResult = (HRESULT)hr;						\
	if (FAILED(hResult)) {								\
		std::wstring filePath = __FILEW__;				\
		filePath = filePath.substr(filePath.find_last_of(L"/\\") + 1);	\
		wprintf(L"[%ls\t:\t%d]", filePath.c_str(), __LINE__);			\
		_com_error err(hr);								\
		FormatMessage(									\
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,	\
			nullptr,													\
			0,															\
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),					\
			nullptr,													\
			0,															\
			nullptr);													\
			MessageBox(nullptr, err.ErrorMessage(), L"Error", MB_OK);	\
		throw hr;														\
}	}																	\

#else
#define HResult(hr) (hr)
#define HThrow(hr) { if (FAILED(hr)) throw hr; }
#endif

#include "Application.h"
#include "GraphicRenderer.h"
#include "MainEntryClass.h"
