#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"

//Интерфейсы для работы с параметрическим оборудованием
namespace MStudioPublish
{
	//Интерфейс класса настроек публикации
	__interface IPublicationSettings: IUnknown
	{
		//Сохраняет параметры в дереве
		void Save(MStudioData::IElement* pDestPublicationParams) const;
		//Загружает параметры из дерева
		void Load(const MStudioData::IElement* pPublicationParams);

		//Сохранение в файл (если не указан путь - используется каталог настроек)
		void SaveToXMLFile(BSTR strFileName) const;
		//Загрузка из файла (если не указан путь - используется файл из каталога настроек)
		bool LoadFromXMLFile(BSTR strFileName);

		//Сохранение в документ
		HRESULT SaveToDWG(AcDbDatabase *pDb) const;
		//Загрузка из документа (вернёт false если данные не найдены)
		bool LoadFromDWG(AcDbDatabase *pDb);
	};

	//Интерфейс объекта публикации
	__interface IPublisher: IUnknown
	{
		//Получение имени файла конфигурации (оттуда будет загружен конфиг перед публикацией)
		//Пустая строка - загрузка из DWG с показом диалога (диалог не показывается при загрузке из XML)
		HRESULT GetConfigFileName(BSTR* pFilePath) const;
		//Установка имени файла конфигурации (оттуда будет загружен конфиг перед публикацией)
		//Пустая строка - загрузка из DWG с показом диалога (диалог не показывается при загрузке из XML)
		HRESULT SetConfigFileName(BSTR pFilePath);

		//Режим работы из командной строки
		bool IsSilentMode() const;
		//Режим работы из командной строки (должен быть указан профиль SetPublicationSettingsPath())
		void SetSilentMode(bool bSilent);

		//Нужно ли создавать DWG из листа проекта
		bool IsCreateRepresentDWG() const;
		//Нужно ли создавать PDF из листа проекта
		bool IsCreateRepresentPDF() const;
		//Какой категории будет этот файл?
		CString GetRepresentDWGCat() const;
		//Какой категории будет этот файл?
		CString GetRepresentPDFCat() const;

		//Установка родительского окна для окна прогресса
		void SetProgressParentWnd(HWND hWnd);

		//--Следующие данные доступны только с начала момента публикации (в BeforePublishSpace)--

		//Получение БД назначения (в которую ведётся публикация)
		//Объект валиден только во время публикации
		HRESULT GetDestinationDB(MStudioDB::IDataBase **ppResDb);

		//Получение имени БД назначения для отчёта
		HRESULT GetDestinationDBName(BSTR* pResDB);

		//Получение текущих настроек публикации
		//Объект валиден только во время публикации
		HRESULT GetSettings(IPublicationSettings **pResSettings);

		//Информация о публикации
		//Общее число объектов для публикации (для вычисления процента готовности)
		int GetTotalObjectsCount() const;
		//Реальное количество добавленных в БД объектов
		int GetAddedObjectsCount() const; 
		//Реальное количество обновлённых объектов БД (если хранится связь с объектами)
		int GetUpdatedObjectsCount() const;
		//Нажал ли пользователь отмену
		bool IsAborted();

		//Добавляет связь указанного типа между двумя объектами
		//метод работает отложенно, т.к. в момент вызова реакторов объект БД ещё не создан
		void AddObjectsLinkDelayed(int nObject1Id, const GUID &object2UId, int nRelationTypeId);

		//Добавляет связь указанного типа между двумя объектами
		//метод работает отложенно, т.к. в момент вызова реакторов объект БД ещё не создан
		void AddObjectsLinkDelayed(int nObject1Id, int nObject2Id, int nRelationTypeId);

		//Добавляет связь указанного типа между двумя объектами
		//метод работает отложенно, т.к. в момент вызова реакторов объект БД ещё не создан
		void AddObjectsLinkDelayed(const GUID &object1UId, const GUID &object2UId, int nRelationTypeId);

		//Добавляет в очередь заявку на удаление всех связей данного типа для объекта
		void RemoveObjectLinksDelayed(int nObject1Id, int nRelationTypeId);

		//Публикует сущность автокада в БД
		//Данный метод безопасно вызывать из события BeforePublishSpace, т.к. к этому времени
		// уже готов контекст публикации
		//idEntityToPublish - идентификатор сущности для публикации		
		//mtTransformation - матрица трансформации сущности (рекомендуется
		//	передавать значение трансформации публикаии GetPublicationTransformation())
		//pParentBlockRef - открытый объект родительского блока
		// (для сущностей внутри блоков или NULL)
		//Публикация сущности вызовет все стандартные реакторы
		// (IsEntityForPublish, GetSmartObject, BeforeAddOrApplyObject, AfterAddOrApplyObject,
		//  PostProceesDumping, AfterDumpEntity)
		bool PublishEntity(const AcDbObjectId& idEntityToPublish,
			const AcGeMatrix3d &mtTransformation, const AcDbBlockReference *pParentBlockRef, bool b3DModelEntity = true, bool bPublishParams2d=false);
		//Получение ссылки на матрица трансформации публикации (данная матрица передаётся в 
		//	PublishEntity во время публикации сущностей каждого пространства)
		AcGeMatrix3d &GetPublicationTransformation();

		//публикует сущности одной сеткой
		//entities - cущности для публикации
		//mtTransformation - матрица трансформации сущности (рекомендуется
		//	передавать значение трансформации публикаии GetPublicationTransformation())
		//pParentBlockRef - открытый объект родительского блока
		bool PublishEntitiesOneMesh(const AcDbObjectIdArray& entities, const AcGeMatrix3d &mtTransformation, 
			const AcDbBlockReference *pParentBlockRef, bool b3DModelEntity = true, bool bPublish2dParams = false);
		
		//Добавление файла
		void AddObjectFileDelayed(int idObject, LPCTSTR szFileName, LPCTSTR szCat, LPCTSTR pszPath, bool bDeleteSrcAfterIns = false);
		void DetachFileDelayed(int idObject, int nIdFile);
	};

