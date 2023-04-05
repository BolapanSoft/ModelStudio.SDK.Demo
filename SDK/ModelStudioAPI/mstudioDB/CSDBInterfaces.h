#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\CSGraphics\ms3DTypes.h"
#include "..\msData\IntermediateGeometry2.h"

namespace MStudioDB
{
	//��������� ������� � ������� ����������� �� ������� ��
	__interface ILibObjectInfo: public IUnknown
	{
		//������ ������� ��
		enum DbSysStatus
		{
			dbStatusCommon = 1,	//1,'COMMON','�����' (����� ����)
			dbStatudShared = 2,	//2,'SHARED','��������' - (������������ ��������� ������ � ������ �������, �� ����� ��� �������)
			dbStatusUser = 3	//3,'PRIVATE','����������������' (����� ������ ������������-���������)
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

		//��������� ���� ��������� ����������� ������� � �������
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
	

	//��������� ������ �� CadLib
	__interface IDataBase: public IUnknown
	{
		enum DbPlatform
		{
			dbMSSQL = 0, 
			dbMSSQLNCLI = 1, 
			dbPostgreSQL = 2 
		};
		//��������� ��
		HRESULT GetDriver(BSTR* pResDB);

		DbPlatform GetPlatform();		
		void SetPlatform(DbPlatform dbp,LPCTSTR pszDriver);

		int GetPort();
		void SetPort(int n);

		//������� �� ����������� � ��
		bool IsConnected();

		//�������� ����������� � �� � ���������� �����������
		//���� pszUser - ������ ������ - ������������ �������������� Windows
		//���� bSilent==true ������ ��������� � ���, � �� � ������
		bool Connect(LPCTSTR pszServerName, LPCTSTR pszDatabase, LPCTSTR pszUser,
			LPCTSTR pszPassword, bool bSilent=false);

		//���������� ������ ����������� � �� � ��������� ������� � ������������ � �� � ������ ������� ��
		//���������� true � ������ ��������� �����������,
		//false � ������ ������ ����������� ��� ������ �����������
		//pszServerName, pszDatabase, pszUser, pszPassword - ������ ��� ����� � ������ �� ���������
		//E��� pszUser �� ����� ��� ������, �� ����� ������������ �������������� Windows
		//bStd - ������������ ����������� ��������� ��, � �� strServer...
		//pszTitle - ��������� ���� �����������
		//pCanceled  - true ������ ���������� �� Cancel
		bool UIConnect(LPCTSTR pszServerName=NULL, LPCTSTR pszDatabase=NULL, LPCTSTR pszUser=NULL,
			LPCTSTR pszPassword=NULL, bool bStd=true, LPCTSTR pszTitle=NULL, bool* pCanceled=NULL);

		//��������� ��������� ����������� ����������, ��������� � ��
		HRESULT GetParamDefs(MStudioData::IParamDefs** pDBParamDefs);

		//��������� ����� ������������� �������
		HRESULT GetServer(BSTR* pResServer);

		//��������� ����� ������������ ��
		HRESULT GetDatabaseName(BSTR* pResDB);

		//��������� ����� ������������, ������������� � ��.
		//� ������ �������������� Windows ������������ ������ ������
		HRESULT GetUserName(BSTR* pResStr);

		//��������� ������ ������������, ���������� ��� �����������
		HRESULT GetUserPassword(BSTR* pResStr);

		//��������� ��� �������� �������� � ��, ����� ������ �������������� ����������� ��� (���� ������ � ���������)
		//pRootElement - ������ ��� ����������
		//nCatDef - ��������� ������� � ������, ���� �� ������ pCategories
		//���� ������ ������ ��������� pCategories, �� ������ ��������� ������ ��������������� GetId ��������
		//bUseProtection - ������������ �� ������ ����������
		//���� ������� bApplyNewIdsToModelUid, �� � ModelUID ������� �������� ����� ������� idObject ��� ������ ������� ��
		//nSysStatus - ��������� ������ ������� (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		long AddObject(MStudioData::IElement* pRootElement, int nCatDef, bool bUseProtection=true,
			int pCategories[]=NULL, int nCategoriesLength=0,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser,
			bool bApplyNewIdsToModelUid=false);

		//��������� ��� �������� �������� � ��, ����� ������ �������������� ����������� ��� (���� ������ � ���������)
		//pRootElement - ������ ��� ����������
		//nCatDef - ��������� ������� � ������, ���� �� ������ pCategories
		//���� ������ ������ ��������� pCategories, �� ������ ��������� ������ ��������������� GetId ��������
		//paramsMap - �� ������������
		//bUseProtection - �� ������������
		//���� ������� bApplyNewIdsToModelUid, �� � ModelUID ������� �������� ����� ������� idObject ��� ������ ������� ��
		//nSysStatus - ��������� ������ ������� (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		long AddObject(MStudioData::IElement* pRootElement, int nCatDef,
			ILibObjectParamsMap** pParamsMap=NULL, bool bAutoCommitParams=true,
			bool bUseProtection=true, int pCategories[]=NULL, int nCategoriesLength=0,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser,
			bool bApplyNewIdsToModelUid=false);

		//��������� ���������� ������ � �������������
		//pElement - ������ ��� ����������
		//nCurrentCat - ��������� ������� � ������, ���� �� ������ pCategories
		//���� ������ ������ ��������� pCategories, �� ������ ��������� ������ ��������������� GetId ��������
		//paramsMap - [in, out] ��� ���������� ��������, ������� ���������� ��������� � �� �������� (Commit)
		//bUseProtection - ������������ �� ������ ����������
		//���� ������� bApplyNewIdsToModelUid, �� � ModelUID ������� �������� ����� ������� idObject ��� ������ ������� ��
		//bInsertWholeHierarchy - ���� ��, �� ����� ��������� ��� ���������� ��������
		//nSysStatus - ��������� ������ ������� (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		long InsertSubObject(MStudioData::IElement* pElement, long lParentObject, int nCurrentCat,			
			ILibObjectParamsMap** pParamsMap,
			int pCategories[]=NULL, int nCategoriesLength=0,
			bool bUseProtection=true, bool bApplyNewIdsToModelUid=false,
			bool bInsertWholeHierarchy=true,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser);

