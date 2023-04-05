#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"

//Интерфейсы для работы с инфраструктурой ModelStudio
namespace MStudioCore
{
#define MSTUDIO_CORE_API_CUR_VER_MAJOR 1
#define MSTUDIO_CORE_API_CUR_VER_MINOR 7

	__interface IMStudioCore
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_CORE_API_CUR_VER_MAJOR и MSTUDIO_CORE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Проверяет имеется ли возможность получить параметры данной сущности (является ли объектом ModelStudio)
		bool IsDataObject(AcDbObject* pObj);
		//Проверяет имеется ли возможность получить параметры данной сущности (является ли объектом ModelStudio)
		bool IsDataObject(const AcDbObjectId& idObj);

		//---Работа с параметрами объекта----------------------------------------------------------
		//Получение дерева параметров объекта по ObjectId
		//В случае, если объект не поддерживает извлечение параметров или произошла ошибка возвращает S_FALSE
		HRESULT GetObjectParameters(const AcDbObjectId& idObject, MStudioData::IElement **pResParams, void* pContext=NULL);

		//Получение дерева параметров объекта
		//В случае, если объект не поддерживает извлечение параметров или произошла ошибка возвращает S_FALSE
		HRESULT GetObjectParameters(AcDbObject* pObj, MStudioData::IElement **pResParams, void* pContext=NULL);

		//Получение описания объекта в соответствии с формулой из настроек (показывается во всплывающей подсказке)
		//В случае, если объект не поддерживает извлечение параметров или произошла ошибка возвращает S_FALSE
		HRESULT GetObjectDescription(AcDbObject* pObject, BSTR* pStrResult);
		//Получение имени объекта
		//В случае, если объект не поддерживает извлечение параметров или произошла ошибка возвращает S_FALSE
		HRESULT GetObjectName(AcDbObject* pObject, BSTR* pStrResult);

		//Замена всего дерева параметров объекта
		//idObject - идентификатор объекта
		//pParams - дерево параметров, которое необходимо применить
		//bStandard - устанавливается в true, если объект вставляется из библиотеки, иначе false (для отслеживания изменения стандартного объекта)
		//В случае, если объект не поддерживает задание параметров или произошла ошибка возвращает S_FALSE
		HRESULT SetObjectParameters(const AcDbObjectId& idObject, MStudioData::IElement *pParams, bool bStandard);

		//Замена всего дерева параметров объекта
		//pDestObject - объект назначения
		//pParams - дерево параметров, которое необходимо применить
		//bStandard - устанавливается в true, если объект вставляется из библиотеки, иначе false (для отслеживания изменения стандартного объекта)
		//В случае, если объект не поддерживает задание параметров или произошла ошибка возвращает S_FALSE
		HRESULT SetObjectParameters(AcDbObject* pDestObject, MStudioData::IElement *pParams, bool bStandard);

		//Изменение параметров, определённых в pParams - будут применены только указанные параметры
		//idObject - идентификатор объекта
		//pParams - параметры объекта для применения (см. IParamsOwner::ApplyParameter)
		//bStandard - устанавливается в true, если объект вставляется из библиотеки, иначе false (для отслеживания изменения стандартного объекта)
		//В случае, если объект не поддерживает задание параметров или произошла ошибка возвращает S_FALSE
		HRESULT SetObjectParameters(const AcDbObjectId& idObject, MStudioData::IParamsOwner *pParams, bool bStandard);

		//Изменение параметров, определённых в pParams - будут применены только указанные параметры
		//pDestObject - объект назначения
		//pParams - параметры объекта для применения (см. IParamsOwner::ApplyParameter)
		//bStandard - устанавливается в true, если объект вставляется из библиотеки, иначе false (для отслеживания изменения стандартного объекта)
		//В случае, если объект не поддерживает задание параметров или произошла ошибка возвращает S_FALSE
		HRESULT SetObjectParameters(AcDbObject* pDestObject, MStudioData::IParamsOwner *pParams, bool bStandard);

		//---Работа с GUID объекта-----------------------------------------------------------------
		//Возвращает GUID объекта (присваивается при публикации модели в БД с сохранением связи с БД) или GUID_NULL
		GUID GetObjectGUID(const AcDbObject* pEnt);

		//Устанавливает новый GUID объекту (через XData)
		HRESULT SetObjectGUID(AcDbObject* pEnt, GUID guid);

		//---Расположение объекта в пространстве---------------------------------------------------
		//Получает минимальный ограничивающий параллелепипед по объекту
		//pEnt - сущность для получения AABB
		//ptOrig, vX, vY, vZ - результирующая исходная точка и оси прямоугольника
		//В случае ошибка возвращает S_FALSE
		HRESULT GetEntityBoundingBox(const AcDbEntity* pEnt, AcGePoint3d& ptOrig, AcGeVector3d& vX, AcGeVector3d& vY, AcGeVector3d& vZ);

		//Возвращает исходную точку сущности
		//pEnt - сущность для получения исходной точки
		//ptOrig - результирующая исходная точка сущности
		//В случае ошибка возвращает S_FALSE
		HRESULT GetEntityOrigin(const AcDbEntity* pEnt, AcGePoint3d& ptOrig);
	};

#ifndef NCAD
#define MODEL_STUDIO_CORE_MODULE_NAME L"UnitsCS.dbx"
#else
#define MODEL_STUDIO_CORE_MODULE_NAME L"UnitsCS.nrx"
#endif 
#define MODEL_STUDIO_CORE_ENTRY_NAME "GetMStudioCoreInterface"

	//Класс для получения базового интерфейса API ModelStudio данного модуля
	//модуль уже должен быть загружен в память
	class CMStudioDataInterface
	{
	public:
		typedef IMStudioCore* MSTPluginEntryFn(int nClientMajorVer, int nClientMinorVer);

		//Получение базового интерфейса API ModelStudio данного модуля
		//Если установлен bCheckVersion, то будет произведена проверка совместимости версии загруженного
		//модуля с версией API и в случае несовместимости выброшено исключение типа CString
		static IMStudioCore* Get(bool bCheckVersion=true)
		{
			//Значение кэшируется внутри каждого клиентского модуля
			static IMStudioCore* pRes = NULL;
			if (pRes)
				return pRes;

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_CORE_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_CORE_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_CORE_API_CUR_VER_MAJOR, MSTUDIO_CORE_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_CORE_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_CORE_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_CORE_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_CORE_API_CUR_VER_MAJOR, MSTUDIO_CORE_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}