	//Интерфейс для объектов, которые можно зарегистрировать в качестве реакторов
	//на события публикации. Используется для добавления дополнительных связей и свойств к публикуемым сущностям и т.д.
	//В классе CEmptyPublishingReactor (внизу файла) интерфейс реализован с поведением по умолчанию
	__interface ICadLibPublishingReactor
	{
		//Вызывается в самом начале - непосредственно перед процессом публикации (для инициализации ресурсов)
		//bCancel - если установить в true, то процесс публикации будет отменён, последующие ректоры не будут вызваны
		void BeforePublishingStarted(IPublisher *pPublisher, bool &bCancel);

		//Вызывается после публикации всех объеков: всем объектам присвоены идентификаторы БД
		virtual void AfterPublishingEntities(MStudioPublish::IPublisher *pPublisher);

		//Вызывается после завершения публикации (или в случае отмены или ошибки) (для освобождения ресурсов)
		//bCanceled - true, если процесс публикации был отменён пользователем или плагином
		//bException - true, если процесс публикации прерван из-за возникшего исключения
		void AfterPublicationFinished(IPublisher *pPublisher, bool bCanceled, bool bException);

		//Вызывается перед началом публикации каждого блока (минимум один раз для ModelSpace)		
		//pPublisher - публикатор
		//idBlockToPublish - блок, который будет опубликован
		//arrSelection - список объекта пространства, который будет опубликован
		// (не включает внешние ссылки)
		//Если метод вернёт false, то публикация пространства произведена не будет, но данный метод
		// будет вызван у последующих реакторов.
		bool BeforePublishSpace(IPublisher *pPublisher, const AcDbObjectId& idBlockToPublish,
			AcDbObjectIdArray& arrSelection);

		//Вызывается после получения настроек (в т.ч. из диалога) и перед подключением к БД
		void AfterAcquireSettings(IPublisher *pPublisher);

		//Вызывается перед подключением к БД
		//Метод должен вернуть false по умолчанию
		// либо подключиться к БД и вернуть true
		bool CustomConnectToDestDB(IPublisher *pPublisher); //return false;

		//Вызывается после попытки подключения к БД назначения
		void AfterDbConnected(IPublisher *pPublisher);

		//Нужно ли публиковать сущность сущность pEnt или просто пропустить её
		//pEnt - открытая для чтения сущность
		//Метод должен вернуть true по умолчанию
		bool IsEntityForPublish(IPublisher *pPublisher, const AcDbBlockReference *pParentBlockRef,
			AcDbEntity* pEnt); //return true;

		//Метод должен вернуть true, если сущность pEnt является умным объектом (не подложка)
		//Для таких объектов не происходит извлечение параметров - публикуются параметры resParams, заполняемые
		//этим же методом
		//pEnt - открытая для чтения сущность
		//mtTransform - матрица трансформации на которую необходимо трансформировать объект для публикации в МСК
		//pResParams - дерево параметров, куда необходимо сохранить умный объект
		bool GetSmartObject(IPublisher *pPublisher, AcDbObject *pEnt, const AcGeMatrix3d& mtTransform,
			MStudioData::IElement *pResParams); //return false;

		//Данный метод вызывается непосредственно перед добавлением/обновлением объекта в БД
		//pEnt - открытая для чтения сущность
		//pObjectParameters - дерево параметров объекта для записи в БД (чтение/запись)
		//Метод должен вернуть true по умолчанию
		//Если метод возвращает false, то объект не будет опубликован/обновлён
		bool BeforeAddOrApplyObject(IPublisher *pPublisher, AcDbObject* pEnt,
			MStudioData::IElement *pObjectParameters); //return true;

		//Данный метод вызывается сразу после добавления/обновления объекта в БД, но до добавления
		// графики
		//pLibObject - образ созданного/обновлённого объекта в БД. На самом деле объект
		// может быть создан в любой момент публикации, т.к. загрузка объекта в БД - отложенное
		// действие поэтому, если объект новый, связь с ним можно установить только отложенно через
		// AddObjectsLinkDelayed
		//bNewObject - true, если объект был/будет добавлен в БД, иначе объект был обновлён
		//pEnt - открытая для чтения сущность
		//pObjectParameters - дерево параметров объекта для записи в БД (чтение)
		void AfterAddOrApplyObject(IPublisher *pPublisher, MStudioDB::ILibObjectInfo *pLibObject,
			bool bNewObject, AcDbObject* pEnt, MStudioData::IElement *pObjectParameters);

		//Вызывается после скачивания графики у сущностей перед добавлением графики в БД
		//pLibObject - образ созданного/обновлённого объекта в БД. На самом деле объект
		// может быть создан в любой момент публикации, т.к. загрузка объекта в БД - отложенное
		// действие поэтому, если объект новый, связь с ним можно установить только отложенно через
		//arrDumpedSet[nDumpedSetCount] - массив сущностей в наборе
		//pCurTopBlockRef - блок верхнего уровня или NULL
		//pParentBlockRef - блок - владелец сущностей или NULL
		//mtSetTransformation - матрица трансформации, которая будет применена сущностям
		//pDumper - указатель на объект дампера (пока нет интерфейса)
		void AfterDumpEntity(IPublisher *pPublisher, MStudioDB::ILibObjectInfo *pLibObject,
			AcDbEntity** arrDumpedSet, int nDumpedSetCount,
			const AcDbBlockReference *pTopBlockRef,	const AcDbBlockReference *pParentBlockRef,
			AcGeMatrix3d& mtSetTransformation,
			void* pDumper);

		//Вызывается после получения из настроек глобальной системы координат
		//На эту матрицу будут трансформированы все объект
		//позволяет сдвинуть трёхмерное представления сущности путём модификации матрицы трансформации mtTransform
		//(например в плагине системы координат документа (палитра "Текущие переменные"))
		void OnGetGloablTransformation(IPublisher *pPublisher, AcGeMatrix3d &mtTransform);

		
	};

#define MSTUDIO_PUBLISH_API_CUR_VER_MAJOR 2
#define MSTUDIO_PUBLISH_API_CUR_VER_MINOR 2

