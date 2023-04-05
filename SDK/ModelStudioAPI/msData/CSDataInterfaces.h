#pragma once

#include "commtpl.h"

namespace MStudioData
{
	//Интерфейс параметра (атрибута) в IParamsOwner
	__interface IParam: public IUnknown
	{
		//Получение имени параметра
		LPCTSTR GetName() const;
		//Получение русского имени параметра
		LPCTSTR GetComment() const;
		//Получение значения параметра в виде строки
		void GetValue(BSTR *pStrDest) const;
		//Получение комментария к значению параметра (часто формула)
		LPCTSTR GetValueComment() const;

		//Установка имени параметра
		//Список запрещённых символов: <=32 и '"@$&*()[]{}.,:;?/\<>|
		//Имя параметра принято писать заглавными латинскими буквами (PART_TYPE)
		void SetName(LPCTSTR pszVal);
		//Установка русского имени параметра
		void SetComment(LPCTSTR pszVal);
		//Установка значения параметра в виде строки
		void SetValue(LPCTSTR pszVal);
		//Установка комментария к значению параметра (часто формула)
		void SetValueComment(LPCTSTR pszVal);

		//Применение значения исходного параметра
		void AssignValue(const IParam* pSourceParam);
		//Применение комментария к значению исходного параметра
		void AssignValueComment(const IParam* pSourceParam);
		//Применение значения и комментария к значению исходного параметра
		void AssignValueAndComment(const IParam* pSourceParam);

		//Создание копии параметра
		void Clone(IParam** pClonedParam);

		//Сравнение двух параметров по имени без учёта регистра
		int Compare(const IParam* pOther);

		//Возвращает имя в верхнем регистре
		LPCTSTR GetUpperName() const; 
	};

#pragma pack(push, 1)
	//Структура трёхмерного вектора двойной точности
	//бинарно совместима с AcGeVector3d, CMSVector3d, CSVECTORD3 и прочими
	struct CCS3DoubleVector
	{
		double x, y, z;
	};
#pragma pack(pop)

	//Интерфейс для коллекции параметров IParam
	__interface IParamsOwner: public IUnknown
	{
		//Установка значений параметров
		//Если параметра небыло в коллекции - он создаётся
		void SetParameter(LPCTSTR pszName,LPCTSTR pszValue,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,double fValue,LPCTSTR pszComment,LPCTSTR pszValueComment,int nPrescision);
		void SetParameter(LPCTSTR pszName,double fValue,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,int nValue,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,const GUID& guid,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,const CCS3DoubleVector &vt,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));

		//Добавление нового параметра (или возврат существующего)
		void AddParameter(LPCTSTR pszName, LPCTSTR pszValue, LPCTSTR pszComment,
			LPCTSTR pszValueComment, IParam** pRes=NULL);

		//Добавление нового параметра (если bCheckName и параметр уже есть, то действий не совершается)
		void AddParamCopy(const IParam* pSrc, bool bCheckName);

		//Применение параметра (обработка *ERASED*, *VALUE_SET* и прочих флагов из даилога редактирования)
		void ApplyParameter(const IParam* pParam);
		//Применение всех параметров коллекции
		void ApplyParameters(const IParamsOwner* pParamsOwner);

		//---Доступ к значением параметра аналогичный GetValue, но с указанием значения по умолчанию---
		LPCTSTR GetParameterValue(LPCTSTR pszParamName,LPCTSTR pszDefault=_T(""))const;
		double GetParameterValue(LPCTSTR pszParamName,double fDefault)const;
		int GetParameterValue(LPCTSTR pszParamName,int nDefault)const;
		CCS3DoubleVector GetParameterValue(LPCTSTR pszParamName, const CCS3DoubleVector &vtDefault)const;

		//Чтение значения параметра в переменную
		//Возвращает false, если параметр не найден (значение параметра не меняется)
		bool GetValue(LPCTSTR pszParamName, BSTR *pStrDest) const;

		//Чтение значения параметра в переменную
		//Возвращает false, если параметр не найден (значение параметра не меняется)
		//В случае ошибки конвертации записывается значение 0
		bool GetValue(LPCTSTR pszParamName, int& nDest) const;