		//��������� �������� PARAM_DBUID ������� � �� ������� �������� � ������������� �� ���������
		//���� �� ����� PARAM_DBUID (��� ����� ������ �� ������), �� ����������� ����� ������
		//pElement - �������� �������� ��� ������������
		//nCategory - ��������� ���� �������� (�� ���������������, ������������ ��� �������� �����)
		//paramsMap - [in, out] ��� ���������� ��������, ������� ���������� ��������� � �� �������� (Commit)
		//bRemoveMissingSubs - ������� �� ������� �������� ��, ������� ��� � �������� ��������
		//bProcessWholeHierarchy - ���� ���, �� ����� ��������� ������ �������� ������
		//���� ������� bApplyNewIdsToModelUid, �� � ModelUID ������� �������� ����� ������� idObject ��� ������ ������� ��
		//nSysStatus - ��������� ������ ������� (DB_SYS_STATUS_COMMON, DB_SYS_STATUS_USER)
		int ActualizeObject(MStudioData::IElement* pElement, int nCategory, ILibObjectParamsMap** pParamsMap,
			bool bRemoveMissingSubs=true,
			bool bProcessWholeHierarchy=true, bool bApplyNewIdsToModelUid=false,
			ILibObjectInfo::DbSysStatus nSysStatus=ILibObjectInfo::dbStatusUser);

		//��������� ����� ��������� ������� dbObject
		//���� �� ����� ������ ��������� pCategories, �� ���� �������� ����������� ��������� nCatDef ��� ��������� �������
		//��������� �� ��, ��� ��� �������� �������
		//��� ������� ��������������� (���� ���������) � ����������� � newParameters
		//������������ true � ������ ��������� ���������� ����������
		bool SetObjectParameters(ILibObjectInfo* pDbObject, MStudioData::IElement* pNewParameters,
			int nCatDef=0, bool bUseProtection=false, int pCategories[]=NULL, int nCategoriesLength=0);

		//��������� ���������� �� ������� �� GUID
		//���������� NULL ���� ������ �� ������
		HRESULT GetLibraryObject(const GUID &objectUID, ILibObjectInfo** ppResObj);

		//��������� ���������� �� ������� �� GUID
		//���������� ppResObj==NULL ���� ������ �� ������
		HRESULT GetLibraryObject(BSTR pszUID, ILibObjectInfo** ppResObj);

		//��������� ���������� �� ������� �� idObject
		//���������� ppResObj==NULL ���� ������ �� ������
		HRESULT GetLibraryObject(long lPK, ILibObjectInfo** ppResObj);

		//��������� ��������� �������
		//nIdObject - ������������� ������� ��� ��������� ����������
		HRESULT GetObjectParameters(int nIdObject, MStudioData::IParamsOwner** ppResParams);	

		//��������� ��������� ������, � ����� ���������� ������� � ����������� ��� IElement
		//pInfo - �������� ������ �������������� ��������
		//ppResElement - �������������� �������
		HRESULT DownloadObjectAsElement(ILibObjectInfo* pInfo, MStudioData::IElement** ppResElement);	