	__interface IFactoryInterface
	{
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_CORE_API_CUR_VER_MAJOR и MSTUDIO_CORE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Регистрация реактора публикации (методы реактора будут вызываться при всех публикациях в МиА или CadLib Проект)
		void RegisterPublishingReactor(ICadLibPublishingReactor* pReactor);

		//Отмена регистрации реактора публикации
		void UnregisterPublishingReactor(ICadLibPublishingReactor* pReactor);

		//Создаёт объект параметров публикации
		HRESULT CreatePublicationSettings(IPublicationSettings** ppNewObj);
	};

//Строковые константы

//Системное имя категории объекта в БД (используется при добавлении в БД)
#define OBJECT_DEFINE_CATEGORY _T("SYS_OBJECT_CATEGORY")
#define OBJECT_DEFINE_CATEGORY_CAPTION _T("Категория БД")

//Положение узла
#define NODE_POSITION			_T("NODE_POSITION")
#define NODE_POSITION_CAPTION	_T("Положение узла")
#define NODE_DIRECTION			_T("NODE_DIRECTION")
#define NODE_DIRECTION_CAPTION	_T("Направление узла")
#define NODE_NORMAL				_T("NODE_NORMAL")
#define	NODE_NORMAL_CAPTION		_T("Нормаль узла")


//---Параметры публикации (CSPublicationSettings)-------------------------------------------------
//Имя объекта типа AcDbXrecord в словаре чертежа для хранения параметров
#define PUBL_PARAMS_XOBJECT L"CSOFT_MS_PUBLICATION_PARAMS"

//Имя файла настроек "По умолчанию" в каталоге настроек
#define PUBL_PARAMS_DEFAULT_FILE L"db_publ_def_settings.xml"

#define PUBL_BD_SERVER_NAME_PARAM L"DB_SERVER_NAME"
#define PUBL_BD_SERVER_NAME_PARAM_TITLE L"Сервер"
#define PUBL_DB_NAME_PARAM L"DB_NAME"
#define PUBL_DB_NAME_PARAM_TITLE L"Имя БД"
#define PUBL_DB_USER_PARAM L"DB_USER"
#define PUBL_DB_USER_PARAM_TITLE L"Пользователь БД"

#define PUBL_ADDITIONAL_PARAMS_PARAM_NAME L"ADDITIONAL_PARAMS"
#define PUBL_ADDITIONAL_PARAM_ELEMENT_NAME L"ADDITIONAL_PARAM"
#define PUBL_ADDITIONAL_PARAMS_PARAM_TITLE L"Вычисляемые параметры"
#define PUBL_LAND_MODE_PARAM_NAME L"LAND_PUBLICATION_MODE"
#define PUBL_LAND_MODE_PARAM_TITLE L"Режим публикации"
#define PUBL_LAND_LAYERS_PARAM_NAME L"LAND_LAYERS"
#define PUBL_LAND_LAYERS_PARAM_TITLE L"Слои земли"
#define PUBL_LAND_SETUP_PLACEHOLDER_NAME L"LAND_SETUP_PLACEHOLDER"
#define PUBL_LAND_SETUP_PLACEHOLDER_TITLE L"Параметры"
#define PUBL_LAND_LAYERS_MASK_PARAM_NAME L"LAND_LAYERS_MASK"
#define PUBL_LAND_LAYERS_MASK_PARAM_TITLE L"Маска имени слоя"

#define PUBL_EXPLORE_XREFS_PARAM L"EXPLORE_XREFS"
#define PUBL_EXPLORE_XREFS_PARAM_TITLE L"Раскрывать блоки XRef"
#define PUBL_LINK_DRAWING_PARAM L"LINK_DRAWING_OBJECTS"
#define PUBL_LINK_DRAWING_PARAM_TITLE L"Сохранять связь объектов с документом"
#define PUBL_PUBLISH_INVISIBLE_PARAM L"PUBLISH_INVISIBLE_OBJECTS"
#define PUBL_PUBLISH_INVISIBLE_PARAM_TITLE L"Публиковать невидимые объекты"
#define PUBL_PUBLISH_LAYOUT_PARAM L"PUBLISH_LAYOUT_OBJECTS"
#define PUBL_PUBLISH_LAYOUT_PARAM_TITLE L"Публиковать листы"
#define PUBL_TAG_PREFIX_PARAM L"TAG_PREFIX"
#define PUBL_TAG_PREFIX_PARAM_TITLE L"Префикс тега публикации"

#define PUBL_SACLE_FACTOR_PARAM L"SACLE_FACTOR"
#define PUBL_SACLE_FACTOR_PARAM_TITLE L"Масштаб"
#define PUBL_SACLE_BASE_PT_PARAM L"SACLE_BASE_PT"
#define PUBL_SACLE_BASE_PT_PARAM_TITLE L"Базовая точка масштабирования"

#define PUBL_OFFSET_VT_PARAM L"OFFSET_VT"
#define PUBL_OFFSET_VT_PARAM_TITLE L"Смещение базовой точки"
#define PUBL_ROTATION_XY_PARAM L"ROTATION_XY"
#define PUBL_ROTATION_XY_PARAM_TITLE L"Поворот в XY"
#define PUBL_ROTATION_BASE_PT_PARAM L"ROTATION_BASE_PT"
#define PUBL_ROTATION_BASE_PT_PARAM_TITLE L"Базовая точка поворота" 

#define PUBL_LAND_SEPERATE_LANDS_BY_LAYERS_PARAM L"SEPERATE_LANDS_BY_LAYERS"
#define PUBL_LAND_SEPERATE_LANDS_BY_LAYERS_PARAM_TITLE L"Разделять рельефы по слоям"
//------------------------------------------------------------------------------------------------

//Дополнительные параметры публикации (профиль)
#define ALL_TABLES_ID -1
#define ALL_TABLES_NAME _T("all_objects")
#define ALL_TABLES_CAPTION _T("[Все объекты]")
#define UNDEFINED_TABLE_ID	-2 
#define UNDEFINED_TABLE_NAME _T("undefined_objects")
#define UNDEFINED_TABLE_CAPTION _T("[Остальные объекты]")