		//Чтение значения параметра в переменную
		//Возвращает false, если параметр не найден (значение параметра не меняется)
		bool GetValue(LPCTSTR pszParamName, bool& bDest) const;

		//Чтение значения параметра в переменную
		//Возвращает false, если параметр не найден (значение параметра не меняется)
		//В случае ошибки конвертации записывается значение 0.0
		bool GetValue(LPCTSTR pszParamName, double& fDest) const;

		//Чтение значения параметра в переменную
		//Возвращает false, если параметр не найден или ошибка конвертации (значение параметра не меняется)
		bool GetValue(LPCTSTR pszParamName, CCS3DoubleVector& vtDest) const;

		//Чтение значения параметра в переменную
		//Возвращает false, если параметр не найден или ошибка конвертации (значение параметра не меняется)
		bool GetValue(LPCTSTR pszParamName, GUID& uidDest) const;

		//Получение параметра по имени (если параметр не найден возвращает false)
		bool GetParameter(LPCTSTR pszName, IParam** pResParam)const;

		//Получение параметра по индексу (если параметр не найден возвращает false)
		bool GetParameter(idx_t nParam, IParam** pResParam) const;

		//Получение количества параметров (индексов)
		idx_t GetParamsCount() const;

		//Удаление параметра по имени
		void RemoveParameter(LPCTSTR pszParam);
		//Удаление параметра по индексу
		void RemoveParameter(idx_t nParam);	

		//Удаление всех параметров
		void DeleteAllParams();	

		//Создание копии коллекции
		void Clone(IParamsOwner** pClonedParams);

		//Присваивание другой коллекции этой (они будут равны)
		void CopyParamsFrom(const IParamsOwner* pSrcEl);

		//Слияние параметров (применение коллекции pSrcParams)
		//bMergeEmptyValues - добавлять ли параметры без значений из pSrcParams
		//bSrcValuePriority - запретить переписывать значения существующих параметров
		void MergeParamsFrom(const IParamsOwner* pSrcParams, bool bMergeEmptyValues, bool bSrcValuePriority);

		//Сравнение двух коллекций
		bool IsEqualParameters(const IParamsOwner *pOtherParams);

