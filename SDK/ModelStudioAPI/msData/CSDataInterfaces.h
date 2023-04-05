#pragma once

#include "commtpl.h"

namespace MStudioData
{
	//��������� ��������� (��������) � IParamsOwner
	__interface IParam: public IUnknown
	{
		//��������� ����� ���������
		LPCTSTR GetName() const;
		//��������� �������� ����� ���������
		LPCTSTR GetComment() const;
		//��������� �������� ��������� � ���� ������
		void GetValue(BSTR *pStrDest) const;
		//��������� ����������� � �������� ��������� (����� �������)
		LPCTSTR GetValueComment() const;

		//��������� ����� ���������
		//������ ����������� ��������: <=32 � '"@$&*()[]{}.,:;?/\<>|
		//��� ��������� ������� ������ ���������� ���������� ������� (PART_TYPE)
		void SetName(LPCTSTR pszVal);
		//��������� �������� ����� ���������
		void SetComment(LPCTSTR pszVal);
		//��������� �������� ��������� � ���� ������
		void SetValue(LPCTSTR pszVal);
		//��������� ����������� � �������� ��������� (����� �������)
		void SetValueComment(LPCTSTR pszVal);

		//���������� �������� ��������� ���������
		void AssignValue(const IParam* pSourceParam);
		//���������� ����������� � �������� ��������� ���������
		void AssignValueComment(const IParam* pSourceParam);
		//���������� �������� � ����������� � �������� ��������� ���������
		void AssignValueAndComment(const IParam* pSourceParam);

		//�������� ����� ���������
		void Clone(IParam** pClonedParam);

		//��������� ���� ���������� �� ����� ��� ����� ��������
		int Compare(const IParam* pOther);

		//���������� ��� � ������� ��������
		LPCTSTR GetUpperName() const; 
	};

#pragma pack(push, 1)
	//��������� ���������� ������� ������� ��������
	//������� ���������� � AcGeVector3d, CMSVector3d, CSVECTORD3 � �������
	struct CCS3DoubleVector
	{
		double x, y, z;
	};
#pragma pack(pop)

	//��������� ��� ��������� ���������� IParam
	__interface IParamsOwner: public IUnknown
	{
		//��������� �������� ����������
		//���� ��������� ������ � ��������� - �� ��������
		void SetParameter(LPCTSTR pszName,LPCTSTR pszValue,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,double fValue,LPCTSTR pszComment,LPCTSTR pszValueComment,int nPrescision);
		void SetParameter(LPCTSTR pszName,double fValue,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,int nValue,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,const GUID& guid,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));
		void SetParameter(LPCTSTR pszName,const CCS3DoubleVector &vt,LPCTSTR pszComment=_T(""),LPCTSTR pszValueComment=_T(""));

		//���������� ������ ��������� (��� ������� �������������)
		void AddParameter(LPCTSTR pszName, LPCTSTR pszValue, LPCTSTR pszComment,
			LPCTSTR pszValueComment, IParam** pRes=NULL);

		//���������� ������ ��������� (���� bCheckName � �������� ��� ����, �� �������� �� �����������)
		void AddParamCopy(const IParam* pSrc, bool bCheckName);

		//���������� ��������� (��������� *ERASED*, *VALUE_SET* � ������ ������ �� ������� ��������������)
		void ApplyParameter(const IParam* pParam);
		//���������� ���� ���������� ���������
		void ApplyParameters(const IParamsOwner* pParamsOwner);

		//---������ � ��������� ��������� ����������� GetValue, �� � ��������� �������� �� ���������---
		LPCTSTR GetParameterValue(LPCTSTR pszParamName,LPCTSTR pszDefault=_T(""))const;
		double GetParameterValue(LPCTSTR pszParamName,double fDefault)const;
		int GetParameterValue(LPCTSTR pszParamName,int nDefault)const;
		CCS3DoubleVector GetParameterValue(LPCTSTR pszParamName, const CCS3DoubleVector &vtDefault)const;

		//������ �������� ��������� � ����������
		//���������� false, ���� �������� �� ������ (�������� ��������� �� ��������)
		bool GetValue(LPCTSTR pszParamName, BSTR *pStrDest) const;

