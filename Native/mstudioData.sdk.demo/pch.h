// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

#define _AFX_NO_OLE_SUPPORT

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

#ifdef NOINTERLOCKEDINC
{
long __cdecl _InterlockedIncrement(long volatile* pn);
long __cdecl _InterlockedDecrement(long volatile* pn);
}

inline long InterlockedIncrement(long volatile* pn) { return _InterlockedIncrement(pn); }
inline long InterlockedDecrement(long volatile* pn) { return _InterlockedDecrement(pn); }
#endif
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//Упрощённая версия проверки
#define CS_CHECK_NOTNULL(var) if (var==nullptr) {CString strErrMsg; strErrMsg.Format(L"Error: %s can't be NULL. Disposed object using possible."); throw CString(L#var);}
#define CS_CHECK_HR(expr) {HRESULT hrChk=expr; if (FAILED(hrChk)) {CString strMsg; strMsg.Format(L"Error executing expression %s: hr=%d", L#expr, hrChk); throw strMsg;}}

//Ловит CString и остальные исключения и выкидывает System::Exception
#define MST_API_CATCH(errorMsg)catch (CString& strException)\
{throw gcnew System::Exception(gcnew String(strException));}\
catch (...){throw gcnew System::Exception(errorMsg);}
#endif //PCH_H