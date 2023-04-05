#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\CSGraphics\ms3DTypes.h"
#include "..\msData\IntermediateGeometry2.h"

namespace MStudioDB
{
	//Интерфейс объекта с базовой информацией об объекте БД
	__interface ILibObjectInfo: public IUnknown
	{
		//Статус объекта БД
		enum DbSysStatus
		{
			dbStatusCommon = 1,	//1,'COMMON','Общий' (виден всем)
			dbStatudShared = 2,	//2,'SHARED','Открытый' - (пользователь открывает доступ к своему объекту, но может его удалить)
			dbStatusUser = 3	//3,'PRIVATE','Пользовательский' (виден только пользователю-владельцу)
		};		

		LPCTSTR GetName() const;

		int GetObjectId() const;
		int GetElementId() const;
		int GetParentObjectId() const;
		int GetObjectCategoryId() const;
		int GetTag() const;

		int GetUserId() const;
		DbSysStatus GetStatus() const;
		GUID GetUID() const;

		//Получение даты последней модификации объекта в формате
		//OLE Automation Date
		double GetModifiedDate() const;
	};	

	//Forward declarations
	__interface ILibObjectInfoArr;
	__interface ILibObjectParamsMap;
	__interface IObjectRelationType;
	__interface IObjectRelationTypesArr;
	__interface ILinkedObjectsRecArr;
	__interface ILinkedObjectsInfoRecArr;
	__interface IElementData;
	__interface IElementDataArr;
	__interface IObjectsLinkInfoRecArr;
	__interface IDBDownloadedLand;
	

	//Интерфейс класса БД CadLib
	__interface IDataBase: public IUnknown
	{
		enum DbPlatform
		{
			dbMSSQL = 0, 
			dbMSSQLNCLI = 1, 
			dbPostgreSQL = 2 
		};
		//Платформа БД
		HRESULT GetDriver(BSTR* pResDB);

		DbPlatform GetPlatform();		
		void SetPlatform(DbPlatform dbp,LPCTSTR pszDriver);

		int GetPort();
		void SetPort(int n);

		//Имеется ли подключение к БД
		bool IsConnected();

		//Пытается подключится к БД с указанными параметрами
		//Если pszUser - пустая строка - используется аутентификация Windows
		//Если bSilent==true ошибка выводится в лог, а не в диалог
		bool Connect(LPCTSTR pszServerName, LPCTSTR pszDatabase, LPCTSTR pszUser,
			LPCTSTR pszPassword, bool bSilent=false);

		//Показывает диалог подключения к БД с введёнными данными и подключается к БД в случае нажатия ОК
		//Возвращает true в случае успешного подключения,
		//false в случае отмены подключения или ошибки подключения
		//pszServerName, pszDatabase, pszUser, pszPassword - данные для ввода в диалог по умолчанию
		//Eсли pszUser не задан или пустой, то будет использована аутентификация Windows
		//bStd - использовать стандартные настройки БД, а не strServer...
		//pszTitle - заголовок окна подключения
		//pCanceled  - true диалог завершился по Cancel
		bool UIConnect(LPCTSTR pszServerName=NULL, LPCTSTR pszDatabase=NULL, LPCTSTR pszUser=NULL,
			LPCTSTR pszPassword=NULL, bool bStd=true, LPCTSTR pszTitle=NULL, bool* pCanceled=NULL);

		//Получение коллекции определений параметров, связанной с БД
		HRESULT GetParamDefs(MStudioData::IParamDefs** pDBParamDefs);

		//Получение имени подключенного сервера
		HRESULT GetServer(BSTR* pResServer);

		//Получение имени подключенной БД
		HRESULT GetDatabaseName(BSTR* pResDB);

		//Получение имени пользователя, подключенного к БД.
		//В случае аутентификации Windows возвращается пустая строка
		HRESULT GetUserName(BSTR* pResStr);

		//Получение пароля пользователя, указанного при подключении
		HRESULT GetUserPassword(BSTR* pResStr);

		//Добавляет всю иерархию объектов в БД, также внутри рассчитывается вычисляемое имя (если задано в категории)
		//pRootElement - объект для добавления
		//nCatDef - категория объекта в случае, если не указан pCategories
		//Если указан массив категорий pCategories, то берётся категория оттуда соответствующая GetId элемента
		//bUseProtection - использовать ли защиту параметров
		//Если указать bApplyNewIdsToModelUid, то в ModelUID каждого элемента будет записан idObject его нового объекта БД
		//nSysStatus - системный статус объекта (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		long AddObject(MStudioData::IElement* pRootElement, int nCatDef, bool bUseProtection=true,
			int pCategories[]=NULL, int nCategoriesLength=0,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser,
			bool bApplyNewIdsToModelUid=false);