		//Форматирование строки с GUID такое же, как используется в методе SetParameter
		void FormatUID(const GUID& guid, BSTR *pStrDest);		
	};

	//Интерфейс дерева параметров (IParamsOwner в древовидной форме)
	__interface IElement: public IParamsOwner
	{
		//----текущий элемент--------------------------------------------------------------------------------
		//Получение имени элемента
		LPCTSTR GetName() const;	
		//Устанавливает имя элемента
		void SetName(LPCTSTR pszName);

		//Получение идентификатора элемента (уникальный для всего дерева)
		int GetId() const;

		//Получение уровеня данного элемента в дереве (начиная с 0)
		int GetLevel(void) const;

		//Получение пользовательского идентификатора (Tag)
		int GetModelUID() const;
		//Установка пользовательского идентификатора (Tag)
		void SetModelUID(int uid);	

		//----подчинённые элементы---------------------------------------------------------------------------
		//Получение количества подчинённых элементов
		idx_t GetChildCount() const;
		//Получение подчинённого элемента по индексу
		bool GetChild(idx_t nChild, IElement** pResChild) const;
		//Получение подчинённого элемента по имени (или NULL)
		bool GetChild(LPCTSTR pszName, IElement** pResChild) const;
		//Получение подчинённого элемента по имени без учёта регистра
		bool GetChildNoCase(LPCTSTR pszName, IElement** pResChild) const;
		//Получение индекса по подчинённому элементу
		idx_t GetChildIndex(IElement* pEl) const;
		//Поиск элемента дерева по идентификатору
		bool GetElementById(idx_t nID, IElement** pResElement) const;
		//Поиск подчинённого элемента по идентификатору
		bool GetChildById(int nID, IElement** pResChild);
		//Является ли элемент pChild подэлементом данного элемента
		bool HasChild(IElement* pChild);

		//Создание подчинённого элемента с указанием имени
		void AddChild(LPCTSTR pszName, IElement** pResChild);
		//Создание подчинённого элемента с указанием места вставки и имени
		void InsertChild(idx_t nIdx, LPCTSTR pszName, IElement** pResChild);
		//Добавляет копию pChildToCopy в виде подчинённого элемента
		void AddChildCopy(const IElement* pChildToCopy, IElement** pResChild);

		//Получение максимального идентификатора элементов в дереве
		int GetMaxElementId();

		//----родительские элементы--------------------------------------------------------------------------
		//Получение родительского элемента (или NULL)
		bool GetParent(IElement** pResParent)const;
		//Получение корневого элемента (или this)
		void GetRoot(IElement** pResRoot)const;

		//----удаление---------------------------------------------------------------------------------------
		//Удаление подчинённого элемента
		void DeleteChild(IElement* pChild);
		//Удаляет все подчинённые элементы
		void DeleteAllChildren();	
		//Удаление данного элемента из иерархии (и из памяти)
		void Delete();

		//----Вектор пользовательских данных-----------------------------------------------------------------
		//Получение тэга по индексу
		int GetTag(int n)const;
		//Установка тэга по индексу (с автоматическим увеличением вектора с обнулением)
		void SetTag(int nTag, int n);
		//Установка размер вектора пользовательских данных (с обнулением)
		void SetTagsCount(int nTags);
		//Получение размер вектора пользовательских данных
		int GetTagsCount()const;
		//Получение вектора  пользовательских данных (размера GetTagsCount)
		const int* GetTags()const;

		//----Работа с деревьями-----------------------------------------------------------------------------
		//Создание копии дерева параметров
		void Clone(IElement** pClonedElement);

		//Присваивание другого дерева этому (они будут равны)
		void CopyFrom(const IElement* pSourceElement);

		//Слияние с деревом pSrcElement (применение дерева pSrcElement с добавлением новых детей и слиянием параметров)
		//Слияние данного элемента происходит с pSrcElement, далее всех подчинённых элементов по равенству имени
		//bMergeEmptyValues - добавлять ли параметры без значений
		//bSrcValuePriority - запретить переписывать значения существующих параметров
		//bSetName - переименовать текущий элемент в имя pSrcElement
		void Merge(const IElement* pSrcElement, bool bMergeNullValues, bool bSrcValuePriority, bool bSetName);

		//Заменяет подчинённые элементы текущего элемента
		//на копии подчинённых элементов из pSourceElement
		void CopyChildrenFrom(const IElement* pSourceElement);

		//----Расчёт значений параметров---------------------------------------------------------------------
		//Расчёт всех параметров этого элемента и нижестоящего дерева
		//Формулы для расчёта записываются в комментарий к знаниям параметров, начиная с символа '='
		void CalculateParameters();

		//Методы получения значений параметров с расчетом
		void GetParameterValueEx(LPCTSTR pszParamName, BSTR* pResStr, LPCTSTR pszDefault=_T(""), bool bCount=true);
		int GetParameterValueEx(LPCTSTR pszParamName, int nDefault, bool bCount=true);
		double GetParameterValueEx(LPCTSTR pszParamName, double fDefault, bool bCount=true);

		//----XML Сериализация-------------------------------------------------------------------------------
		//Считывает элемент со всеми подчинёнными из строки с XML, записанной с помощью WriteToXml
		bool ReadFromXML(LPCTSTR pszXml);
		//Считывает элемент со всеми подчинёнными из файла с XML
		bool ReadFromFile(LPCTSTR pszFileName);
		//Записывает элемент со всеми подчинёнными в XML
		bool WriteToXML(BSTR* pStrXmlRes) const;
		//Записывает элемент со всеми подчинёнными в XML
		bool WriteToFile(LPCTSTR pszFileName) const;

		//----Методы расширенного поиска----
		//Ищет во всём нижестоящем дереве первый узел, имеющий определённое значение заданного параметра
		bool FindElementByParameterValue(LPCTSTR pszParamName, LPCTSTR pszParamValue, bool bIgnoreCase, IElement** pResElement);
	};

	//Интерфейс определения параметра в БД и графических редакторах параметров
	__interface IParamDef: public IUnknown
	{
		//Типы параметров
		//Используются в определениях параметров БД CadLib таблица ParamTypes (3 базовых типа: строка, целое, действительное)
		enum EType
		{
			ptDBString=1,	//[DB:STR] редактируемая строка (можно вводить строку)
			ptDBInt=2,	//[DB:INT] число (можно вводить строку с проверкой на целое число)
			ptDBDouble=3,	//[DB:DBL] число (можно вводить строку с проверкой на действительное число)
			ptDBMemo=4,	//[DB:STR] многострочный текст (показывается первая строка и [...] для редактирования)
			ptDBListOpen=5, //[DB:STR] ComboBox с возможностью писать свои значения 
			ptDBHyperlink=17,	//[DB:STR] гиперссылка (подчёркнутый текст по которому можно кликнуть)
			ptDBListInt=18,	//[DB:INT "Список с целочисленным ключом"] не используется
			ptDBListDbl=19,	//[DB:DBL "Список с действительным ключом"] не используется
			ptDBListStr=20,	//[DB:STR "Список со строковым ключом"] Выпадающий список строк (ptListClosed, но с поиском выбранного индекса по строке)
		};

		//----Определение параметра--------------------------------------------------------------------------
		//Получение имени параметра
		LPCTSTR GetName();
		//Установка имени параметра
		//Список запрещённых символов: <=32 и '"@$&*()[]{}.,:;?/\<>|
		//Имя параметра принято писать заглавными латинскими буквами (PART_TYPE)
		void SetName(LPCTSTR pszName);
		//Заменяет запрещённые символы имени параметра на _
		//Возвращает true, если имя изменилось
		//Список запрещённых символов: <=32 и '"@$&*()[]{}.,:;?/\<>|
		bool MakeCorrectName();

		//Получение русского имени параметра
		LPCTSTR GetComment();
		//Установка русского имени параметра
		void SetComment(LPCTSTR pszComment);

		//Получение типа параметра
		EType GetType();
		//Установка типа параметра
		void SetType(EType type);
		//Принадлежит ли параметр типу, представленному действительным или целым числом
		bool IsNumber();

		//Является ли параметр только для чтения
		// (проверяется тип, ReadOnlyFlag, ReadOnlyCategory, наличие формулы в комментарии к значению)
		bool IsParamReadOnly();
		//Находится ли параметр хотя-бы в одной категории только для чтения
		bool IsInReadOnlyCategory();

		//Получение статуса флага параметра "только для чтения"
		bool GetReadOnlyFlag();
		//Установка статуса флага параметра "только для чтения"
		void SetReadOnlyFlag(bool bReadonly);
		//Смотрит на наличие знака = в начале формулы в комментарии к значению по умолчанию
		bool IsCalculated();

		//Находится ли параметр хотя-бы в одной скрытой категории
		bool IsHidden();

		//Получение точности преобразования значения параметра в строку
		int GetPrescision();
		//Установка точности преобразования значения параметра в строку
		void SetPrescision(int nP);	

		//Получение идентификатора группы связанных параметров
		int GetDependency();
		//Установка идентификатора группы связанных параметров
		void SetDependency(int n);

		//Проверка на полное совпадение с другим параметром
		bool IsEqual(const IParamDef* pOtherParamDef)const;

		//Создание копии определения параметра
		void Clone(IParamDef** pClonedParamDef);

		//-----Значение по умолчанию-------------------------------------------------------------------
		//Получение значения по умолчанию в виде строки
		LPCTSTR GetDefaultValue();
		//Получение значения по умолчанию в виде целого числа
		int GetDefaultValueInt();
		//Получение значения по умолчанию в виде действительного
		double GetDefaultValueDbl();

		//Установка значения параметра по умолчанию
		void SetDefaultValue(LPCTSTR pszDef);
		//Установка значения параметра по умолчанию
		void SetDefaultValue(int nVal);
		//Установка значения параметра по умолчанию
		void SetDefaultValue(double nVal);
		//Установка значения параметра по умолчанию
		void SetDefaultValue(VARIANT& vVal);

		//Получение комментария к значению по умолчанию
		LPCTSTR GetDefaultValueComment();
		//Установка комментария к значению по умолчанию
		void SetDefaultValueComment(LPCTSTR pszDef);
		//Установка комментария значения по умолчанию в соответствии с выбранным вариантом значения
		//записанным в значение по умолчанию
		void UpdateDefaultValueComment();

		//-----Категории параметра---------------------------------------------------------------------
		//Добавление параметра в категорию параметров с указанным именем и порядком следования параметра ORDER_MAX 
		void AddCategory(LPCTSTR pszCat);
		//Добавление параметра в категорию параметров с указанным именем и порядком следования параметра
		void AddCategory(LPCTSTR pszCat, UINT nOrder);

		//Получение количества категорий параметров, к которым принадлежит данный параметр
		idx_t GetCategoriesCount();
		//Получение категории параметра по индексу
		LPCTSTR GetCategory(idx_t n);
		//Получение индекса категории параметров по параметру (NOT_FOUND если не найдено)
		idx_t FindCategory(LPCTSTR pszCat);	
		//Принадлежит ли параметр указанной категории
		bool HasCategory(LPCTSTR pszCategory);

		//Удаление категории по индексу
		void RemoveCategory(idx_t n);
		//Очистка списка категорий к которым принадлежит параметр
		void RemoveAllCategories();

		//-----Варианты значения параметра-------------------------------------------------------------
		//Добавление варианта значения параметра
		//pszValue - значение параметра
		//pszValueComment - комментарий к значению
		//bCheckUnique - если да, то повторяющееся значение не будет добавлено, но комментарий обновится
		void AddValue(LPCTSTR pszValue, LPCTSTR pszValueComment, bool bCheckUnique);

		//Получение количества вариантов значений параметра
		idx_t GetValuesCount();

		//Получение значения варианта значения параметра по индексу
		LPCTSTR GetValue(idx_t n);
		//Получение комментария к значению варианта значения параметра по индексу
		LPCTSTR GetValueComment(idx_t n);
		//Получение индекса варианта значения параметра по значению
		idx_t FindValueIndex(LPCTSTR pszVal) const;

		//Удаление варианта значения параметра по индексу
		void DeleteValue(idx_t n);
		//Удаление варианта значения параметра по значению
		void DeleteValue(LPCTSTR pszValue);
		//Удаление всех вариантов значения параметра
		void DeleteAllValues();
	};

	//Интерфейс окна прогресса с кнопкой "Отмена"
	__interface IProgressWnd
	{
		//Обновляет статус окна прогресса
		//pszMessage - сообщение для добавления в окно лога прогресса (или NULL)
		//fProgress - доля выполненной работы
		// < 0 - нет изменения прогресса (только добавление сообщения или для извлечения отмены)
		// [0; 1] - изменить прогресс на обозначенную долю
		// > 0 - показать неопределённость процесса выполнения (бегунок)
		//Метод возвращает false, если пользователь желает немедленно прервать операцию
		bool ReportProgress(LPCTSTR pszMessage, double fProgress);
	};

	//Интерфейс коллекции определений параметров
	__interface IParamDefs: public IUnknown
	{
		//Получение количества определений параметров
		idx_t GetCount()const;
		//Получение определения параметра по индексу
		HRESULT GetParam(idx_t n, IParamDef** pResParamDef);
		//Получение определения параметра по имени
		HRESULT GetParam(LPCTSTR pszName, IParamDef** pResParamDef);

		//bool HasParam(LPCTSTR pszName); см. ниже

		//Получение индекса по имени определения параметра
		idx_t GetParamIndex(LPCTSTR pszParam);

		//Добавляет новое определение параметров в коллекцию
		//В случае, если определение уже в коллекции возвращает существующее
		void AddParam(LPCTSTR szName, LPCTSTR szComment, IParamDef **pNewParamDef=NULL);

		//Добавляет копию pSrc в коллекцию определений параметров
		//Если bCheck, то происходит поиск существующего определения параметра в коллекции и его возврат в случае успешного поиска
		void AddParamCopy(IParamDef* pSrc, bool bCheck=true, IParamDef **pNewParamDef=NULL);

		//Копирует все недостающие определения параметров из источника
		void AddParamsCopy(const IParamDefs* source);

		//Удаляет определение параметра по имени
		bool RemoveParam(LPCTSTR pszParam);

		//Очищает коллекцию определений параметров
		void Clear();

		//Загрузка определений параметров из файла
		bool LoadFromFile(LPCTSTR pszPath);
		//Сохранение коллекции определений параметров в файл
		bool SaveToFile(LPCTSTR pszPath);

		//Имеется ли определение параметра с таким именем
		bool HasParam(LPCTSTR pszName);

		//Обновляет/добавляет определение параметра в ассоциированной БД
		HRESULT UpdateDbParameter(IParamDef* pParam);

		//Удаляет определение параметра с указанным индексом из БД
		//В БД не должно быть ссылок на данное определение параметров
		HRESULT DeleteDBParameter(int nParamIndex);

		//Обновляет все определения параметров в ассоциированной БД
		HRESULT SaveToDb();
	};

