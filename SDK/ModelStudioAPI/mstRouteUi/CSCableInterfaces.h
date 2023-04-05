#pragma once

#include "..\msData\CSDataInterfaces.h"

namespace MStudioCable
{
	__interface IJournalCable; //forward declaration
	
	//Полка кабельного графа (ребро) с информацией о кабелях
	__interface IJournalEdge: public IUnknown
	{
		//Получение идентификатора объекта лотка (прототипа)
		AcDbObjectId GetTrayId();
		//Получение идентификатора полки на лотке (прототипе)
		int GetShelfId();

		//Длина полки
		double GetLength();
		//Ширина полки
		double GetWidth();
		//Высота полки
		double GetHeight();

		HRESULT GetBuilding(BSTR *pStrRes);

		int GetDivisionsCount();
		HRESULT GetDivisionAt(int nDivisionIndex, BSTR* pStrRes);

		//Количество кабелей, проложенных по полке
		int GetCablesCount();
		//Получение информации о проложенном кабеле по индексу
		HRESULT GetCableAt(int nCableIndex, IJournalCable** pResCable);
	};

	//Информация об участке пути кабеля
	__interface ICableOnTrayInfo: public IUnknown
	{
		//Получение идентификатора объекта лотка (прототипа)
		AcDbObjectId GetTrayId();
		//Получение идентификатора полки на лотке (прототипе)
		int GetShelfId();

		//Длина кабеля, находящегося на полке
		double GetLength();
		//Положение кабеля на полке по вертикали
		double GetHorizontalPosition();
		//Положение кабеля на полке по горизонтали
		double GetVerticalPosition();

		//Получение минимальной высоты кабеля в мировых координатах
		double GetHeightMin();
		//Получение максимальной высоты кабеля в мировых координатах
		double GetHeightMax();

		//Получение высоты полки
		double GetTrayHeight();
		//Получение ширины полки
		double GetTrayWidth();
	};

	//Информация о прокладке кабеля
	__interface IJournalCable: public IUnknown
	{
		//Получение идентификатора объекта кабеля
		AcDbObjectId GetCableId();
		//Получение идентификатора узла, к которому подключено начало кабеля
		AcDbObjectId GetNodeStartId();
		//Получение идентификатора узла, к которому подключен конец кабеля
		AcDbObjectId GetNodeEndId();

		//Радиус кабеля
		double GetRadius();

		HRESULT GetAbbriviation(BSTR *pStrRes);
		HRESULT GetDivision(BSTR *pStrRes);

		//Группа
		UINT GetGoroup();

		//Получение количество участков пути, по которым проложен кабель
		int GetTraysCount();
		//Получение информации об участке пути прокладки кабеля по индексу
		HRESULT GetTrayAt(int nTrayIndex, ICableOnTrayInfo** pResInfo);
	};

	//Интерфейс класса кабельного журнала
	__interface ICableJournal: public IUnknown
	{
		//Инициализирует кабельный журнал, анализируя данные текущей модели автокада
		HRESULT Init();

		//Получение количества полок (рёбер) кабельного графа 
		int GetEdgesCount();
		//Получение полки (ребра) кабельного графа по индексу
		HRESULT GetEdgeAt(int nEdgeIndex, IJournalEdge** pResEdge);

		//Получение количества кабелей в журнале
		int GetCablesCount();
		//Получение кабеля по индексу
		HRESULT GetCableAt(int nCableIndex, IJournalCable** pResCable);
	};


#define MSTUDIO_CABLE_API_CUR_VER_MAJOR 1
#define MSTUDIO_CABLE_API_CUR_VER_MINOR 7

	__interface IFactoryInterface
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_CABLE_API_CUR_VER_MAJOR и MSTUDIO_CABLE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Создание нового объекта кабельного журнала
		HRESULT CreateCableJournal(ICableJournal** pNewCableJournal);

		//Получение класса кабеля (mstCable)
		AcRxClass* GetCableClass();
		//Получение класс прототипа (mstRoutePrototype)
		AcRxClass* GetPrototypeClass();
		//Получение базового класса конструкции прототипа - опоры и т.д.(mstRouteConstructionBase)
		AcRxClass* GetPrototypeConstructionBaseClass();
	};

#ifndef NCAD
#define MODEL_STUDIO_CABLE_MODULE_NAME L"mstRouteUi.arx"
#else
#define MODEL_STUDIO_CABLE_MODULE_NAME L"mstRouteUi.nrx"
#endif 
#define MODEL_STUDIO_CABLE_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_CABLE_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_CABLE_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_CABLE_API_CUR_VER_MAJOR, MSTUDIO_CABLE_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_CABLE_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_CABLE_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_CABLE_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_CABLE_API_CUR_VER_MAJOR, MSTUDIO_CABLE_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}