	//Базовый класс реактора публикации, реализующий поведение по умолчанию.
	//Унаследуйтесь от это класса и переопределите только необходимые методы.
	class CEmptyPublishingReactor: public ICadLibPublishingReactor
	{
	protected:
		CEmptyPublishingReactor() {};
		CEmptyPublishingReactor(const CEmptyPublishingReactor&) {};
		CEmptyPublishingReactor& operator= (const CEmptyPublishingReactor&) {return *this;}
		virtual ~CEmptyPublishingReactor() {};
	public:
		virtual void BeforePublishingStarted(IPublisher *pPublisher, bool &bCancel) override {};
		virtual void AfterPublicationFinished(IPublisher *pPublisher,
			bool bCanceled, bool bException) override {};

		virtual bool BeforePublishSpace(IPublisher *pPublisher, const AcDbObjectId& idBlockToPublish,
			AcDbObjectIdArray& arrSelection) override { return true;};
		virtual void AfterAcquireSettings(IPublisher *pPublisher) override {};
		virtual bool CustomConnectToDestDB(IPublisher *pPublisher) override {return false;}
		virtual void AfterDbConnected(IPublisher *pPublisher) override {};

		virtual bool IsEntityForPublish(IPublisher *pPublisher,
			const AcDbBlockReference *pParentBlockRef,
			AcDbEntity* pEnt) override {return true;}