		//Добавляет всю иерархию объектов в БД, также внутри рассчитывается вычисляемое имя (если задано в категории)
		//pRootElement - объект для добавления
		//nCatDef - категория объекта в случае, если не указан pCategories
		//Если указан массив категорий pCategories, то берётся категория оттуда соответствующая GetId элемента
		//paramsMap - не используется
		//bUseProtection - не используется
		//Если указать bApplyNewIdsToModelUid, то в ModelUID каждого элемента будет записан idObject его нового объекта БД
		//nSysStatus - системный статус объекта (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		long AddObject(MStudioData::IElement* pRootElement, int nCatDef,
			ILibObjectParamsMap** pParamsMap=NULL, bool bAutoCommitParams=true,
			bool bUseProtection=true, int pCategories[]=NULL, int nCategoriesLength=0,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser,
			bool bApplyNewIdsToModelUid=false);

		//Добавляет подчинённый объект к родительскому
		//pElement - объект для добавления
		//nCurrentCat - категория объекта в случае, если не указан pCategories
		//Если указан массив категорий pCategories, то берётся категория оттуда соответствующая GetId элемента
		//paramsMap - [in, out] кэш параметров объектов, который необходимо сохранить в БД отдельно (Commit)
		//bUseProtection - использовать ли защиту параметров
		//Если указать bApplyNewIdsToModelUid, то в ModelUID каждого элемента будет записан idObject его нового объекта БД
		//bInsertWholeHierarchy - если да, то будут вставлены все подчинённые элементы
		//nSysStatus - системный статус объекта (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		long InsertSubObject(MStudioData::IElement* pElement, long lParentObject, int nCurrentCat,			
			ILibObjectParamsMap** pParamsMap,
			int pCategories[]=NULL, int nCategoriesLength=0,
			bool bUseProtection=true, bool bApplyNewIdsToModelUid=false,
			bool bInsertWholeHierarchy=true,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser);

		//Используя параметр PARAM_DBUID находит в БД объекты иерархии и актуализирует их параметры
		//если не задан PARAM_DBUID (или такой объект не найден), то добавляется новый объект
		//pElement - иерархия объектов для актуализации
		//nCategory - категория всех объектов (не актуализируется, используется при создании новых)
		//paramsMap - [in, out] кэш параметров объектов, который необходимо сохранить в БД отдельно (Commit)
		//bRemoveMissingSubs - удалять ли объекты иерархий БД, которых нет в заданной иерархии
		//bProcessWholeHierarchy - если нет, то будет обработан только корневой объект
		//Если указать bApplyNewIdsToModelUid, то в ModelUID каждого элемента будет записан idObject его нового объекта БД
		//nSysStatus - системный статус объекта (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		int ActualizeObject(MStudioData::IElement* pElement, int nCategory, ILibObjectParamsMap** pParamsMap,
			bool bRemoveMissingSubs=true,
			bool bProcessWholeHierarchy=true, bool bApplyNewIdsToModelUid=false,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser);

		//Применяет новые параметры объекту dbObject
		//Если не задан массив категорий pCategories, то всем объектам применяется категория nCatDef или категория объекта
		//параметры те же, что при создании объекта
		//Имя объекта пересчитывается (если расчётное) и применяется к newParameters
		//Возвращается true в случае успешного применения параметров
		bool SetObjectParameters(ILibObjectInfo* pDbObject, MStudioData::IElement* pNewParameters,
			int nCatDef=0, bool bUseProtection=false, int pCategories[]=NULL, int nCategoriesLength=0);

		//Получение информации об объекте по GUID
		//Возвращает NULL если объект не найден
		HRESULT GetLibraryObject(const GUID &objectUID, ILibObjectInfo** ppResObj);

		//Получение информации об объекте по GUID
		//Возвращает ppResObj==NULL если объект не найден
		HRESULT GetLibraryObject(BSTR pszUID, ILibObjectInfo** ppResObj);

		//Получение информации об объекте по idObject
		//Возвращает ppResObj==NULL если объект не найден
		HRESULT GetLibraryObject(long lPK, ILibObjectInfo** ppResObj);

		//Загружает параметры объекта
		//nIdObject - идентификатор объекта для получения параметров
		HRESULT GetObjectParameters(int nIdObject, MStudioData::IParamsOwner** ppResParams);	

		//Загружает параметры объект, а также подчинённые объекты с параметрами как IElement
		//pInfo - корневой объект запрашиваемого элемента
		//ppResElement - результирующий элемент
		HRESULT DownloadObjectAsElement(ILibObjectInfo* pInfo, MStudioData::IElement** ppResElement);	

		//Также смотрите ниже
		//DownloadElementsByObjectsIds
		//DownloadElementsByFilter

		//----------------Связи-----------------------------------------------------------------------------------------		
		//Получение типа связи по идентификатору
		//nRelTypeId - идентификатор типа связи
		//ppResRelType - тип связи или NULL, если связь не найдена
		HRESULT GetObjectRelationTypeById(int nRelTypeId, IObjectRelationType** ppResRelType);

		//Получение типа связи по имени
		//strRelTypeName - имя типа связи
		//ppResRelType - тип связи или NULL, если связь не найдена
		HRESULT GetObjectRelationTypeByName(BSTR pszRelTypeName, IObjectRelationType** ppResRelType);

		//Получение списка типов связей (пока не реализовано)
		HRESULT GetObjectRelationTypes(IObjectRelationTypesArr** ppResArrRelations);

		//Добавление типа связи (с проверкой на наличие существующей)
		//pRelTypeTemplate - полностью инициализированный (кроме Id) объект - шаблон 
		// (можно создать методом CreateObjectRelationType)
		//pszIcon - имя иконки в БД, для ее идентификации
		//uIconResId16 - идентификатор картинки типа связи 16x16 из ресурсов
		//uIconResId32 - идентификатор картинки типа связи 32x32 из ресурсов
		//hresInst - дескриптор модуля с ресурсными картинками
		//Возвращает Id новой или существующей связи, и также записывает Id в переданный шаблон
		int AddObjectRelationType(IObjectRelationType *pRelTypeTemplate, BSTR pszIcon=NULL,
			UINT uIconResId16=0, UINT uIconResId32=0, HINSTANCE hresInst=NULL);

		//Обновление/удаление типа связи
		//relType - Полностью инициализированный объект типа связи, если установить пустое системное
		// имя типа связи, то данный тип будет удалён вместе со всеми связями
		//pszIcon - имя иконки в БД, для ее идентификации
		//uIconResId16 - идентификатор картинки типа связи 16x16 из ресурсов
		//uIconResId32 - идентификатор картинки типа связи 32x32 из ресурсов
		//hresInst - дескриптор модуля с ресурсными картинками
		//Возвращает Id связи или 0 в случае ошибки или удаления связи
		int UpdateObjectRelationType(IObjectRelationType *pRelType, BSTR pszIcon=NULL,
			UINT uIconResId16=0, UINT uIconResId32=0, HINSTANCE hresInst=NULL);

		//Добавление связи в БД (если связь уже есть, то ошибка не происходит)
		//nObject1Id - Id первого связываемого объекта
		//nObject2Id - Id второго связываемого объекта
		//nRelationTypeId - идентификатор типа связи
		//Возвращает false в случае ошибки
		bool LinkObjects(int nObject1Id, int nObject2Id, int nRelationTypeId);

		//Добавление связи в БД (если связь уже есть, то ошибка не происходит)
		//nObject1Id - Id первого связываемого объекта
		//object2UId - UID второго связываемого объекта
		//nRelationTypeId - идентификатор типа связи
		//Возвращает false в случае ошибки
		bool LinkObjects(int nObject1Id, const GUID& object2UId, int nRelationTypeId);

		//Получение связанных объектов
		//arrObjectsIds - вектор объектов, связи с которыми необходимо получить
		//nArrObjectsIdsCount - количество объектов в arrObjectsIds
		//nRelationTypeId - идентификатор рассматриваемого типа связи объектов
		//ppArrResult - результирующие связи для каждого объекта из arrObjectsIds
		//	KeyObject - всегда является корневой объект из arrObjectsIds, даже если связь с его потомком
		//bSelByLeftObject - arrObjectsIds указывает на объекты из левого столбца (1) и возвращаются
		//	связанные объекты из правого столбца, иначе исходными являются объекты правого столбца (2)
		//bIncludeFullHierarchy - будут получены связи также для всех подчинённых объектов (детей arrObjectsIds)
		HRESULT GetLinkedObjects(int* arrObjectsIds, int nArrObjectsIdsCount,
			int nRelationTypeId,
			ILinkedObjectsRecArr **ppArrResult,
			bool bSelByLeftObject=true, bool bIncludeFullHierarchy=false);

		//Получение связанных объектов (версия с получением CLibObjectInfo)
		//arrObjectsIds - вектор объектов, связи с которыми необходимо получить
		//nArrObjectsIdsCount - количество объектов в arrObjectsIds
		//nRelationTypeId - идентификатор рассматриваемого типа связи объектов
		//ppArrResult - результирующие связи для каждого объекта из arrObjectsIds
		//	KeyObject - всегда является корневой объект из arrObjectsIds, даже если связь с его потомком
		//bSelByLeftObject - arrObjectsIds указывает на объекты из левого столбца (1) и возвращаются
		//	связанные объекты из правого столбца, иначе исходными являются объекты правого столбца (2)
		//bIncludeFullHierarchy - будут получены связи также для всех подчинённых объектов (детей arrObjectsIds)
		HRESULT GetLinkedObjects(int* arrObjectsIds, int nArrObjectsIdsCount,
			int nRelationTypeId,
			ILinkedObjectsInfoRecArr **ppArrResult,
			bool bSelByLeftObject=true, bool bIncludeFullHierarchy=false);

		//Удаление связи(связей) объекта из БД
		//nObjectId - Id объекта у которого удаляем связь (может быть как слева, так и справа)
		//pRelTypeTemplate - объект описывающий связь
		//nObject2 - Id объекта с которым удаляем связь (или 0, для удаления всех связей указанного типа с первым объектом)
		//Возвращает false в случае ошибки
		bool RemoveObjectLinks(int nObjectId, const IObjectRelationType *pRelTypeTemplate, int nObject2=0);

		//GetObjectsLinksInfo (Ниже)

		//--------------------------------------------------------------------------------------------------------------

		//Скачивает массив объектов с подобъектами и параметрами (CElements)
		//arrObjectsIds[nObjectsCount] - массив ID необходимых корневых объектов (уникальные значения)
		//Все иерархии скаченных объектов добавляются в корневой элемент pResParentElement
		//pResultObjects - результирующий массив всех скаченных объектов (включая подчинённые) CLibObject+ссылка на CElement
		// информация валидна для неизменного pResParentElement, т.к. ссылается на него
		void DownloadElementsByObjectsIds(int* arrObjectsIds, int nObjectsCount,
			MStudioData::IElement **pResParentElement,
			IElementDataArr **pResultObjects);

		//Скачивает массив объектов с подобъектами и параметрами (CElements) по фильтру
		//pszFilter - фильтр для выборки корневых объектов (должен быть результатом выполнения других методов)
		//Все иерархии скаченных объектов добавляются в корневой элемент pResParentElement
		//pResultObjects - результирующий массив всех скаченных объектов (включая подчинённые) CLibObject+ссылка на CElement
		// информация валидна для неизменного pResParentElement, т.к. ссылается на него
		void DownloadElementsByFilter(LPCTSTR pszFilter,
			MStudioData::IElement **pResParentElement,
			IElementDataArr **pResultObjects);

		//Отключение от БД (если было подключение)
		HRESULT Disconnect();

		//--------------------------------------------------------------------------------------------------------------

		//Получает идентификатор категории по системному имени, либо заголовку
		//pszName - системное имя или заголовок категории
		//bSysName - что конкретно указано в pszName
		//Возвращает 0 в случае ошибки или если категория не найдена, иначе идентификатор категории
		int GetObjectCategoryId(LPCTSTR pszName, bool bSysName);

		//Получение списка категорий объектов
		//pResCatList - указатель для записи IElement, (в ModelUID хранится id категории)
		HRESULT GetObjectCategories(MStudioData::IElement **pResCatList);

		//Получение идентификатора системной категории для нематериальных объектов "Структурные данные"
		//Имя категории SYS_CAT_STRUCTURE_DATA ("structure_data")
		//Данная категория создаётся по умолчанию во всех БД
		//nEnum - зарезервировано для будущих нужд
		int GetStandardCategoryId(int nEnum=0);

		//Добавление категории объекта (с проверкой на наличие существующей)
		//Возвращает идентификатор вновь созданной категории объектов
		//pszSysName - системное имя категории
		//pszLabel - человеческое имя категории (заголовок)
		//pszIconName - имя иконки, которая будет создана в случае указания hBmpSmall и hBmpLarge
		//hBmpSmall - иконка категории 16х16
		//hBmpLarge - иконка категории 32х32
		//В случае если категория существует - будет возвращён её идентификатор
		int AddObjectCategory(LPCTSTR pszSysName, LPCTSTR pszLabel,	LPCTSTR pszIconName=NULL,
			HBITMAP hBmpSmall=NULL, HBITMAP hBmpLarge=NULL);

		//--------------------------------------------------------------------------------------------------------------
		//Возвращает версию БД умноженную на 1000
		int GetVersion();

		//Получение минимальной и максимальной поддерживаемой версии БД
		//Проверка версии происходит при подключении
		//Номер версии - версия БД*1000
		HRESULT GetDatabaseSupportedVersion(int& nCurrentVersion, int& nLastVersion);

		//Возвращает версию 3D умноженную на 1000, либо 0 если нет версии (БД не 3D)
		int GetVersion3D();

		//Возвращает ревизию 3D, либо 0 если нет версии (БД не 3D)
		int GetVersionRevision3D();
		//--------------------------------------------------------------------------------------------------------------
		//Загрузка сетки в БД (если такая сетка уже есть - вернётся id существующей)
		//ptBase - базовая точка сетки (её положение указывается в БД, она же 0 в XPG)
		//pMeshData, nMeshSize - массив байт длинной nShapeSize, содержащий сетку в формате msm
		//pszXpg - строка с XPG графикой (может быть NULL)
		//Возвращает idMesh сетки из таблицы Mesh или исключение
		int AddMesh(
			void* pMesh,
			ULONG nMeshSize,
			ULONG nMeshHash,
			LPCTSTR pXPG,			
			const CSVECTORD3 &ptBase,
			const CSVECTORD3 &ptSize);

		//Возвращает true если имеется сетка пониженной детализации idMesh с уровнем детализации nLevel
		bool HasLowDtailedMeshData(int idMesh, int nLevel);

		//Добавляет/обновляет сетку низкой детализации к основной сетки с idMesh
		//Возвращает true в случае успешного добавления
		//nLevel - LOW_DEATAILED_MESH_SIMPLIFIED и прочие виды детализации
		bool AddLowDetailedMeshData(int idMesh, int nLevel, void* pMeshData, ULONG nMeshSize);

		//Добавляет ссылку на сетку в БД МиА, Project
		//nIdObject - id объект с которым ассоциирована графика
		//nIdMesh - id сетки графики
		//ptPosition - положение в пространстве базовой точки
		//ptExtMin, ptExtMax - экстенты трансформированного тела (конечные реальные экстенты)
		//vtXAxis, vtYAxis, vtZAxis - направление и ориентация из базовой точки	
		//pARGBColor - если задан, то графика будет перекрашена в указанный цвет
		//Возвращает idGraphics > 0 в случае успешного добавления в БД
		int AddShape(int nIdObject, int nIdMesh,
			const CSPOINTD &ptPosition,
			const CSPOINTD &ptExtMin, const CSPOINTD &ptExtMax,
			const CSVECTORD3& vtXAxis, const CSVECTORD3& vtYAxis, const CSVECTORD3& vtZAxis,
			int *pARGBColor=NULL);
		//--------------------------------------------------------------------------------------------------------------

		//Получение информации о связях объектов
		//Извлекается информации о том, связи каких типов присутствуют
		// и об их количестве (см. LinkInfoRec)
		//arrObjectsIds - вектор ключевых объектов для извлечения информации
		//nArrObjectsIdsCount - количество объектов в arrObjectsIds
		//ppArrResult - массив с результатом LinkInfoRec[]
		//	KeyObject - всегда является ключевым объектом из arrObjectsIds
		//  Массив отсортирован по KeyObject
		//bAnalyzeFullHierarchy - активирует учёт связей всех подчинённых объектов arrObjectsIds
		HRESULT GetObjectsLinksInfo(int* arrObjectsIds, int nArrObjectsIdsCount,
			IObjectsLinkInfoRecArr **ppArrResult, bool bAnalyzeFullHierarchy=false);

		//Получение информации об объектах по списку идентификаторов arrObjectsIds[nObjectsCount]
		//ppResObjArr - результирующий массив информации об объектах, имеющих указанные идентификаторы
		HRESULT GetLibraryObjects(int* arrObjectsIds, int nObjectsCount, ILibObjectInfoArr** ppResObjArr);

		//Получение информации об объектах по списку уникальных идентификаторов arrObjectsUids[nObjectsCount]
		//ppResObjArr - результирующий массив информации об объектах, имеющих указанные идентификаторы
		HRESULT GetLibraryObjects(GUID* arrObjectsUids, int nObjectsCount, ILibObjectInfoArr** ppResObjArr);

		//Получение информации об объектах по выборке
		//pszFilter - фильтр для выборки корневых объектов (должен быть результатом выполнения других методов)
		//ppResObjArr - результирующий массив информации об объектах из выборки
		HRESULT GetLibraryObjects(LPCTSTR pszFilter, ILibObjectInfoArr** ppResObjArr);

		//Удаляет объект из библиотеки
		//nObjectId - идентификатор объекта
		//Вместе с данным объектом будут удалены все подчинённые объекты,
		// а также все зависимо связанные объекты, ссылки на графику и файлы
		HRESULT DeleteObject(int nObjectId);

		//Удаляет объекты из библиотеки по списку идентификаторов arrObjectsIds[nObjectsCount]
		//Вместе с данными объектами будут удалены все подчинённые объекты,
		// а также все зависимо связанные объекты, ссылки на графику и файлы
		HRESULT DeleteObjects(int* arrObjectsIds, int nObjectsCount);

		//Удаляет объекты из библиотеки
		//arrObjectsInfo - массив с информацией об объектах для удаления
		//Вместе с данными объектами будут удалены все подчинённые объекты,
		// а также все зависимо связанные объекты, ссылки на графику и файлы
		HRESULT DeleteObjects(ILibObjectInfoArr* arrObjectsInfo);

		//--------------------------------------------------------------------------------------------------------------

		//Связывает указанную БД с переданными определениями параметров и обновляет их
		//pParamDefs - определения параметров для связи
		//bTransimtOwnership - если, да, то при удалении БД будет освобождена память,
		// занимаемая pParamDefs
		HRESULT BindWithParamDefs(MStudioData::IParamDefs *pParamDefs, bool bTransimtOwnership);

		//-------------------------------------------------------------
		//Связывает указанную БД с переданными определениями параметров и обновляет их
		//pParamDefs - определения параметров для связи
		//bTransimtOwnership - если, да, то при удалении БД будет освобождена память,
		// занимаемая pParamDefs
		//HRESULT GetLandSurface(MStudioData::IParamDefs *pParamDefs, bool bTransimtOwnership);
		//Используйте DBL_MAX и -DBL_MAX, если необходимо отменить ограничение по определённой оси
		HRESULT DownloadLandSurface(int nLandId,  IDBDownloadedLand** ppLandsResData,
			int nCountAABB = 0, CAABBI* pExtents = NULL);

		//Загружает существующие настройки МиА из бд
		void LoadProjectSettings();
	};

	//Массив информации об объектах
	__interface ILibObjectInfoArr: public IUnknown
	{
		//Получение количества элементов
		int GetCount();

		//Получение идентификатора объекта БД по индексу в массиве
		int GetObjectIdByIndex(int nIdx);

		//Получение индекса объекта БД по индексу в массиве
		GUID GetObjectUIDByIndex(int nIdx);

		//Получение имени объекта по индексу в массиве
		LPCTSTR GetObjectNameByIndex(int nIdx);

		//Получение имени идентефикатора категории объекта по индексу в массиве
		int GetObjectCetegoryIdByIndex(int nIdx);

		//Получение информации об объекте БД по индексу
		HRESULT GetItemAt(int nIdx, ILibObjectInfo** pResInfo);

		//Поиск элемента по идентификатору объекта nObjectId
		//В случае неудачи pResInfo остаётся неизменным
		HRESULT FindItemByObjectId(int nObjectId, ILibObjectInfo** pResInfo);
	};

	//Подготовленный контейнер параметров для сохранения в базу за раз
	//В основном используется классом БД, но вынесен наружу для возможности накопления изменений
	__interface ILibObjectParamsMap: public IUnknown
	{
		//Перенос значений параметров в контейнер
		void SetValues(long idObject, MStudioData::IParamsOwner* pParamsOwner, bool bUseProtection);
		//Сохранение значений параметров в БД
		void Commit();
		//Загрузка из БД сразу всех метаданных по параметрам
		void CacheAllParameters();
		//Удаление всех накопленных параметров
		void ResetValues();
	};

	//Интерфейс информации об объекте БД, связанным с частью скаченной структурой CElement
	//Валиден до момента уничтожения массива-владельца и CElement назначения (resParentElement) методов DownloadElementsBy
	__interface IElementData: public IUnknown
	{
		//Получение идентификатора объекта БД
		int GetObjectId();

		//Получение информации об объекте БД
		void GetObjectInfo(ILibObjectInfo** pResInfo);

		//Получение ссылки на часть корневой структуры CElement, связанной с этим объектом БД		
		void GetElement(MStudioData::IElement** ppResElementRef);
	};

	//Интерфейс результирующего массива методов DownloadElementsBy
	//Валиден до момента уничтожения CElement назначения (resParentElement) методов DownloadElementsBy
	__interface IElementDataArr: public IUnknown
	{
		//Получение количества элементов
		int GetCount();

		//Получение элемента по индексу
		HRESULT GetItemAt(int nIdx, IElementData** pResEl);

		//Поиск элемента по идентификатору объекта nObjectId
		//В случае неудачи pResEl остаётся неизменным
		HRESULT FindItemByObjectId(int nObjectId, IElementData** pResEl);

		//Поиск элемента по указателю на место в иерархии
		//В случае неудачи pResEl остаётся неизменным
		HRESULT FindItemByElement(MStudioData::IElement* pElement, IElementData** pResEl);
	};

	//Тип связи между объектами (таблица [ObjectsRelationTypes])
	__interface IObjectRelationType: public IUnknown
	{
		int GetId() const;

		int GetIdIcon() const;
		void SetIdIcon(int nVal);

		HRESULT GetName(BSTR* pStrRes);
		void SetName(LPCTSTR pStrName);

		HRESULT GetCaption(BSTR* pStrRes);
		void SetCaption(LPCTSTR pStrCaption);

		//Поведение второго объекта при удалении первого. 
		//	false - soft pointer (при удалении первого связанного объекта второй остаётся). 
		//	true - hard pointer (при удалении первого объекта второй удаляется)
		bool IsHardLink1() const;
		void SetHardLink1(bool bHard);

		//Поведение первого объекта при удалении второго. 
		//	false - soft pointer (при удалении второго связанного объекта первый остаётся).
		//	true - hard pointer (при удалении второго объекта первый удаляется)
		bool IsHardLink2() const;
		void SetHardLink2(bool bHard);
	};
	
