#pragma once

#include "..\msData\CSDataInterfaces.h"

//Интерфейсы для работы с параметрическим оборудованием
namespace MStudioParametric
{
	//Коллекция узлов параметрического оборудования (linCSNode)
	//Коллекция владеет узлами, пока не вызвать метод DetachNodes
	__interface IParametricNodes: public IUnknown
	{
		//Получение количества узлов
		idx_t GetCount();
		//Получение узла (linCSNode) по индексу
		AcDbEntity* GetNode(idx_t nNode);

		//Отсоединение узлов - коллекция не удалит их в деструкторе
		void DetachNodes();
		//Является ли коллекция владельцем узлов (false после вызова DetachNodes)
		bool IsNodesOwner();

		//Присоединение узлов к резидентной параметрической сущности (linCSParametricSolidBase)
		//Узлы добавляются в ту же AcDbBlockTableRecord в которой находится pParametric
		//pTrans - транзакция в рамках которой происходит добавление
		//bTransformNodes - следует ли трансформировать узлы в систему координат pParametric
		Acad::ErrorStatus AttachNodesToParametric(AcDbEntity* pParametric, AcTransaction* pTrans,
			bool bTransformNodes=true);
	};

	//Интерфейс класса-обёртки над параметрической сущностью
	//Обёртка позволяет управлять открытой предоставленной сущностью pParametricEnt
	//pParametricEnt должна быть унаследованна от linCSParametricSolidBase
	//Если сущность открыта для чтения, то необходимо избежать вызовов методов без модификатора const
	__interface IParametricEntWrapper: public IUnknown
	{
		//----Система координат объекта------------------------------------------------------------
		//Получение системы координат с масштабом
		void GetCoordSystem(AcGeMatrix3d& mtCoordSystem) const;
		//Получение системы координат с масштабом
		void GetCoordSystem(AcGePoint3d &ptPosition, AcGeVector3d &vX, AcGeVector3d &vY, AcGeVector3d &vZ) const;

		//Получение положения
		AcGePoint3d GetPosition() const;
		//Получение направления оси X
		AcGeVector3d GetDirX() const;
		//Получение направления оси Y
		AcGeVector3d GetDirY() const;
		//Получение направления оси Z
		AcGeVector3d GetDirZ() const;
		//Получение масштаба
		double GetScale() const;

		//Установка положения
		Acad::ErrorStatus SetPosition(const AcGePoint3d& ptPosition);
		//Установка направления оси X
		Acad::ErrorStatus SetDirX(const AcGeVector3d& vtDirX);
		//Установка направления оси Y
		Acad::ErrorStatus SetDirY(const AcGeVector3d& vtDirY);
		//Установка направления оси Z
		Acad::ErrorStatus SetDirZ(const AcGeVector3d& vtDirZ);
		//Установка масштаба
		Acad::ErrorStatus SetScale(double fScale=1.0);

		//----Параметрическая графика и атрибуты---------------------------------------------------
		//Получение ссылки на дерево с параметрической графикой для 2D или 3D режимов
		Acad::ErrorStatus GetGraphicsRoot(MStudioData::IElement **pParametric, bool b3DMode);
		//Получение ссылки на дерево с параметрами объекта
		Acad::ErrorStatus GetParametersRoot(MStudioData::IElement **pParameters);
		//Перерасчёт формул и обновление графики объекта, чтобы изменения деревьев вступили в силу
		Acad::ErrorStatus UpdateData();

		//Получение текущего режима отображения объекта (2D или 3D)
		bool Is3DMode();
		//Установка текущего режима отображения объекта (2D или 3D)
		void Set3dMode(bool bMode3d);

		//----XML Сериализация---------------------------------------------------------------------
		//Экспорт параметрической сущности в XML файл (формат XPG)
		bool ExportToXmlFile(LPCTSTR pszFileName);
		//Экспорт параметрической сущности в XML строку (формат XPG)
		bool ExportToXmlString(BSTR* pStrResXML);
		//Импорт параметрической сущности из XML файла (формат XPG, XPGX)
		//pResNodes - считанные узлы, которые необходимо добавить в модель вручную
		bool ImportFromXmlFile(LPCTSTR pszFileName, IParametricNodes** pResNodes=NULL);
		//Импорт параметрической сущности из XML строки (формат XPG)
		//pResNodes - считанные узлы, которые необходимо добавить в модель вручную
		bool ImportFromXmlString(LPCTSTR pszSourXML, IParametricNodes** pResNodes=NULL);

		//----Доступ к сущности, обёрнутой в данный объект-----------------------------------------
		//Получение обёртываемой параметрической сущности linCSParametricSolidBase
		AcDbEntity* GetWrappedEnity();
		//Установка обёртываемой параметрической сущности linCSParametricSolidBase
		//позволяет использовать класс, реализующий данный интерфейс для множества сущностей поочерёдно
		Acad::ErrorStatus SetWrappedEnity(AcDbEntity* pEnt);

		//----Импорт примитивов в XPG--------------------------------------------------------------
		//Импорт полилинии в профиль выдавливания или вращения
		//pSourPoly - исходная полилиния (поддерживаются дуги)
		//pDestParent - узел параметрической графики в который необходимо импортировать профиль (выдавливание или вращение)
		//mtTransform - матрица трансформации точек профиля
		Acad::ErrorStatus ImportProfile(const AcDbPolyline* pSourPoly, MStudioData::IElement* pDestParent,
			const AcGeMatrix3d& mtTransform,bool bCloseIfPolyClosed);

		//Запускает процесс интерактивной вставки параметрической сущности в документ
		//bAskAngle - выводить ли запрос угла
		//pBasePoint - позволяет задать точку вставки. В этом случае произойдет запрос только угла или
		// второй точки (см. PE_PARAM_INSERTION_SECOND_POINT)
		//Возвращает true, если сущность успешно добавлена в БД автокада
		bool PlaceWithJig(bool bAskAngle = true, const AcGePoint3d* pBasePoint = NULL);
	};
	
#define MSTUDIO_PARAMETRIC_API_CUR_VER_MAJOR 1
#define MSTUDIO_PARAMETRIC_API_CUR_VER_MINOR 9