		virtual bool GetSmartObject(IPublisher *pPublisher, AcDbObject *pEnt,
			const AcGeMatrix3d &mt, MStudioData::IElement *pResParams) override {return false;}

		virtual bool BeforeAddOrApplyObject(IPublisher *pPublisher, AcDbObject* pEnt,
			MStudioData::IElement *pObjectParameters) override {return true;}
		
		virtual void AfterAddOrApplyObject(IPublisher *pPublisher,
			MStudioDB::ILibObjectInfo *pLibObject, bool bNewObject,
			AcDbObject* pEnt, MStudioData::IElement *pObjectParameters) override {};

		virtual void AfterDumpEntity(IPublisher *pPublisher, MStudioDB::ILibObjectInfo *pLibObject,
			AcDbEntity** arrDumpedSet, int nDumpedSetCount,
			const AcDbBlockReference *pTopBlockRef,	const AcDbBlockReference *pParentBlockRef,
			AcGeMatrix3d& mtSetTransformation, void*) override {};

		void OnGetGloablTransformation(IPublisher *pPublisher, AcGeMatrix3d &mtTransform) override {};
		virtual void AfterPublishingEntities(MStudioPublish::IPublisher *pPublisher)override{}
	};

#ifndef NCAD
#define MODEL_STUDIO_PUBLISH_MODULE_NAME L"nvExporter.dbx"
#else
#define MODEL_STUDIO_PUBLISH_MODULE_NAME L"nvExporter.nrx"
#endif 
#define MODEL_STUDIO_PUBLISH_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PUBLISH_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PUBLISH_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_PUBLISH_API_CUR_VER_MAJOR, MSTUDIO_PUBLISH_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_PUBLISH_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_PUBLISH_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_PUBLISH_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_PUBLISH_API_CUR_VER_MAJOR, MSTUDIO_PUBLISH_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}