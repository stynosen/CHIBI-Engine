#pragma once

// Let VC++ know we are compiling for WinXP and up.  This let's us use
// API functions specific to WinXP (e.g., WM_INPUT API).
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0600 // Vista
#endif


// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.  
// This makes D3D objects work well in the debugger watch window, but slows down 
// performance slightly.
#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#include <d2d1.h>
#include <d3d10_1.h>
#include <d3dx10.h>
#include <dwrite_1.h>
#include <D3DX10Core.h>
#include <D3DX10Math.h>
#include <Wincodec.h>
#include <tchar.h>
#include <windows.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "Windowscodecs.lib")

#include <dxerr.h>
#pragma comment(lib, "dxerr.lib")

#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>

#ifdef _UNICODE	// extra unicode defines
#define tstring wstring
#define tcin wcin
#define tcout wcout
#define tstringstream wstringstream
#define tostringstream wostringstream
#define tofstream wofstream
#define tifstream wifstream
#define tfstream wfstream
#define tstrtod wcstod
#define tstrtol wcstol
#define tchar wchar_t 
#define tstrcmp wcscmp
#define tstrcpy_s wcscpy_s
#define tfopen _wfopen_s
#define tstrtod	wcstod
#define tof _wtof 
#else
#define tstring string
#define tcin cin
#define tcout cout
#define tstringstream stringstream
#define tostringstream ostringstream
#define tofstream ofstream
#define tifstream ifstream
#define tfstream fstream
#define tstrod strtod
#define tstrtol strtol
#define tchar char 
#define tstrcmp strcmp
#define tstrcpy_s strcpy_s
#define tfopen fopen_s
#define	tstrtod strtod
#define tof atof
#endif

//*****************************************************************************
// Math Constants
//*****************************************************************************
#ifndef INFINITE
#define INFINITE = 0xFFFFFFFF;
#endif

const float EPSILON = 0.0001f;

#ifndef PI
#define PI = (3.14159265358979323846);
#endif

//*****************************************************************************
// Use of lambdas
//*****************************************************************************

#ifndef Action
#undef Action
#endif

typedef std::function<void()> Action;

//Macro for a lambda to a class method
#ifndef LocalLambda
#undef LocalLambda
#endif

#define LocalAction(function) \
	[&]() -> void {function(); }

//*****************************************************************************
//Declare templates for releasing interfaces and deleting objects 
//*****************************************************************************
template<typename T>
inline void SafeRelease(T &pInterfaceToRelease)
{
	if (pInterfaceToRelease != nullptr)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = nullptr;
	}
}
template<typename T>
inline void SafeRelease(T &pInterfaceToRelease,ULONG& result)
{
	if (pInterfaceToRelease != nullptr)
	{
		#if defined(DEBUG) | defined(_DEBUG)
			result = pInterfaceToRelease->Release();
		#else
			pInterfaceToRelease->Release();
		#endif
		pInterfaceToRelease = nullptr;
	}
}
template<typename T>
inline void SafeDelete(T &pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

//*****************************************************************************
// Assert Macro stdafx.h
//*****************************************************************************

// ASSERT macro
#if defined(_WIN64)
#ifndef NDEBUG
#define ASSERT \
if (false) {} \
	else \
struct LocalAssert {
\
int mLine; \
LocalAssert(int line = __LINE__) : mLine(line) {} \
LocalAssert(bool isOK, const TCHAR* message = _T("")) {
	\
	if (!isOK) {
		\
			tstringstream buffer; \
			buffer << _T("ERROR!! Assert failed on line ") << LocalAssert().mLine << _T(" in file '") << __FILE__ << _T("'\nBoodschap: \"") << message << _T("\"\n"); \
			OutputDebugString(buffer.str().c_str()); \
			__debugbreak(); \
	} \
} \
} myAsserter = LocalAssert
#else
#define ASSERT \
if (true) {}
 else \
 struct NoAssert {
	 \
	 NoAssert(bool isOK, const TCHAR* message = _T("")) {} \
 } myAsserter = NoAssert
#endif
#else
#ifndef NDEBUG
#define ASSERT \
if (false) {} \
	else \
struct LocalAssert { \
	int mLine; \
	LocalAssert(int line = __LINE__) : mLine(line) {} \
	LocalAssert(bool isOK, const TCHAR* message = _T("")) { \
if (!isOK) { \
	tstringstream buffer; \
	buffer << _T("ERROR!! Assert failed on line ") << LocalAssert().mLine << _T(" in file '") << __FILE__ << _T("'\nBoodschap: \"") << message << _T("\"\n"); \
	OutputDebugString(buffer.str().c_str()); \
	__asm { int 3 } \
} \
	} \
} myAsserter = LocalAssert
#else
#define ASSERT \
if (true) {} \
 else \
struct NoAssert { \
	NoAssert(bool isOK, const TCHAR* message = _T("")) {} \
} myAsserter = NoAssert 
#endif
#endif

//*****************************************************************************
// HR macro
//*****************************************************************************

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
{ \
	HRESULT hr = (x);                                      \
if (FAILED(hr))                                         \
{                                                      \
	DXTrace(__FILE__, (DWORD)__LINE__, hr, _T(#x), true); \
}                                                      \
}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

//*****************************************************************************
// Dynamic cast method
//*****************************************************************************
template <typename T, typename I>
T DCAST(I objectPtr)
{
	T dObjectPtr = dynamic_cast<T>(objectPtr);
	ASSERT(dObjectPtr != nullptr, _T("Mismatching object type"));
	return dObjectPtr;
}