		//����� �������� ����
		//DownloadElementsByObjectsIds
		//DownloadElementsByFilter

		//----------------�����-----------------------------------------------------------------------------------------		
		//��������� ���� ����� �� ��������������
		//nRelTypeId - ������������� ���� �����
		//ppResRelType - ��� ����� ��� NULL, ���� ����� �� �������
		HRESULT GetObjectRelationTypeById(int nRelTypeId, IObjectRelationType** ppResRelType);

		//��������� ���� ����� �� �����
		//strRelTypeName - ��� ���� �����
		//ppResRelType - ��� ����� ��� NULL, ���� ����� �� �������
		HRESULT GetObjectRelationTypeByName(BSTR pszRelTypeName, IObjectRelationType** ppResRelType);

		//��������� ������ ����� ������ (���� �� �����������)
		HRESULT GetObjectRelationTypes(IObjectRelationTypesArr** ppResArrRelations);

		//���������� ���� ����� (� ��������� �� ������� ������������)
		//pRelTypeTemplate - ��������� ������������������ (����� Id) ������ - ������ 
		// (����� ������� ������� CreateObjectRelationType)
		//pszIcon - ��� ������ � ��, ��� �� �������������
		//uIconResId16 - ������������� �������� ���� ����� 16x16 �� ��������
		//uIconResId32 - ������������� �������� ���� ����� 32x32 �� ��������
		//hresInst - ���������� ������ � ���������� ����������
		//���������� Id ����� ��� ������������ �����, � ����� ���������� Id � ���������� ������
		int AddObjectRelationType(IObjectRelationType *pRelTypeTemplate, BSTR pszIcon=NULL,
			UINT uIconResId16=0, UINT uIconResId32=0, HINSTANCE hresInst=NULL);

		//����������/�������� ���� �����
		//relType - ��������� ������������������ ������ ���� �����, ���� ���������� ������ ���������
		// ��� ���� �����, �� ������ ��� ����� ����� ������ �� ����� �������
		//pszIcon - ��� ������ � ��, ��� �� �������������
		//uIconResId16 - ������������� �������� ���� ����� 16x16 �� ��������
		//uIconResId32 - ������������� �������� ���� ����� 32x32 �� ��������
		//hresInst - ���������� ������ � ���������� ����������
		//���������� Id ����� ��� 0 � ������ ������ ��� �������� �����
		int UpdateObjectRelationType(IObjectRelationType *pRelType, BSTR pszIcon=NULL,
			UINT uIconResId16=0, UINT uIconResId32=0, HINSTANCE hresInst=NULL);

		//���������� ����� � �� (���� ����� ��� ����, �� ������ �� ����������)
		//nObject1Id - Id ������� ������������ �������
		//nObject2Id - Id ������� ������������ �������
		//nRelationTypeId - ������������� ���� �����
		//���������� false � ������ ������
		bool LinkObjects(int nObject1Id, int nObject2Id, int nRelationTypeId);

		//���������� ����� � �� (���� ����� ��� ����, �� ������ �� ����������)
		//nObject1Id - Id ������� ������������ �������
		//object2UId - UID ������� ������������ �������
		//nRelationTypeId - ������������� ���� �����
		//���������� false � ������ ������
		bool LinkObjects(int nObject1Id, const GUID& object2UId, int nRelationTypeId);

		//��������� ��������� ��������
		//arrObjectsIds - ������ ��������, ����� � �������� ���������� ��������
		//nArrObjectsIdsCount - ���������� �������� � arrObjectsIds
		//nRelationTypeId - ������������� ���������������� ���� ����� ��������
		//ppArrResult - �������������� ����� ��� ������� ������� �� arrObjectsIds
		//	KeyObject - ������ �������� �������� ������ �� arrObjectsIds, ���� ���� ����� � ��� ��������
		//bSelByLeftObject - arrObjectsIds ��������� �� ������� �� ������ ������� (1) � ������������
		//	��������� ������� �� ������� �������, ����� ��������� �������� ������� ������� ������� (2)
		//bIncludeFullHierarchy - ����� �������� ����� ����� ��� ���� ���������� �������� (����� arrObjectsIds)
		HRESULT GetLinkedObjects(int* arrObjectsIds, int nArrObjectsIdsCount,
			int nRelationTypeId,
			ILinkedObjectsRecArr **ppArrResult,
			bool bSelByLeftObject=true, bool bIncludeFullHierarchy=false);