#define MSTUDIO_DATA_API_CUR_VER_MAJOR 1
#define MSTUDIO_DATA_API_CUR_VER_MINOR 9

	__interface IFactoryInterface
	{
	public:
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_DATA_API_CUR_VER_MAJOR и MSTUDIO_DATA_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		HRESULT CreateParam(IParam** pNewParam, LPCTSTR pszName=L"", LPCTSTR pszValue=L"", 
			LPCTSTR pszNameComment=L"", LPCTSTR pszValueComment=L"");

		HRESULT CreateElement(IElement** pNewElement, LPCTSTR pszName = L"");

		HRESULT CreateParamDef(IParamDef** pNewParamDef, LPCTSTR szName, LPCTSTR szComment, 
			IParamDef::EType type=IParamDef::ptDBListOpen, bool bReadOnly=false, int nPrescision=-1,int nDependency=0);

		//Создание объекта определений параметров
		HRESULT CreateParamDefs(IParamDefs** pNewParamDefs);

		//Получение ссылки на глобальную коллекцию определений параметров, используемую по умолчанию в ModelStudio
		HRESULT GetGlobalParamDefs(IParamDefs** pGlobalParamDefs);

		//Получение главного ключа приложения из конфига
		HRESULT GetMainAppKey(BSTR* pStrResAppKey);
	};

