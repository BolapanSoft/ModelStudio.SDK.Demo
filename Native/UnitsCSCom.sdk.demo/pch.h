﻿// (C) Copyright 2002-2003 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

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

#if _MSC_VER < 1600
//----- Modify the following defines if you have to target a platform prior to the ones specified below.
//----- Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER					//----- Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0501			//----- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT			//----- Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0501		//----- Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS			//----- Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410	//----- Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE				//----- Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0600		//----- Change this to the appropriate value to target IE 5.0 or later.
#endif


#else 

//- Modify the following defines if you have to target a platform prior to the ones specified below.
//- Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              //- Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0501     //- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef _WIN32_WINDOWS			//----- Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0501	//----- Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE				//----- Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0501		//----- Change this to the appropriate value to target IE 5.0 or later.
#endif

#endif
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
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
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
#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif

//-----------------------------------------------------------------------------
//----- Include ObjectDBX/ObjectARX headers
//----- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_			//- Support for the BRep API
//#define _HLR_SUPPORT_				//- Support for the Hidden Line Removal API
//#define _IE_SDK_SUPPORT_			//- Support for the Autodesk Image Engine API
//#define _AMODELER_SUPPORT_		//- Support for the AModeler API
//#include <amodeler.h>
#include "dbxHeaders.h"
#include "AcExtensionModule.h" //- Needed for AutoCAD MFC extension even id not present in DBX SDK

//#include <afxmt.h>
#include <dbmain.h>
#include <aced.h>
#include <SchxTpl.h>
#include <Arx2010Comp.h>

class AcDbIdMapping;
class CFastUniqueObjectIdContainer;
extern AcGeMatrix3d  GlobalUCSMatrix;
extern HINSTANCE _hUnitCsInstance;
#include "..\Common\ppLocalizeDef.h" //_LOCALIZE definition there

#ifdef _LOCALIZE

#include "..\msData\Localization.h"
#define GET_STRING(uintID) GetStringLang(_hUnitCsInstance, uintID) //returns CString from string table
#define LOAD_STRING_LOC(str, uintID) str = GetStringLang(_hUnitCsInstance, uintID)

#else

#include "HcStrings.h"
#define GET_STRING(id) _##id  //constant string from above file (by identifier)
#define LOAD_STRING_LOC(str, uintID) str.LoadString(_hUnitCsInstance,uintID)

#endif