		//��������� ��������� �������� (������ � ���������� CLibObjectInfo)
		//arrObjectsIds - ������ ��������, ����� � �������� ���������� ��������
		//nArrObjectsIdsCount - ���������� �������� � arrObjectsIds
		//nRelationTypeId - ������������� ���������������� ���� ����� ��������
		//ppArrResult - �������������� ����� ��� ������� ������� �� arrObjectsIds
		//	KeyObject - ������ �������� �������� ������ �� arrObjectsIds, ���� ���� ����� � ��� ��������
		//bSelByLeftObject - arrObjectsIds ��������� �� ������� �� ������ ������� (1) � ������������
		//	��������� ������� �� ������� �������, ����� ��������� �������� ������� ������� ������� (2)
		//bIncludeFullHierarchy - ����� �������� ����� ����� ��� ���� ���������� �������� (����� arrObjectsIds)
		HRESULT GetLinkedObjects(int* arrObjectsIds, int nArrObjectsIdsCount,
			int nRelationTypeId,
			ILinkedObjectsInfoRecArr **ppArrResult,
			bool bSelByLeftObject=true, bool bIncludeFullHierarchy=false);

		//�������� �����(������) ������� �� ��
		//nObjectId - Id ������� � �������� ������� ����� (����� ���� ��� �����, ��� � ������)
		//pRelTypeTemplate - ������ ����������� �����
		//nObject2 - Id ������� � ������� ������� ����� (��� 0, ��� �������� ���� ������ ���������� ���� � ������ ��������)
		//���������� false � ������ ������
		bool RemoveObjectLinks(int nObjectId, const IObjectRelationType *pRelTypeTemplate, int nObject2=0);

		//GetObjectsLinksInfo (����)

		//--------------------------------------------------------------------------------------------------------------

		//��������� ������ �������� � ������������ � ����������� (CElements)
		//arrObjectsIds[nObjectsCount] - ������ ID ����������� �������� �������� (���������� ��������)
		//��� �������� ��������� �������� ����������� � �������� ������� pResParentElement
		//pResultObjects - �������������� ������ ���� ��������� �������� (������� ����������) CLibObject+������ �� CElement
		// ���������� ������� ��� ����������� pResParentElement, �.�. ��������� �� ����
		void DownloadElementsByObjectsIds(int* arrObjectsIds, int nObjectsCount,
			MStudioData::IElement **pResParentElement,
			IElementDataArr **pResultObjects);

		//��������� ������ �������� � ������������ � ����������� (CElements) �� �������
		//pszFilter - ������ ��� ������� �������� �������� (������ ���� ����������� ���������� ������ �������)
		//��� �������� ��������� �������� ����������� � �������� ������� pResParentElement
		//pResultObjects - �������������� ������ ���� ��������� �������� (������� ����������) CLibObject+������ �� CElement
		// ���������� ������� ��� ����������� pResParentElement, �.�. ��������� �� ����
		void DownloadElementsByFilter(LPCTSTR pszFilter,
			MStudioData::IElement **pResParentElement,
			IElementDataArr **pResultObjects);

		//���������� �� �� (���� ���� �����������)
		HRESULT Disconnect();

		//--------------------------------------------------------------------------------------------------------------

		//�������� ������������� ��������� �� ���������� �����, ���� ���������
		//pszName - ��������� ��� ��� ��������� ���������
		//bSysName - ��� ��������� ������� � pszName
		//���������� 0 � ������ ������ ��� ���� ��������� �� �������, ����� ������������� ���������
		int GetObjectCategoryId(LPCTSTR pszName, bool bSysName);

		//��������� ������ ��������� ��������
		//pResCatList - ��������� ��� ������ IElement, (� ModelUID �������� id ���������)
		HRESULT GetObjectCategories(MStudioData::IElement **pResCatList);

		//��������� �������������� ��������� ��������� ��� �������������� �������� "����������� ������"
		//��� ��������� SYS_CAT_STRUCTURE_DATA ("structure_data")
		//������ ��������� �������� �� ��������� �� ���� ��
		//nEnum - ��������������� ��� ������� ����
		int GetStandardCategoryId(int nEnum=0);

		//���������� ��������� ������� (� ��������� �� ������� ������������)
		//���������� ������������� ����� ��������� ��������� ��������
		//pszSysName - ��������� ��� ���������
		//pszLabel - ������������ ��� ��������� (���������)
		//pszIconName - ��� ������, ������� ����� ������� � ������ �������� hBmpSmall � hBmpLarge
		//hBmpSmall - ������ ��������� 16�16
		//hBmpLarge - ������ ��������� 32�32
		//� ������ ���� ��������� ���������� - ����� ��������� � �������������
		int AddObjectCategory(LPCTSTR pszSysName, LPCTSTR pszLabel,	LPCTSTR pszIconName=NULL,
			HBITMAP hBmpSmall=NULL, HBITMAP hBmpLarge=NULL);