#define MODEL_STUDIO_DATA_MODULE_NAME L"mstudioData.dll"
#define MODEL_STUDIO_DATA_ENTRY_NAME "GetMStudioDataInterface"

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

				HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_DATA_MODULE_NAME);
				if (!hDataDll)
					return NULL;

				MSTPluginEntryFn* pGetFn = 
					(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_DATA_ENTRY_NAME);
				if (!pGetFn)
					return NULL;

				//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
				pRes = pGetFn(MSTUDIO_DATA_API_CUR_VER_MAJOR, MSTUDIO_DATA_API_CUR_VER_MINOR);
				if (!pRes)
					return NULL;

				if (bCheckVersion)
				{
					int nMajorVer = 0;
					int nMinorVer = 0;
					pRes->GetApiVersion(nMajorVer, nMinorVer);
					if (nMajorVer != MSTUDIO_DATA_API_CUR_VER_MAJOR ||
						nMinorVer < MSTUDIO_DATA_API_CUR_VER_MINOR)
					{
						CString strErrorMsg;
						strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
							MODEL_STUDIO_DATA_MODULE_NAME,
							nMajorVer, nMinorVer,
							MSTUDIO_DATA_API_CUR_VER_MAJOR, MSTUDIO_DATA_API_CUR_VER_MINOR);
						throw strErrorMsg;
					}
				}

				return pRes;
			}
	};
}