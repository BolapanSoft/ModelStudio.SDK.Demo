#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"
#include "CSProjectBuildingHierarchyConstants.h"
#include "..\mstStructureDataHierarchyBase\constants.h"

namespace MStudioBuildingHierarchy
{
	//Интерфейс объекта работы с подсистемой "Здания и сооружения"
	//Иерархия Площадка(Генплан) -> Здание(Сооружение) -> Этажи -> Помещения(Зоны)
	//+ Блоки(Узлы), которые могут быть связаны с несколькими помещениями
	//Помещения могут принадлежать напрямую зданию без этажей
	__interface IPBH: public IUnknown
	{
		//Текущая БД (может быть NULL)
		HRESULT GetDB(MStudioDB::IDataBase** pResDb);
		//Установка текущей БД (может быть NULL)
		//Если изменить БД после загрузки, то все связи объектов иерархии с исходной БД будут потеряны
		//что приведёт к невозможности применить иерархию к существующим объектам
		HRESULT SetDB(MStudioDB::IDataBase* pDb);

		//--------GUI-------------------------------------------
		//Показ диалога редактирования иерархии
		int ShowHierarchyEditDialog(HWND hParentWnd, int nRootObjectId);
		//Показывает диалог выбора(только чтение) объекта иерархии 
		int ShowHierarchySelectDialog(HWND hParentWnd, int nRootObjectId);
		int ShowHierarchySiteSelectDialog(HWND hParentWnd, int nRootObjectId);
		int ShowHierarchyBuildingSelectDialog(HWND hParentWnd, int nRootObjectId);
		//Показ немодального диалогового окна перекрестной фильтрации иерархий
		HRESULT ShowHierarchyFilterDialog(HWND hParentWnd, HierarchyGraphicsFilterCallback callback);
		//Не относится к ЗиС, нужно только для связи фабрики с настройками
		void CollectObjectsFactoryData();

		//legacy
		//Возвращает корневой элемент иерархии, содержащий список площадок на верхнем уровне
		HRESULT GetRootElement(MStudioData::IElement** pResElement);
		//Создаёт или получает вид связи объекта с иерархией
		int GetOrCreateObjectToStructLinkType(MStudioDB::IObjectRelationType** pResLinkType);
	};

	//Класс утилит работы с БД CadLib Проект.
	//!ВРЕМЕННО здесь, т.к. нет отдельного модуля расшаринного с МиА для CLP
	__interface IProjectDBUtils: public IUnknown
	{
		//0. Обновление иерархий ЗиС и РП (открыть/закрыть)
		HRESULT UpdateBldAndPSH();
		//1. Создание публикаций для старых файлов, где их небыло (см. описание внизу)
		HRESULT CreatePublicationsForOldDB();
		//2.Обновление старых версий публикации
		bool HasOldPublications(); //имеются ли публикации, чтобы показать предупреждение и диалог ЗиС
		HRESULT UpdateOldPublications();
		//3. Добавление/проверка параметра актуальности последней публикации (и связи с файлом)
		HRESULT CheckAndUpdateActualPublications();
		//4. Удаление неиспользуемых сеток
		HRESULT DeleteUnusedMeshes();
	};

//Внимание! Новые методы интерфейсов разрешено добавлять ТОЛЬКО в конец!
#define MSTUDIO_PBH_API_CUR_VER_MAJOR 1
#define MSTUDIO_PBH_API_CUR_VER_MINOR 6

	__interface IFactoryInterface
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсов внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_PBH_API_CUR_VER_MAJOR и MSTUDIO_PBH_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Создание нового объекта для работы с подсистемой "Здания и сооружения"
		HRESULT CreatePBH(IPBH **pNew);

		HRESULT CreateProjectDBUtils(MStudioDB::IDataBase *pDb, MStudioData::IProgressWnd *pProgress,
			IProjectDBUtils **pNew);
	};

#define MODEL_STUDIO_PBH_MODULE_NAME L"mstProjectBuildingHierarchy.dll"
#define MODEL_STUDIO_PBH_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PBH_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PBH_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_PBH_API_CUR_VER_MAJOR, MSTUDIO_PBH_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_PBH_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_PBH_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_PBH_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_PBH_API_CUR_VER_MAJOR, MSTUDIO_PBH_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}