#pragma pack(push, 1)
	//Запись массива связанных объектов
	struct LinkedObjectsRec
	{
		//Ключевой объект (по которым был запрос)
		int nKeyObjectId;
		//Связанный объект
		int nLinkedObjectId;
	};

	//Запись массива информации об активных связях
	struct LinkInfoRec
	{
		//Ключевой объект (по которым был запрос)
		int nKeyObjectId;
		//Тип связи
		int nObjectRelationType;
		//Количество связей, где ключевой объект слева
		int nLinksCountLeft;
		//Количество связей, где ключевой объект справа
		int nLinksCountRight;
	};
#pragma pack(pop)

	//Интерфейс массива с информацией о связанных объектах
	//Используется только в качестве владельца массива "C"
	__interface ILinkedObjectsRecArr: public IUnknown
	{
		//Возвращает количество записей в массиве
		int GetLength();

		//Возвращает вектор записей связанных объектов длиной GetLength()
		//Все записи отсортированы сначала по nKeyObjectId, затем по nLinkedObjectId
		LinkedObjectsRec* GetRecords();
	};

	//Интерфейс результата получения информации о связанных объектах
	//Результат сгруппирован по ключевому объекту (по которому был запрос)
	__interface ILinkedObjectsInfoRecArr: public IUnknown
	{
		//Возвращает количество ключевых объектов
		int GetKeyObjectsCount();

		//Возвращает идентификатор БД ключевого объекта по индексу
		//nKeyObjectIdx - индекс ключевого объекта [< GetKeyObjectsCount()]
		//Результат отсортирован по nKeyObjectId
		int GetKeyObjectIdAt(int nKeyObjectIdx);

		//Возвращает индекс ключевого объекта по его идентификатору в БД
		//nKeyObjectId - идентификатор БД ключевого объекта
		//Возвращает -1 в случае, если информация по запрашиваемому объекту не найдена
		int GetKeyObjectIndexById(int nKeyObjectId);

		//Возвращает количество связанных с ключевым объектов
		//по индексу ключевого объекта 
		//nKeyObjectIdx - индекс ключевого объекта [< GetKeyObjectsCount()]
		int GetLinkedObjectsCountAt(int nKeyObjectIdx);

		//Возвращает идентификатор БД объекта, связанного с ключевым
		//nKeyObjectIdx - индекс ключевого объекта [0 <= nKeyObjectIdx < GetKeyObjectsCount()]
		//nLinkedObjectIdx - индекс связанного объекта
		//  [0 <= nLinkedObjectIdx < GetLinkedObjectsCountAt(nKeyObjectIdx)]
		int GetLinkedObjectAt(int nKeyObjectIdx, int nLinkedObjectIdx);

		//Возвращает информацию об объекте БД, связанного с ключевым
		//nKeyObjectIdx - индекс ключевого объекта [0 <= nKeyObjectIdx < GetKeyObjectsCount()]
		//nLinkedObjectIdx - индекс связанного объекта
		//  [0 <= nLinkedObjectIdx < GetLinkedObjectsCountAt(nKeyObjectIdx)]
		//ppResObjectInfo - интерфейс копии объекта с информацией о связанном объекте
		HRESULT GetLinkedObjectAt(int nKeyObjectIdx, int nLinkedObjectIdx,
			ILibObjectInfo** ppResObjectInfo);
	};	
	
	//Интерфейс массива записей о типах связей
	//Записи отсортированы по идентификатору типа связи
	__interface IObjectRelationTypesArr: public IUnknown
	{
		//Возвращает количество записей в массиве
		int GetLength();

		//Возвращает идентификатор типа связи БД по индексу
		//nIdx - индекс записи
		int GetRelationTypeIdAt(int nIdx);

		//Возвращает имя типа связи БД по индексу
		//nIdx - индекс записи
		LPCTSTR GetRelationTypeNameAt(int nIdx);

		//Возвращает заголовок типа связи БД по индексу
		//nIdx - индекс записи
		LPCTSTR GetRelationTypeCaptionAt(int nIdx);

		//Возвращает имя тип связи БД по индексу
		//nIdx - индекс записи
		//ppResRelType - указатель по которому будет записан указатель на
		//  интерфейс копии объекта типа записи
		HRESULT GetRelationTypeAt(int nIdx, IObjectRelationType** ppResRelType);
	};
	
	//Интерфейс массива LinkInfoRec
	//Используется только в качестве владельца массива "C"
	__interface IObjectsLinkInfoRecArr: public IUnknown
	{
		//Возвращает количество записей в массиве
		int GetLength();

		//Возвращает вектор записей информации о связях объекта
		//см. GetObjectsLinksInfo
		//Все записи отсортированы сначала по nKeyObjectId
		LinkInfoRec* GetRecords();
	};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define MSTUDIO_DB_API_CUR_VER_MAJOR 1
