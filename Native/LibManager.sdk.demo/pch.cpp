// pch.cpp: source file corresponding to the pre-compiled header

#include "pch.h"

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.


//-----------------------------------------------------------------------------
//----- StdAfx.h : include file for standard system include files,
//-----      or project specific include files that are used frequently,
//-----      but are changed infrequently
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#ifdef _FULLDEBUG_
#pragma message ("Warning! You should not run this application in a Standard AutoCAD release.")
#pragma message ("         Due to the memory managment constraints.")
#endif

#pragma warning(disable: 4786)
//#pragma warning(disable: 4098)

//-----------------------------------------------------------------------------
#define STRICT

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			//----- Exclude rarely-used stuff from Windows headers
#endif

//----- Modify the following defines if you have to target a platform prior to the ones specified below.
//----- Refer to MSDN for the latest info on corresponding values for different platforms.
#define WINVER 0x0501			//----- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#define _WIN32_WINNT 0x0501		//----- Change this to the appropriate value to target Windows 2000 or later.
#define _WIN32_WINDOWS 0x0410	//----- Change this to the appropriate value to target Windows Me or later.
#define _WIN32_IE 0x0600		//----- Change this to the appropriate value to target IE 5.0 or later.

//-----------------------------------------------------------------------------
#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	//----- Some CString constructors will be explicit
//----- Turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

//-----------------------------------------------------------------------------
//----- 'DEBUG workaround' below prevents the MFC or ATL #include-s from pulling 
//----- in "Afx.h" that would force the debug CRT through #pragma-s.
#if defined(_DEBUG) && !defined(_FULLDEBUG_)
#define _DEBUG_WAS_DEFINED
#define _DISABLE_MFC_ASSERT
#undef _DEBUG
#pragma message ("     Compiling MFC / STL / ATL header files in release mode.")
#endif

//----- ObjectARX and OMF headers needs this
#include <map>
//#include <aduiPaletteSet.h>
//#include <aduiPalette.h>

//-----------------------------------------------------------------------------
#include <afxwin.h>				//----- MFC core and standard components
#include <afxext.h>				//----- MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>				//----- MFC OLE classes
#include <afxodlgs.h>			//----- MFC OLE dialog classes
#include <afxdisp.h>			//----- MFC Automation classes
#endif //----- _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>				//----- MFC ODBC database classes
#endif //----- _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>				//----- MFC DAO database classes
#endif //----- _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>			//----- MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>				//----- MFC support for Windows Common Controls
#endif //----- _AFX_NO_AFXCMN_SUPPORT

//-----------------------------------------------------------------------------
#include <AtlBase.h>
#include <AtlCom.h>
/*#ifdef _ARXVER_2008
#include <atlchecked.h>
#endif*/
using namespace ATL;

//-----------------------------------------------------------------------------
#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

#define _USE_MATH_DEFINES
#include <math.h>
//-----------------------------------------------------------------------------
//----- Include ObjectDBX/ObjectARX headers
//----- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_			//- Support for the BRep API
//#define _HLR_SUPPORT_				//- Support for the Hidden Line Removal API
//#define _IE_SDK_SUPPORT_			//- Support for the Autodesk Image Engine API
//#define _AMODELER_SUPPORT_		//- Support for the AModeler API
//#define _ASE_SUPPORT_				//- Support for the ASI/ASE API
//#define _RENDER_SUPPORT_			//- Support for the AutoCAD Render API
//#define _ARX_CUSTOM_DRAG_N_DROP_	//- Support for the ObjectARX Drag'n Drop API
//#define _INC_LEAGACY_HEADERS_		//- Include legacy headers in this project
#include "arxHeaders.h"
//-----------------------------------------------------------------------------
//#include "DocData.h" //----- Your document specific data class holder
#include "..\msData\ParamDefs.h"
#include "..\msData\paramsObject.h"
#include "..\Params\Params.h"
#include "..\msData\Function.h"
//----- Declare it as an extern here so that it becomes available in all modules
//

//-----------------------------------------------------------------------------
extern HINSTANCE _hLibmanInstance;
#include "..\Common\ppLocalizeDef.h" //_LOCALIZE definition there


#ifdef _LOCALIZE

#include "..\msData\Localization.h"

#ifdef _DEBUG
#pragma comment( lib, "..\\lib\\Debug\\mstudioData.lib")
#elif defined NDEBUG
#pragma comment( lib, "..\\lib\\Release\\mstudioData.lib")
#endif

#define GET_STRING(uintID) GetStringLang(_hLibmanInstance, uintID) //returns CString from string table
#define LOAD_STRING_LOC(str, uintID) str = GetStringLang(_hLibmanInstance, uintID)

#else

#include "HcStrings.h"
#define GET_STRING(id) _##id  //constant string from above file (by identifier)
#define LOAD_STRING_LOC(str, uintID) str.LoadString(_hLibmanInstance,uintID)

#endif