		//������ �������� ��������� � ����������
		//���������� false, ���� �������� �� ������ (�������� ��������� �� ��������)
		//� ������ ������ ����������� ������������ �������� 0
		bool GetValue(LPCTSTR pszParamName, int& nDest) const;

		//������ �������� ��������� � ����������
		//���������� false, ���� �������� �� ������ (�������� ��������� �� ��������)
		bool GetValue(LPCTSTR pszParamName, bool& bDest) const;

		//������ �������� ��������� � ����������
		//���������� false, ���� �������� �� ������ (�������� ��������� �� ��������)
		//� ������ ������ ����������� ������������ �������� 0.0
		bool GetValue(LPCTSTR pszParamName, double& fDest) const;

		//������ �������� ��������� � ����������
		//���������� false, ���� �������� �� ������ ��� ������ ����������� (�������� ��������� �� ��������)
		bool GetValue(LPCTSTR pszParamName, CCS3DoubleVector& vtDest) const;

		//������ �������� ��������� � ����������
		//���������� false, ���� �������� �� ������ ��� ������ ����������� (�������� ��������� �� ��������)
		bool GetValue(LPCTSTR pszParamName, GUID& uidDest) const;

		//��������� ��������� �� ����� (���� �������� �� ������ ���������� false)
		bool GetParameter(LPCTSTR pszName, IParam** pResParam)const;

		//��������� ��������� �� ������� (���� �������� �� ������ ���������� false)
		bool GetParameter(idx_t nParam, IParam** pResParam) const;

		//��������� ���������� ���������� (��������)
		idx_t GetParamsCount() const;

		//�������� ��������� �� �����
		void RemoveParameter(LPCTSTR pszParam);
		//�������� ��������� �� �������
		void RemoveParameter(idx_t nParam);	

		//�������� ���� ����������
		void DeleteAllParams();	

		//�������� ����� ���������
		void Clone(IParamsOwner** pClonedParams);

		//������������ ������ ��������� ���� (��� ����� �����)
		void CopyParamsFrom(const IParamsOwner* pSrcEl);

		//������� ���������� (���������� ��������� pSrcParams)
		//bMergeEmptyValues - ��������� �� ��������� ��� �������� �� pSrcParams
		//bSrcValuePriority - ��������� ������������ �������� ������������ ����������
		void MergeParamsFrom(const IParamsOwner* pSrcParams, bool bMergeEmptyValues, bool bSrcValuePriority);

		//��������� ���� ���������
		bool IsEqualParameters(const IParamsOwner *pOtherParams);