#define MSTUDIO_DB_API_CUR_VER_MINOR 15

	__interface IFactoryInterface
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_DB_API_CUR_VER_MAJOR и MSTUDIO_DB_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Создание нового объекта для работы с БД
		HRESULT CreateDataBase(IDataBase** pNewDb);

		//Получение глобального объекта БД стандартных компонент ModelStudio
		//связанного с глобальными определениями параметров
		//(для автокада это библиотека на вкладке "библиотекой стандартных компонент")
		HRESULT GetStandardComponentsDataBase(MStudioDB::IDataBase** pStandardDb);

		//Создание нового экземпляра объекта типа связи
		HRESULT CreateObjectRelationType(IObjectRelationType** pNewRelTypeObject);

		//См. описание ниже
		bool SetupModelStudioOptions(HWND hWndParent);

		//Показ стандартного диалога настроек ModelStudio
		//hWndParent - дескриптор родительского окна (или NULL)
		//pStandardDb - БД, временно используемая как БД стандартных компонент для
		// работы с определениями параметров или NULL
		//Возвращает Да, если пользователь нажал OK
		bool SetupModelStudioParams(HWND hWndParent, IDataBase* pStandardDb);
	};

#define MODEL_STUDIO_DB_MODULE_NAME L"mstudioDB.dll"
#define MODEL_STUDIO_DB_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_DB_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_DB_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_DB_API_CUR_VER_MAJOR, MSTUDIO_DB_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_DB_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_DB_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_DB_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_DB_API_CUR_VER_MAJOR, MSTUDIO_DB_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};

	//Массивы информации о вершинах и треугольниках предствляющие слой "земли"
	__interface IDBDownloadedLand: public IUnknown
	{
		//Получение количества вершин
		int GetCountVertices();
		//Получение количества треугольников составляющих поверхность
		int GetCountTriangles();

		//Получение вершин
		 CSPOINTD* GetVertices();

		//Получение треугольников
		 CLibDBSurfTriangle* GetTriangles();

	};

}