	__interface IFactoryInterface
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_CORE_API_CUR_VER_MAJOR и MSTUDIO_CORE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Создание интерфейса-обёртки над параметрической сущностью
		// см. описание IParametricEntWrapper
		//В случае не верного типа сущности возрашает Acad::eWrongObjectType
		Acad::ErrorStatus CreateParametricWrapper(IParametricEntWrapper** pWrapper, AcDbEntity* pParametricEnt);

		//Создаёт экземпляр обычного Параметрического оборудования linCSParametricSolid
		//Его можно создать и с использованием RTTI автокада
		//Далее можно считать сущность из XPG (файл или память) с помощью обёртки IParametricEntWrapper
		AcDbEntity* CreatePlainParametricEntity();

		//Возвращает базовые класс для всех параметрический сущностей (не может быть инстанциирован)
		AcRxClass* GetParametricEntBaseClass();
		//Возвращает класс параметрического оборудования
		AcRxClass* GetParametricEntClass();
		//Возвращает класс узла
		AcRxClass* GetNodeClass();
		//Является ли сущность параметрическим оборудованием
		bool IsParametricEntity(const AcDbEntity *pEnt);

		//---Работа с набором сущностей------------------------------------------------------------
		//Объединяет набор параметрических сущностей в одну
		//Вся графика исходных сущностей записывается в группы корневого элемента результирующей
		//Все параметры исходных сущностей записываются как подчинённые объекты дерева параметров результирующей
		//запись ведётся в том же порядке, в котором расположены исходные сущности в arrSource
		AcDbEntity* CreateMergedParametricEntitiy(const AcDbVoidPtrArray& arrSource);

		// Возвращает установвленный 3Д режим для переданной базы
		// если pDb = Null то проверяем для текущей базы данных
		bool Is3dMode(AcDbDatabase* pDb = NULL);

		//Устанавливает 3Д режим для переданной базы
		// если pDb = Null то устанавливаем для текущей базы данных
		void Set3dMode(bool b3dMode, AcDbDatabase* pDb=NULL);
	};

#ifndef NCAD
#define MODEL_STUDIO_PARAMETRIC_MODULE_NAME L"UnitsCS.dbx"
#else
#define MODEL_STUDIO_PARAMETRIC_MODULE_NAME L"UnitsCS.nrx"
#endif 
#define MODEL_STUDIO_PARAMETRIC_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PARAMETRIC_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PARAMETRIC_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
			pRes = pGetFn(MSTUDIO_PARAMETRIC_API_CUR_VER_MAJOR, MSTUDIO_PARAMETRIC_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_PARAMETRIC_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_PARAMETRIC_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
						MODEL_STUDIO_PARAMETRIC_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_PARAMETRIC_API_CUR_VER_MAJOR, MSTUDIO_PARAMETRIC_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}