		//--------------------------------------------------------------------------------------------------------------
		//���������� ������ �� ���������� �� 1000
		int GetVersion();

		//��������� ����������� � ������������ �������������� ������ ��
		//�������� ������ ���������� ��� �����������
		//����� ������ - ������ ��*1000
		HRESULT GetDatabaseSupportedVersion(int& nCurrentVersion, int& nLastVersion);

		//���������� ������ 3D ���������� �� 1000, ���� 0 ���� ��� ������ (�� �� 3D)
		int GetVersion3D();

		//���������� ������� 3D, ���� 0 ���� ��� ������ (�� �� 3D)
		int GetVersionRevision3D();
		//--------------------------------------------------------------------------------------------------------------
		//�������� ����� � �� (���� ����� ����� ��� ���� - ������� id ������������)
		//ptBase - ������� ����� ����� (� ��������� ����������� � ��, ��� �� 0 � XPG)
		//pMeshData, nMeshSize - ������ ���� ������� nShapeSize, ���������� ����� � ������� msm
		//pszXpg - ������ � XPG �������� (����� ���� NULL)
		//���������� idMesh ����� �� ������� Mesh ��� ����������
		int AddMesh(
			void* pMesh,
			ULONG nMeshSize,
			ULONG nMeshHash,
			LPCTSTR pXPG,			
			const CSVECTORD3 &ptBase,
			const CSVECTORD3 &ptSize);

		//���������� true ���� ������� ����� ���������� ����������� idMesh � ������� ����������� nLevel
		bool HasLowDtailedMeshData(int idMesh, int nLevel);

		//���������/��������� ����� ������ ����������� � �������� ����� � idMesh
		//���������� true � ������ ��������� ����������
		//nLevel - LOW_DEATAILED_MESH_SIMPLIFIED � ������ ���� �����������
		bool AddLowDetailedMeshData(int idMesh, int nLevel, void* pMeshData, ULONG nMeshSize);

		//��������� ������ �� ����� � �� ���, Project
		//nIdObject - id ������ � ������� ������������� �������
		//nIdMesh - id ����� �������
		//ptPosition - ��������� � ������������ ������� �����
		//ptExtMin, ptExtMax - �������� ������������������� ���� (�������� �������� ��������)
		//vtXAxis, vtYAxis, vtZAxis - ����������� � ���������� �� ������� �����	
		//pARGBColor - ���� �����, �� ������� ����� ����������� � ��������� ����
		//���������� idGraphics > 0 � ������ ��������� ���������� � ��
		int AddShape(int nIdObject, int nIdMesh,
			const CSPOINTD &ptPosition,
			const CSPOINTD &ptExtMin, const CSPOINTD &ptExtMax,
			const CSVECTORD3& vtXAxis, const CSVECTORD3& vtYAxis, const CSVECTORD3& vtZAxis,
			int *pARGBColor=NULL);
		//--------------------------------------------------------------------------------------------------------------

		//��������� ���������� � ������ ��������
		//����������� ���������� � ���, ����� ����� ����� ������������
		// � �� �� ���������� (��. LinkInfoRec)
		//arrObjectsIds - ������ �������� �������� ��� ���������� ����������
		//nArrObjectsIdsCount - ���������� �������� � arrObjectsIds
		//ppArrResult - ������ � ����������� LinkInfoRec[]
		//	KeyObject - ������ �������� �������� �������� �� arrObjectsIds
		//  ������ ������������ �� KeyObject
		//bAnalyzeFullHierarchy - ���������� ���� ������ ���� ���������� �������� arrObjectsIds
		HRESULT GetObjectsLinksInfo(int* arrObjectsIds, int nArrObjectsIdsCount,
			IObjectsLinkInfoRecArr **ppArrResult, bool bAnalyzeFullHierarchy=false);

		//��������� ���������� �� �������� �� ������ ��������������� arrObjectsIds[nObjectsCount]
		//ppResObjArr - �������������� ������ ���������� �� ��������, ������� ��������� ��������������
		HRESULT GetLibraryObjects(int* arrObjectsIds, int nObjectsCount, ILibObjectInfoArr** ppResObjArr);

		//��������� ���������� �� �������� �� ������ ���������� ��������������� arrObjectsUids[nObjectsCount]
		//ppResObjArr - �������������� ������ ���������� �� ��������, ������� ��������� ��������������
		HRESULT GetLibraryObjects(GUID* arrObjectsUids, int nObjectsCount, ILibObjectInfoArr** ppResObjArr);

