﻿// EmptyMFCLibrary.h: основной файл заголовка для библиотеки DLL EmptyMFCLibrary
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CEmptyMFCLibraryApp
// Реализацию этого класса см. в файле EmptyMFCLibrary.cpp
//

class CEmptyMFCLibraryApp : public CWinApp
{
public:
	CEmptyMFCLibraryApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
