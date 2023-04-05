﻿// LibManager.sdk.demo.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "LibManager.sdk.demo.h"
#include "CppUnitTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CLibManagersdkdemoApp

BEGIN_MESSAGE_MAP(CLibManagersdkdemoApp, CWinApp)
END_MESSAGE_MAP()


// Создание CLibManagersdkdemoApp

CLibManagersdkdemoApp::CLibManagersdkdemoApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CLibManagersdkdemoApp

CLibManagersdkdemoApp theApp;


// Инициализация CLibManagersdkdemoApp

BOOL CLibManagersdkdemoApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

namespace LibManagersdk{
    TEST_CLASS(LibManager) {
        TEST_METHOD(TestMethod1)
        {
        }
    };
}