// LibManager.sdk.demo.h: основной файл заголовка для библиотеки DLL LibManager.sdk.demo
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLibManagersdkdemoApp
// Реализацию этого класса см. в файле LibManager.sdk.demo.cpp
//

class CLibManagersdkdemoApp : public CWinApp
{
public:
	CLibManagersdkdemoApp();

// Переопределение
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