		//��������� ���������� �� �������� �� �������
		//pszFilter - ������ ��� ������� �������� �������� (������ ���� ����������� ���������� ������ �������)
		//ppResObjArr - �������������� ������ ���������� �� �������� �� �������
		HRESULT GetLibraryObjects(LPCTSTR pszFilter, ILibObjectInfoArr** ppResObjArr);

		//������� ������ �� ����������
		//nObjectId - ������������� �������
		//������ � ������ �������� ����� ������� ��� ���������� �������,
		// � ����� ��� �������� ��������� �������, ������ �� ������� � �����
		HRESULT DeleteObject(int nObjectId);

		//������� ������� �� ���������� �� ������ ��������������� arrObjectsIds[nObjectsCount]
		//������ � ������� ��������� ����� ������� ��� ���������� �������,
		// � ����� ��� �������� ��������� �������, ������ �� ������� � �����
		HRESULT DeleteObjects(int* arrObjectsIds, int nObjectsCount);

		//������� ������� �� ����������
		//arrObjectsInfo - ������ � ����������� �� �������� ��� ��������
		//������ � ������� ��������� ����� ������� ��� ���������� �������,
		// � ����� ��� �������� ��������� �������, ������ �� ������� � �����
		HRESULT DeleteObjects(ILibObjectInfoArr* arrObjectsInfo);

		//--------------------------------------------------------------------------------------------------------------

		//��������� ��������� �� � ����������� ������������� ���������� � ��������� ��
		//pParamDefs - ����������� ���������� ��� �����
		//bTransimtOwnership - ����, ��, �� ��� �������� �� ����� ����������� ������,
		// ���������� pParamDefs
		HRESULT BindWithParamDefs(MStudioData::IParamDefs *pParamDefs, bool bTransimtOwnership);

		//-------------------------------------------------------------
		//��������� ��������� �� � ����������� ������������� ���������� � ��������� ��
		//pParamDefs - ����������� ���������� ��� �����
		//bTransimtOwnership - ����, ��, �� ��� �������� �� ����� ����������� ������,
		// ���������� pParamDefs
		//HRESULT GetLandSurface(MStudioData::IParamDefs *pParamDefs, bool bTransimtOwnership);
		//����������� DBL_MAX � -DBL_MAX, ���� ���������� �������� ����������� �� ����������� ���
		HRESULT DownloadLandSurface(int nLandId,  IDBDownloadedLand** ppLandsResData,
			int nCountAABB = 0, CAABBI* pExtents = NULL);