		//�������������� ������ � GUID ����� ��, ��� ������������ � ������ SetParameter
		void FormatUID(const GUID& guid, BSTR *pStrDest);		
	};

	//��������� ������ ���������� (IParamsOwner � ����������� �����)
	__interface IElement: public IParamsOwner
	{
		//----������� �������--------------------------------------------------------------------------------
		//��������� ����� ��������
		LPCTSTR GetName() const;	
		//������������� ��� ��������
		void SetName(LPCTSTR pszName);

		//��������� �������������� �������� (���������� ��� ����� ������)
		int GetId() const;

		//��������� ������� ������� �������� � ������ (������� � 0)
		int GetLevel(void) const;

		//��������� ����������������� �������������� (Tag)
		int GetModelUID() const;
		//��������� ����������������� �������������� (Tag)
		void SetModelUID(int uid);	

		//----���������� ��������---------------------------------------------------------------------------
		//��������� ���������� ���������� ���������
		idx_t GetChildCount() const;
		//��������� ����������� �������� �� �������
		bool GetChild(idx_t nChild, IElement** pResChild) const;
		//��������� ����������� �������� �� ����� (��� NULL)
		bool GetChild(LPCTSTR pszName, IElement** pResChild) const;
		//��������� ����������� �������� �� ����� ��� ����� ��������
		bool GetChildNoCase(LPCTSTR pszName, IElement** pResChild) const;
		//��������� ������� �� ����������� ��������
		idx_t GetChildIndex(IElement* pEl) const;
		//����� �������� ������ �� ��������������
		bool GetElementById(idx_t nID, IElement** pResElement) const;
		//����� ����������� �������� �� ��������������
		bool GetChildById(int nID, IElement** pResChild);
		//�������� �� ������� pChild ������������ ������� ��������
		bool HasChild(IElement* pChild);

		//�������� ����������� �������� � ��������� �����
		void AddChild(LPCTSTR pszName, IElement** pResChild);
		//�������� ����������� �������� � ��������� ����� ������� � �����
		void InsertChild(idx_t nIdx, LPCTSTR pszName, IElement** pResChild);
		//��������� ����� pChildToCopy � ���� ����������� ��������
		void AddChildCopy(const IElement* pChildToCopy, IElement** pResChild);

		//��������� ������������� �������������� ��������� � ������
		int GetMaxElementId();

		//----������������ ��������--------------------------------------------------------------------------
		//��������� ������������� �������� (��� NULL)
		bool GetParent(IElement** pResParent)const;
		//��������� ��������� �������� (��� this)
		void GetRoot(IElement** pResRoot)const;

		//----��������---------------------------------------------------------------------------------------
		//�������� ����������� ��������
		void DeleteChild(IElement* pChild);
		//������� ��� ���������� ��������
		void DeleteAllChildren();	
		//�������� ������� �������� �� �������� (� �� ������)
		void Delete();

		//----������ ���������������� ������-----------------------------------------------------------------
		//��������� ���� �� �������
		int GetTag(int n)const;
		//��������� ���� �� ������� (� �������������� ����������� ������� � ����������)
		void SetTag(int nTag, int n);
		//��������� ������ ������� ���������������� ������ (� ����������)
		void SetTagsCount(int nTags);
		//��������� ������ ������� ���������������� ������
		int GetTagsCount()const;
		//��������� �������  ���������������� ������ (������� GetTagsCount)
		const int* GetTags()const;

		//----������ � ���������-----------------------------------------------------------------------------
		//�������� ����� ������ ����������
		void Clone(IElement** pClonedElement);

		//������������ ������� ������ ����� (��� ����� �����)
		void CopyFrom(const IElement* pSourceElement);

		//������� � ������� pSrcElement (���������� ������ pSrcElement � ����������� ����� ����� � �������� ����������)
		//������� ������� �������� ���������� � pSrcElement, ����� ���� ���������� ��������� �� ��������� �����
		//bMergeEmptyValues - ��������� �� ��������� ��� ��������
		//bSrcValuePriority - ��������� ������������ �������� ������������ ����������
		//bSetName - ������������� ������� ������� � ��� pSrcElement
		void Merge(const IElement* pSrcElement, bool bMergeNullValues, bool bSrcValuePriority, bool bSetName);

		//�������� ���������� �������� �������� ��������
		//�� ����� ���������� ��������� �� pSourceElement
		void CopyChildrenFrom(const IElement* pSourceElement);

		//----������ �������� ����������---------------------------------------------------------------------
		//������ ���� ���������� ����� �������� � ������������ ������
		//������� ��� ������� ������������ � ����������� � ������� ����������, ������� � ������� '='
		void CalculateParameters();

		//������ ��������� �������� ���������� � ��������
		void GetParameterValueEx(LPCTSTR pszParamName, BSTR* pResStr, LPCTSTR pszDefault=_T(""), bool bCount=true);
		int GetParameterValueEx(LPCTSTR pszParamName, int nDefault, bool bCount=true);
		double GetParameterValueEx(LPCTSTR pszParamName, double fDefault, bool bCount=true);

		//----XML ������������-------------------------------------------------------------------------------
		//��������� ������� �� ����� ����������� �� ������ � XML, ���������� � ������� WriteToXml
		bool ReadFromXML(LPCTSTR pszXml);
		//��������� ������� �� ����� ����������� �� ����� � XML
		bool ReadFromFile(LPCTSTR pszFileName);
		//���������� ������� �� ����� ����������� � XML
		bool WriteToXML(BSTR* pStrXmlRes) const;
		//���������� ������� �� ����� ����������� � XML
		bool WriteToFile(LPCTSTR pszFileName) const;

		//----������ ������������ ������----
		//���� �� ��� ����������� ������ ������ ����, ������� ����������� �������� ��������� ���������
		bool FindElementByParameterValue(LPCTSTR pszParamName, LPCTSTR pszParamValue, bool bIgnoreCase, IElement** pResElement);
	};

	//��������� ����������� ��������� � �� � ����������� ���������� ����������
	__interface IParamDef: public IUnknown
	{
		//���� ����������
		//������������ � ������������ ���������� �� CadLib ������� ParamTypes (3 ������� ����: ������, �����, ��������������)
		enum EType
		{
			ptDBString=1,	//[DB:STR] ������������� ������ (����� ������� ������)
			ptDBInt=2,	//[DB:INT] ����� (����� ������� ������ � ��������� �� ����� �����)
			ptDBDouble=3,	//[DB:DBL] ����� (����� ������� ������ � ��������� �� �������������� �����)
			ptDBMemo=4,	//[DB:STR] ������������� ����� (������������ ������ ������ � [...] ��� ��������������)
			ptDBListOpen=5, //[DB:STR] ComboBox � ������������ ������ ���� �������� 
			ptDBHyperlink=17,	//[DB:STR] ����������� (������������ ����� �� �������� ����� ��������)
			ptDBListInt=18,	//[DB:INT "������ � ������������� ������"] �� ������������
			ptDBListDbl=19,	//[DB:DBL "������ � �������������� ������"] �� ������������
			ptDBListStr=20,	//[DB:STR "������ �� ��������� ������"] ���������� ������ ����� (ptListClosed, �� � ������� ���������� ������� �� ������)
		};

		//----����������� ���������--------------------------------------------------------------------------
		//��������� ����� ���������
		LPCTSTR GetName();
		//��������� ����� ���������
		//������ ����������� ��������: <=32 � '"@$&*()[]{}.,:;?/\<>|
		//��� ��������� ������� ������ ���������� ���������� ������� (PART_TYPE)
		void SetName(LPCTSTR pszName);
		//�������� ����������� ������� ����� ��������� �� _
		//���������� true, ���� ��� ����������
		//������ ����������� ��������: <=32 � '"@$&*()[]{}.,:;?/\<>|
		bool MakeCorrectName();

		//��������� �������� ����� ���������
		LPCTSTR GetComment();
		//��������� �������� ����� ���������
		void SetComment(LPCTSTR pszComment);

		//��������� ���� ���������
		EType GetType();
		//��������� ���� ���������
		void SetType(EType type);
		//����������� �� �������� ����, ��������������� �������������� ��� ����� ������
		bool IsNumber();

		//�������� �� �������� ������ ��� ������
		// (����������� ���, ReadOnlyFlag, ReadOnlyCategory, ������� ������� � ����������� � ��������)
		bool IsParamReadOnly();
		//��������� �� �������� ����-�� � ����� ��������� ������ ��� ������
		bool IsInReadOnlyCategory();

		//��������� ������� ����� ��������� "������ ��� ������"
		bool GetReadOnlyFlag();
		//��������� ������� ����� ��������� "������ ��� ������"
		void SetReadOnlyFlag(bool bReadonly);
		//������� �� ������� ����� = � ������ ������� � ����������� � �������� �� ���������
		bool IsCalculated();

		//��������� �� �������� ����-�� � ����� ������� ���������
		bool IsHidden();

		//��������� �������� �������������� �������� ��������� � ������
		int GetPrescision();
		//��������� �������� �������������� �������� ��������� � ������
		void SetPrescision(int nP);	

		//��������� �������������� ������ ��������� ����������
		int GetDependency();
		//��������� �������������� ������ ��������� ����������
		void SetDependency(int n);

		//�������� �� ������ ���������� � ������ ����������
		bool IsEqual(const IParamDef* pOtherParamDef)const;

		//�������� ����� ����������� ���������
		void Clone(IParamDef** pClonedParamDef);

		//-----�������� �� ���������-------------------------------------------------------------------
		//��������� �������� �� ��������� � ���� ������
		LPCTSTR GetDefaultValue();
		//��������� �������� �� ��������� � ���� ������ �����
		int GetDefaultValueInt();
		//��������� �������� �� ��������� � ���� ���������������
		double GetDefaultValueDbl();

		//��������� �������� ��������� �� ���������
		void SetDefaultValue(LPCTSTR pszDef);
		//��������� �������� ��������� �� ���������
		void SetDefaultValue(int nVal);
		//��������� �������� ��������� �� ���������
		void SetDefaultValue(double nVal);
		//��������� �������� ��������� �� ���������
		void SetDefaultValue(VARIANT& vVal);

		//��������� ����������� � �������� �� ���������
		LPCTSTR GetDefaultValueComment();
		//��������� ����������� � �������� �� ���������
		void SetDefaultValueComment(LPCTSTR pszDef);
		//��������� ����������� �������� �� ��������� � ������������ � ��������� ��������� ��������
		//���������� � �������� �� ���������
		void UpdateDefaultValueComment();

		//-----��������� ���������---------------------------------------------------------------------
		//���������� ��������� � ��������� ���������� � ��������� ������ � �������� ���������� ��������� ORDER_MAX 
		void AddCategory(LPCTSTR pszCat);
		//���������� ��������� � ��������� ���������� � ��������� ������ � �������� ���������� ���������
		void AddCategory(LPCTSTR pszCat, UINT nOrder);

		//��������� ���������� ��������� ����������, � ������� ����������� ������ ��������
		idx_t GetCategoriesCount();
		//��������� ��������� ��������� �� �������
		LPCTSTR GetCategory(idx_t n);
		//��������� ������� ��������� ���������� �� ��������� (NOT_FOUND ���� �� �������)
		idx_t FindCategory(LPCTSTR pszCat);	
		//����������� �� �������� ��������� ���������
		bool HasCategory(LPCTSTR pszCategory);

		//�������� ��������� �� �������
		void RemoveCategory(idx_t n);
		//������� ������ ��������� � ������� ����������� ��������
		void RemoveAllCategories();

		//-----�������� �������� ���������-------------------------------------------------------------
		//���������� �������� �������� ���������
		//pszValue - �������� ���������
		//pszValueComment - ����������� � ��������
		//bCheckUnique - ���� ��, �� ������������� �������� �� ����� ���������, �� ����������� ���������
		void AddValue(LPCTSTR pszValue, LPCTSTR pszValueComment, bool bCheckUnique);

		//��������� ���������� ��������� �������� ���������
		idx_t GetValuesCount();

		//��������� �������� �������� �������� ��������� �� �������
		LPCTSTR GetValue(idx_t n);
		//��������� ����������� � �������� �������� �������� ��������� �� �������
		LPCTSTR GetValueComment(idx_t n);
		//��������� ������� �������� �������� ��������� �� ��������
		idx_t FindValueIndex(LPCTSTR pszVal) const;

		//�������� �������� �������� ��������� �� �������
		void DeleteValue(idx_t n);
		//�������� �������� �������� ��������� �� ��������
		void DeleteValue(LPCTSTR pszValue);
		//�������� ���� ��������� �������� ���������
		void DeleteAllValues();
	};

	//��������� ���� ��������� � ������� "������"
	__interface IProgressWnd
	{
		//��������� ������ ���� ���������
		//pszMessage - ��������� ��� ���������� � ���� ���� ��������� (��� NULL)
		//fProgress - ���� ����������� ������
		// < 0 - ��� ��������� ��������� (������ ���������� ��������� ��� ��� ���������� ������)
		// [0; 1] - �������� �������� �� ������������ ����
		// > 0 - �������� ��������������� �������� ���������� (�������)
		//����� ���������� false, ���� ������������ ������ ���������� �������� ��������
		bool ReportProgress(LPCTSTR pszMessage, double fProgress);
	};

	//��������� ��������� ����������� ����������
	__interface IParamDefs: public IUnknown
	{
		//��������� ���������� ����������� ����������
		idx_t GetCount()const;
		//��������� ����������� ��������� �� �������
		HRESULT GetParam(idx_t n, IParamDef** pResParamDef);
		//��������� ����������� ��������� �� �����
		HRESULT GetParam(LPCTSTR pszName, IParamDef** pResParamDef);

		//bool HasParam(LPCTSTR pszName); ��. ����

		//��������� ������� �� ����� ����������� ���������
		idx_t GetParamIndex(LPCTSTR pszParam);

		//��������� ����� ����������� ���������� � ���������
		//� ������, ���� ����������� ��� � ��������� ���������� ������������
		void AddParam(LPCTSTR szName, LPCTSTR szComment, IParamDef **pNewParamDef=NULL);

		//��������� ����� pSrc � ��������� ����������� ����������
		//���� bCheck, �� ���������� ����� ������������� ����������� ��������� � ��������� � ��� ������� � ������ ��������� ������
		void AddParamCopy(IParamDef* pSrc, bool bCheck=true, IParamDef **pNewParamDef=NULL);

		//�������� ��� ����������� ����������� ���������� �� ���������
		void AddParamsCopy(const IParamDefs* source);

		//������� ����������� ��������� �� �����
		bool RemoveParam(LPCTSTR pszParam);

		//������� ��������� ����������� ����������
		void Clear();

		//�������� ����������� ���������� �� �����
		bool LoadFromFile(LPCTSTR pszPath);
		//���������� ��������� ����������� ���������� � ����
		bool SaveToFile(LPCTSTR pszPath);

		//������� �� ����������� ��������� � ����� ������
		bool HasParam(LPCTSTR pszName);

		//���������/��������� ����������� ��������� � ��������������� ��
		HRESULT UpdateDbParameter(IParamDef* pParam);

		//������� ����������� ��������� � ��������� �������� �� ��
		//� �� �� ������ ���� ������ �� ������ ����������� ����������
		HRESULT DeleteDBParameter(int nParamIndex);

		//��������� ��� ����������� ���������� � ��������������� ��
		HRESULT SaveToDb();
	};

