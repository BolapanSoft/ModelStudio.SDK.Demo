#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"
#include "CSProjectStructureHierarchyConstants.h"

namespace MStudioStructureHierarchy
{
	//Интерфейс объекта подсистемы "Структура разделов проекта"
	//Иерархия Разделы проекта -> Раздел проекта -> Подраздел -> Часть
	__interface IPSH: public IUnknown
	{
		//Текущая БД (может быть NULL)
		HRESULT GetDB(MStudioDB::IDataBase** pResDb);
		//Установка текущей БД (может быть NULL)
		//Если изменить БД после загрузки, то все связи объектов иерархии с исходной БД будут потеряны
		//что приведёт к невозможности применить иерархию к существующим объектам
		HRESULT SetDB(MStudioDB::IDataBase* pDb);

		//--------GUI----------------------------------------
		//Показ диалога редактирования иерархии
		int ShowHierarchyEditDialog(HWND hParentWnd, int nRootObjectId);
		//Показывает диалог выбора объекта иерархии(только чтение)
		int ShowHierarchySelectDialog(HWND hParentWnd, int nRootObjectId);

		//Импортирует иерархию из файла, удаляя всё содержимое текущей иерархии
		bool XmlImportFromFile(LPCTSTR pszFileName);	
	};

//Внимание! Новые методы интерфейсов разрешено добавлять ТОЛЬКО в конец!
#define MSTUDIO_PSH_API_CUR_VER_MAJOR 1
#define MSTUDIO_PSH_API_CUR_VER_MINOR 3

	__interface IFactoryInterface
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсов внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_PSH_API_CUR_VER_MAJOR и MSTUDIO_PSH_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Создание нового объекта для работы с подсистемой "Здания и сооружения"
		HRESULT CreatePBH(IPSH** pNew);
	};

#define MODEL_STUDIO_PSH_MODULE_NAME L"mstProjectStructureHierarchy.dll"
#define MODEL_STUDIO_PSH_ENTRY_NAME "GetMStudioDataInterface"

	//Класс для получения базового интерфейса API ModelStudio данного модуля
	//модуль уже должен быть загружен в память
	class CMStudioDataInterface
	{
	public:
		typedef IFactoryInterface* PASCAL MSTPluginEntryFn(int nClientMajorVer, int nClientMinorVer);

		//Получение базового интерфейса API ModelStudio данного модуля
		//Если установлен bCheckVersion, то будет произведена проверка совместимости версии загруженного
		//модуля с версией API и в случае несовместимости выброшено исключение типа CString
		static IFactoryInterface* Get(bool bCheckVersion=true)
		{
			//Значение кэшируется внутри каждого клиентского модуля
			static IFactoryInterface* pRes = NULL;
			if (pRes)
				return pRes;

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PSH_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PSH_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_PSH_API_CUR_VER_MAJOR, MSTUDIO_PSH_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_PSH_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_PSH_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_PSH_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_PSH_API_CUR_VER_MAJOR, MSTUDIO_PSH_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}