		//��������� ������������ ��������� ��� �� ��
		void LoadProjectSettings();
	};

	//������ ���������� �� ��������
	__interface ILibObjectInfoArr: public IUnknown
	{
		//��������� ���������� ���������
		int GetCount();

		//��������� �������������� ������� �� �� ������� � �������
		int GetObjectIdByIndex(int nIdx);

		//��������� ������� ������� �� �� ������� � �������
		GUID GetObjectUIDByIndex(int nIdx);

		//��������� ����� ������� �� ������� � �������
		LPCTSTR GetObjectNameByIndex(int nIdx);

		//��������� ����� �������������� ��������� ������� �� ������� � �������
		int GetObjectCetegoryIdByIndex(int nIdx);

		//��������� ���������� �� ������� �� �� �������
		HRESULT GetItemAt(int nIdx, ILibObjectInfo** pResInfo);

		//����� �������� �� �������������� ������� nObjectId
		//� ������ ������� pResInfo ������� ����������
		HRESULT FindItemByObjectId(int nObjectId, ILibObjectInfo** pResInfo);
	};

	//�������������� ��������� ���������� ��� ���������� � ���� �� ���
	//� �������� ������������ ������� ��, �� ������� ������ ��� ����������� ���������� ���������
	__interface ILibObjectParamsMap: public IUnknown
	{
		//������� �������� ���������� � ���������
		void SetValues(long idObject, MStudioData::IParamsOwner* pParamsOwner, bool bUseProtection);
		//���������� �������� ���������� � ��
		void Commit();
		//�������� �� �� ����� ���� ���������� �� ����������
		void CacheAllParameters();
		//�������� ���� ����������� ����������
		void ResetValues();
	};

	//��������� ���������� �� ������� ��, ��������� � ������ ��������� ���������� CElement
	//������� �� ������� ����������� �������-��������� � CElement ���������� (resParentElement) ������� DownloadElementsBy
	__interface IElementData: public IUnknown
	{
		//��������� �������������� ������� ��
		int GetObjectId();

		//��������� ���������� �� ������� ��
		void GetObjectInfo(ILibObjectInfo** pResInfo);

		//��������� ������ �� ����� �������� ��������� CElement, ��������� � ���� �������� ��		
		void GetElement(MStudioData::IElement** ppResElementRef);
	};

	//��������� ��������������� ������� ������� DownloadElementsBy
	//������� �� ������� ����������� CElement ���������� (resParentElement) ������� DownloadElementsBy
	__interface IElementDataArr: public IUnknown
	{
		//��������� ���������� ���������
		int GetCount();

		//��������� �������� �� �������
		HRESULT GetItemAt(int nIdx, IElementData** pResEl);

		//����� �������� �� �������������� ������� nObjectId
		//� ������ ������� pResEl ������� ����������
		HRESULT FindItemByObjectId(int nObjectId, IElementData** pResEl);

		//����� �������� �� ��������� �� ����� � ��������
		//� ������ ������� pResEl ������� ����������
		HRESULT FindItemByElement(MStudioData::IElement* pElement, IElementData** pResEl);
	};

	//��� ����� ����� ��������� (������� [ObjectsRelationTypes])
	__interface IObjectRelationType: public IUnknown
	{
		int GetId() const;

		int GetIdIcon() const;
		void SetIdIcon(int nVal);

		HRESULT GetName(BSTR* pStrRes);
		void SetName(LPCTSTR pStrName);

		HRESULT GetCaption(BSTR* pStrRes);
		void SetCaption(LPCTSTR pStrCaption);

		//��������� ������� ������� ��� �������� �������. 
		//	false - soft pointer (��� �������� ������� ���������� ������� ������ �������). 
		//	true - hard pointer (��� �������� ������� ������� ������ ���������)
		bool IsHardLink1() const;
		void SetHardLink1(bool bHard);

		//��������� ������� ������� ��� �������� �������. 
		//	false - soft pointer (��� �������� ������� ���������� ������� ������ �������).
		//	true - hard pointer (��� �������� ������� ������� ������ ���������)
		bool IsHardLink2() const;
		void SetHardLink2(bool bHard);
	};
	
#pragma pack(push, 1)
	//������ ������� ��������� ��������
	struct LinkedObjectsRec
	{
		//�������� ������ (�� ������� ��� ������)
		int nKeyObjectId;
		//��������� ������
		int nLinkedObjectId;
	};

	//������ ������� ���������� �� �������� ������
	struct LinkInfoRec
	{
		//�������� ������ (�� ������� ��� ������)
		int nKeyObjectId;
		//��� �����
		int nObjectRelationType;
		//���������� ������, ��� �������� ������ �����
		int nLinksCountLeft;
		//���������� ������, ��� �������� ������ ������
		int nLinksCountRight;
	};