#define MSTUDIO_DATA_API_CUR_VER_MAJOR 1
#define MSTUDIO_DATA_API_CUR_VER_MINOR 9

	__interface IFactoryInterface
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_DATA_API_CUR_VER_MAJOR � MSTUDIO_DATA_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		HRESULT CreateParam(IParam** pNewParam, LPCTSTR pszName=L"", LPCTSTR pszValue=L"", 
			LPCTSTR pszNameComment=L"", LPCTSTR pszValueComment=L"");

		HRESULT CreateElement(IElement** pNewElement, LPCTSTR pszName = L"");

		HRESULT CreateParamDef(IParamDef** pNewParamDef, LPCTSTR szName, LPCTSTR szComment, 
			IParamDef::EType type=IParamDef::ptDBListOpen, bool bReadOnly=false, int nPrescision=-1,int nDependency=0);

		//�������� ������� ����������� ����������
		HRESULT CreateParamDefs(IParamDefs** pNewParamDefs);

		//��������� ������ �� ���������� ��������� ����������� ����������, ������������ �� ��������� � ModelStudio
		HRESULT GetGlobalParamDefs(IParamDefs** pGlobalParamDefs);

		//��������� �������� ����� ���������� �� �������
		HRESULT GetMainAppKey(BSTR* pStrResAppKey);
	};

#define MODEL_STUDIO_DATA_MODULE_NAME L"mstudioData.dll"
#define MODEL_STUDIO_DATA_ENTRY_NAME "GetMStudioDataInterface"

	//����� ��� ��������� �������� ���������� API ModelStudio ������� ������
	//������ ��� ������ ���� �������� � ������
	class CMStudioDataInterface
	{
		public:
			typedef IFactoryInterface* PASCAL MSTPluginEntryFn(int nClientMajorVer, int nClientMinorVer);

			//��������� �������� ���������� API ModelStudio ������� ������
			//���� ���������� bCheckVersion, �� ����� ����������� �������� ������������� ������ ������������
			//������ � ������� API � � ������ ��������������� ��������� ���������� ���� CString
			static IFactoryInterface* Get(bool bCheckVersion=true)
			{
				//�������� ���������� ������ ������� ����������� ������
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

				//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
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
						strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
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