#pragma pack(pop)

	//��������� ������� � ����������� � ��������� ��������
	//������������ ������ � �������� ��������� ������� "C"
	__interface ILinkedObjectsRecArr: public IUnknown
	{
		//���������� ���������� ������� � �������
		int GetLength();

		//���������� ������ ������� ��������� �������� ������ GetLength()
		//��� ������ ������������� ������� �� nKeyObjectId, ����� �� nLinkedObjectId
		LinkedObjectsRec* GetRecords();
	};

	//��������� ���������� ��������� ���������� � ��������� ��������
	//��������� ������������ �� ��������� ������� (�� �������� ��� ������)
	__interface ILinkedObjectsInfoRecArr: public IUnknown
	{
		//���������� ���������� �������� ��������
		int GetKeyObjectsCount();

		//���������� ������������� �� ��������� ������� �� �������
		//nKeyObjectIdx - ������ ��������� ������� [< GetKeyObjectsCount()]
		//��������� ������������ �� nKeyObjectId
		int GetKeyObjectIdAt(int nKeyObjectIdx);

		//���������� ������ ��������� ������� �� ��� �������������� � ��
		//nKeyObjectId - ������������� �� ��������� �������
		//���������� -1 � ������, ���� ���������� �� �������������� ������� �� �������
		int GetKeyObjectIndexById(int nKeyObjectId);

		//���������� ���������� ��������� � �������� ��������
		//�� ������� ��������� ������� 
		//nKeyObjectIdx - ������ ��������� ������� [< GetKeyObjectsCount()]
		int GetLinkedObjectsCountAt(int nKeyObjectIdx);

		//���������� ������������� �� �������, ���������� � ��������
		//nKeyObjectIdx - ������ ��������� ������� [0 <= nKeyObjectIdx < GetKeyObjectsCount()]
		//nLinkedObjectIdx - ������ ���������� �������
		//  [0 <= nLinkedObjectIdx < GetLinkedObjectsCountAt(nKeyObjectIdx)]
		int GetLinkedObjectAt(int nKeyObjectIdx, int nLinkedObjectIdx);

		//���������� ���������� �� ������� ��, ���������� � ��������
		//nKeyObjectIdx - ������ ��������� ������� [0 <= nKeyObjectIdx < GetKeyObjectsCount()]
		//nLinkedObjectIdx - ������ ���������� �������
		//  [0 <= nLinkedObjectIdx < GetLinkedObjectsCountAt(nKeyObjectIdx)]
		//ppResObjectInfo - ��������� ����� ������� � ����������� � ��������� �������
		HRESULT GetLinkedObjectAt(int nKeyObjectIdx, int nLinkedObjectIdx,
			ILibObjectInfo** ppResObjectInfo);
	};	
	
	//��������� ������� ������� � ����� ������
	//������ ������������� �� �������������� ���� �����
	__interface IObjectRelationTypesArr: public IUnknown
	{
		//���������� ���������� ������� � �������
		int GetLength();

		//���������� ������������� ���� ����� �� �� �������
		//nIdx - ������ ������
		int GetRelationTypeIdAt(int nIdx);

		//���������� ��� ���� ����� �� �� �������
		//nIdx - ������ ������
		LPCTSTR GetRelationTypeNameAt(int nIdx);

		//���������� ��������� ���� ����� �� �� �������
		//nIdx - ������ ������
		LPCTSTR GetRelationTypeCaptionAt(int nIdx);

		//���������� ��� ��� ����� �� �� �������
		//nIdx - ������ ������
		//ppResRelType - ��������� �� �������� ����� ������� ��������� ��
		//  ��������� ����� ������� ���� ������
		HRESULT GetRelationTypeAt(int nIdx, IObjectRelationType** ppResRelType);
	};
	
	//��������� ������� LinkInfoRec
	//������������ ������ � �������� ��������� ������� "C"
	__interface IObjectsLinkInfoRecArr: public IUnknown
	{
		//���������� ���������� ������� � �������
		int GetLength();

		//���������� ������ ������� ���������� � ������ �������
		//��. GetObjectsLinksInfo
		//��� ������ ������������� ������� �� nKeyObjectId
		LinkInfoRec* GetRecords();
	};
////////////////////////////////////////////////////////////////////////////////////////////////////
#define MSTUDIO_DB_API_CUR_VER_MAJOR 1
#define MSTUDIO_DB_API_CUR_VER_MINOR 15

	__interface IFactoryInterface
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_DB_API_CUR_VER_MAJOR � MSTUDIO_DB_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//�������� ������ ������� ��� ������ � ��
		HRESULT CreateDataBase(IDataBase** pNewDb);

		//��������� ����������� ������� �� ����������� ��������� ModelStudio
		//���������� � ����������� ������������� ����������
		//(��� �������� ��� ���������� �� ������� "����������� ����������� ���������")
		HRESULT GetStandardComponentsDataBase(MStudioDB::IDataBase** pStandardDb);

		//�������� ������ ���������� ������� ���� �����
		HRESULT CreateObjectRelationType(IObjectRelationType** pNewRelTypeObject);

		//��. �������� ����
		bool SetupModelStudioOptions(HWND hWndParent);

		//����� ������������ ������� �������� ModelStudio
		//hWndParent - ���������� ������������� ���� (��� NULL)
		//pStandardDb - ��, �������� ������������ ��� �� ����������� ��������� ���
		// ������ � ������������� ���������� ��� NULL
		//���������� ��, ���� ������������ ����� OK
		bool SetupModelStudioParams(HWND hWndParent, IDataBase* pStandardDb);
	};

#define MODEL_STUDIO_DB_MODULE_NAME L"mstudioDB.dll"
#define MODEL_STUDIO_DB_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_DB_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_DB_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
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
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
						MODEL_STUDIO_DB_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_DB_API_CUR_VER_MAJOR, MSTUDIO_DB_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};

	//������� ���������� � �������� � ������������� ������������� ���� "�����"
	__interface IDBDownloadedLand: public IUnknown
	{
		//��������� ���������� ������
		int GetCountVertices();
		//��������� ���������� ������������� ������������ �����������
		int GetCountTriangles();

		//��������� ������
		 CSPOINTD* GetVertices();

		//��������� �������������
		 CLibDBSurfTriangle* GetTriangles();

	};

}