#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"

//���������� ��� ������ � ��������������� �������������
namespace MStudioPublish
{
	//��������� ������ �������� ����������
	__interface IPublicationSettings: IUnknown
	{
		//��������� ��������� � ������
		void Save(MStudioData::IElement* pDestPublicationParams) const;
		//��������� ��������� �� ������
		void Load(const MStudioData::IElement* pPublicationParams);

		//���������� � ���� (���� �� ������ ���� - ������������ ������� ��������)
		void SaveToXMLFile(BSTR strFileName) const;
		//�������� �� ����� (���� �� ������ ���� - ������������ ���� �� �������� ��������)
		bool LoadFromXMLFile(BSTR strFileName);

		//���������� � ��������
		HRESULT SaveToDWG(AcDbDatabase *pDb) const;
		//�������� �� ��������� (����� false ���� ������ �� �������)
		bool LoadFromDWG(AcDbDatabase *pDb);
	};

	//��������� ������� ����������
	__interface IPublisher: IUnknown
	{
		//��������� ����� ����� ������������ (������ ����� �������� ������ ����� �����������)
		//������ ������ - �������� �� DWG � ������� ������� (������ �� ������������ ��� �������� �� XML)
		HRESULT GetConfigFileName(BSTR* pFilePath) const;
		//��������� ����� ����� ������������ (������ ����� �������� ������ ����� �����������)
		//������ ������ - �������� �� DWG � ������� ������� (������ �� ������������ ��� �������� �� XML)
		HRESULT SetConfigFileName(BSTR pFilePath);

		//����� ������ �� ��������� ������
		bool IsSilentMode() const;
		//����� ������ �� ��������� ������ (������ ���� ������ ������� SetPublicationSettingsPath())
		void SetSilentMode(bool bSilent);

		//����� �� ��������� DWG �� ����� �������
		bool IsCreateRepresentDWG() const;
		//����� �� ��������� PDF �� ����� �������
		bool IsCreateRepresentPDF() const;
		//����� ��������� ����� ���� ����?
		CString GetRepresentDWGCat() const;
		//����� ��������� ����� ���� ����?
		CString GetRepresentPDFCat() const;

		//��������� ������������� ���� ��� ���� ���������
		void SetProgressParentWnd(HWND hWnd);

		//--��������� ������ �������� ������ � ������ ������� ���������� (� BeforePublishSpace)--

		//��������� �� ���������� (� ������� ������ ����������)
		//������ ������� ������ �� ����� ����������
		HRESULT GetDestinationDB(MStudioDB::IDataBase **ppResDb);

		//��������� ����� �� ���������� ��� ������
		HRESULT GetDestinationDBName(BSTR* pResDB);

		//��������� ������� �������� ����������
		//������ ������� ������ �� ����� ����������
		HRESULT GetSettings(IPublicationSettings **pResSettings);

		//���������� � ����������
		//����� ����� �������� ��� ���������� (��� ���������� �������� ����������)
		int GetTotalObjectsCount() const;
		//�������� ���������� ����������� � �� ��������
		int GetAddedObjectsCount() const; 
		//�������� ���������� ���������� �������� �� (���� �������� ����� � ���������)
		int GetUpdatedObjectsCount() const;
		//����� �� ������������ ������
		bool IsAborted();

		//��������� ����� ���������� ���� ����� ����� ���������
		//����� �������� ���������, �.�. � ������ ������ ��������� ������ �� ��� �� ������
		void AddObjectsLinkDelayed(int nObject1Id, const GUID &object2UId, int nRelationTypeId);

		//��������� ����� ���������� ���� ����� ����� ���������
		//����� �������� ���������, �.�. � ������ ������ ��������� ������ �� ��� �� ������
		void AddObjectsLinkDelayed(int nObject1Id, int nObject2Id, int nRelationTypeId);

		//��������� ����� ���������� ���� ����� ����� ���������
		//����� �������� ���������, �.�. � ������ ������ ��������� ������ �� ��� �� ������
		void AddObjectsLinkDelayed(const GUID &object1UId, const GUID &object2UId, int nRelationTypeId);

		//��������� � ������� ������ �� �������� ���� ������ ������� ���� ��� �������
		void RemoveObjectLinksDelayed(int nObject1Id, int nRelationTypeId);

		//��������� �������� �������� � ��
		//������ ����� ��������� �������� �� ������� BeforePublishSpace, �.�. � ����� �������
		// ��� ����� �������� ����������
		//idEntityToPublish - ������������� �������� ��� ����������		
		//mtTransformation - ������� ������������� �������� (�������������
		//	���������� �������� ������������� ��������� GetPublicationTransformation())
		//pParentBlockRef - �������� ������ ������������� �����
		// (��� ��������� ������ ������ ��� NULL)
		//���������� �������� ������� ��� ����������� ��������
		// (IsEntityForPublish, GetSmartObject, BeforeAddOrApplyObject, AfterAddOrApplyObject,
		//  PostProceesDumping, AfterDumpEntity)
		bool PublishEntity(const AcDbObjectId& idEntityToPublish,
			const AcGeMatrix3d &mtTransformation, const AcDbBlockReference *pParentBlockRef, bool b3DModelEntity = true, bool bPublishParams2d=false);
		//��������� ������ �� ������� ������������� ���������� (������ ������� ��������� � 
		//	PublishEntity �� ����� ���������� ��������� ������� ������������)
		AcGeMatrix3d &GetPublicationTransformation();

		//��������� �������� ����� ������
		//entities - c������� ��� ����������
		//mtTransformation - ������� ������������� �������� (�������������
		//	���������� �������� ������������� ��������� GetPublicationTransformation())
		//pParentBlockRef - �������� ������ ������������� �����
		bool PublishEntitiesOneMesh(const AcDbObjectIdArray& entities, const AcGeMatrix3d &mtTransformation, 
			const AcDbBlockReference *pParentBlockRef, bool b3DModelEntity = true, bool bPublish2dParams = false);
		
		//���������� �����
		void AddObjectFileDelayed(int idObject, LPCTSTR szFileName, LPCTSTR szCat, LPCTSTR pszPath, bool bDeleteSrcAfterIns = false);
		void DetachFileDelayed(int idObject, int nIdFile);
	};

	//��������� ��� ��������, ������� ����� ���������������� � �������� ���������
	//�� ������� ����������. ������������ ��� ���������� �������������� ������ � ������� � ����������� ��������� � �.�.
	//� ������ CEmptyPublishingReactor (����� �����) ��������� ���������� � ���������� �� ���������
	__interface ICadLibPublishingReactor
	{
		//���������� � ����� ������ - ��������������� ����� ��������� ���������� (��� ������������� ��������)
		//bCancel - ���� ���������� � true, �� ������� ���������� ����� ������, ����������� ������� �� ����� �������
		void BeforePublishingStarted(IPublisher *pPublisher, bool &bCancel);

		//���������� ����� ���������� ���� �������: ���� �������� ��������� �������������� ��
		virtual void AfterPublishingEntities(MStudioPublish::IPublisher *pPublisher);

		//���������� ����� ���������� ���������� (��� � ������ ������ ��� ������) (��� ������������ ��������)
		//bCanceled - true, ���� ������� ���������� ��� ������ ������������� ��� ��������
		//bException - true, ���� ������� ���������� ������� ��-�� ���������� ����������
		void AfterPublicationFinished(IPublisher *pPublisher, bool bCanceled, bool bException);

		//���������� ����� ������� ���������� ������� ����� (������� ���� ��� ��� ModelSpace)		
		//pPublisher - ����������
		//idBlockToPublish - ����, ������� ����� �����������
		//arrSelection - ������ ������� ������������, ������� ����� �����������
		// (�� �������� ������� ������)
		//���� ����� ����� false, �� ���������� ������������ ����������� �� �����, �� ������ �����
		// ����� ������ � ����������� ���������.
		bool BeforePublishSpace(IPublisher *pPublisher, const AcDbObjectId& idBlockToPublish,
			AcDbObjectIdArray& arrSelection);

		//���������� ����� ��������� �������� (� �.�. �� �������) � ����� ������������ � ��
		void AfterAcquireSettings(IPublisher *pPublisher);

		//���������� ����� ������������ � ��
		//����� ������ ������� false �� ���������
		// ���� ������������ � �� � ������� true
		bool CustomConnectToDestDB(IPublisher *pPublisher); //return false;

		//���������� ����� ������� ����������� � �� ����������
		void AfterDbConnected(IPublisher *pPublisher);

		//����� �� ����������� �������� �������� pEnt ��� ������ ���������� �
		//pEnt - �������� ��� ������ ��������
		//����� ������ ������� true �� ���������
		bool IsEntityForPublish(IPublisher *pPublisher, const AcDbBlockReference *pParentBlockRef,
			AcDbEntity* pEnt); //return true;

		//����� ������ ������� true, ���� �������� pEnt �������� ����� �������� (�� ��������)
		//��� ����� �������� �� ���������� ���������� ���������� - ����������� ��������� resParams, �����������
		//���� �� �������
		//pEnt - �������� ��� ������ ��������
		//mtTransform - ������� ������������� �� ������� ���������� ���������������� ������ ��� ���������� � ���
		//pResParams - ������ ����������, ���� ���������� ��������� ����� ������
		bool GetSmartObject(IPublisher *pPublisher, AcDbObject *pEnt, const AcGeMatrix3d& mtTransform,
			MStudioData::IElement *pResParams); //return false;

		//������ ����� ���������� ��������������� ����� �����������/����������� ������� � ��
		//pEnt - �������� ��� ������ ��������
		//pObjectParameters - ������ ���������� ������� ��� ������ � �� (������/������)
		//����� ������ ������� true �� ���������
		//���� ����� ���������� false, �� ������ �� ����� �����������/�������
		bool BeforeAddOrApplyObject(IPublisher *pPublisher, AcDbObject* pEnt,
			MStudioData::IElement *pObjectParameters); //return true;

		//������ ����� ���������� ����� ����� ����������/���������� ������� � ��, �� �� ����������
		// �������
		//pLibObject - ����� ����������/����������� ������� � ��. �� ����� ���� ������
		// ����� ���� ������ � ����� ������ ����������, �.�. �������� ������� � �� - ����������
		// �������� �������, ���� ������ �����, ����� � ��� ����� ���������� ������ ��������� �����
		// AddObjectsLinkDelayed
		//bNewObject - true, ���� ������ ���/����� �������� � ��, ����� ������ ��� �������
		//pEnt - �������� ��� ������ ��������
		//pObjectParameters - ������ ���������� ������� ��� ������ � �� (������)
		void AfterAddOrApplyObject(IPublisher *pPublisher, MStudioDB::ILibObjectInfo *pLibObject,
			bool bNewObject, AcDbObject* pEnt, MStudioData::IElement *pObjectParameters);

		//���������� ����� ���������� ������� � ��������� ����� ����������� ������� � ��
		//pLibObject - ����� ����������/����������� ������� � ��. �� ����� ���� ������
		// ����� ���� ������ � ����� ������ ����������, �.�. �������� ������� � �� - ����������
		// �������� �������, ���� ������ �����, ����� � ��� ����� ���������� ������ ��������� �����
		//arrDumpedSet[nDumpedSetCount] - ������ ��������� � ������
		//pCurTopBlockRef - ���� �������� ������ ��� NULL
		//pParentBlockRef - ���� - �������� ��������� ��� NULL
		//mtSetTransformation - ������� �������������, ������� ����� ��������� ���������
		//pDumper - ��������� �� ������ ������� (���� ��� ����������)
		void AfterDumpEntity(IPublisher *pPublisher, MStudioDB::ILibObjectInfo *pLibObject,
			AcDbEntity** arrDumpedSet, int nDumpedSetCount,
			const AcDbBlockReference *pTopBlockRef,	const AcDbBlockReference *pParentBlockRef,
			AcGeMatrix3d& mtSetTransformation,
			void* pDumper);

		//���������� ����� ��������� �� �������� ���������� ������� ���������
		//�� ��� ������� ����� ���������������� ��� ������
		//��������� �������� ��������� ������������� �������� ���� ����������� ������� ������������� mtTransform
		//(�������� � ������� ������� ��������� ��������� (������� "������� ����������"))
		void OnGetGloablTransformation(IPublisher *pPublisher, AcGeMatrix3d &mtTransform);

		
	};

#define MSTUDIO_PUBLISH_API_CUR_VER_MAJOR 2
#define MSTUDIO_PUBLISH_API_CUR_VER_MINOR 2

	__interface IFactoryInterface
	{
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_CORE_API_CUR_VER_MAJOR � MSTUDIO_CORE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//����������� �������� ���������� (������ �������� ����� ���������� ��� ���� ����������� � ��� ��� CadLib ������)
		void RegisterPublishingReactor(ICadLibPublishingReactor* pReactor);

		//������ ����������� �������� ����������
		void UnregisterPublishingReactor(ICadLibPublishingReactor* pReactor);

		//������ ������ ���������� ����������
		HRESULT CreatePublicationSettings(IPublicationSettings** ppNewObj);
	};

//��������� ���������

//��������� ��� ��������� ������� � �� (������������ ��� ���������� � ��)
#define OBJECT_DEFINE_CATEGORY _T("SYS_OBJECT_CATEGORY")
#define OBJECT_DEFINE_CATEGORY_CAPTION _T("��������� ��")

//��������� ����
#define NODE_POSITION			_T("NODE_POSITION")
#define NODE_POSITION_CAPTION	_T("��������� ����")
#define NODE_DIRECTION			_T("NODE_DIRECTION")
#define NODE_DIRECTION_CAPTION	_T("����������� ����")
#define NODE_NORMAL				_T("NODE_NORMAL")
#define	NODE_NORMAL_CAPTION		_T("������� ����")


//---��������� ���������� (CSPublicationSettings)-------------------------------------------------
//��� ������� ���� AcDbXrecord � ������� ������� ��� �������� ����������
#define PUBL_PARAMS_XOBJECT L"CSOFT_MS_PUBLICATION_PARAMS"

//��� ����� �������� "�� ���������" � �������� ��������
#define PUBL_PARAMS_DEFAULT_FILE L"db_publ_def_settings.xml"

#define PUBL_BD_SERVER_NAME_PARAM L"DB_SERVER_NAME"
#define PUBL_BD_SERVER_NAME_PARAM_TITLE L"������"
#define PUBL_DB_NAME_PARAM L"DB_NAME"
#define PUBL_DB_NAME_PARAM_TITLE L"��� ��"
#define PUBL_DB_USER_PARAM L"DB_USER"
#define PUBL_DB_USER_PARAM_TITLE L"������������ ��"

#define PUBL_ADDITIONAL_PARAMS_PARAM_NAME L"ADDITIONAL_PARAMS"
#define PUBL_ADDITIONAL_PARAM_ELEMENT_NAME L"ADDITIONAL_PARAM"
#define PUBL_ADDITIONAL_PARAMS_PARAM_TITLE L"����������� ���������"
#define PUBL_LAND_MODE_PARAM_NAME L"LAND_PUBLICATION_MODE"
#define PUBL_LAND_MODE_PARAM_TITLE L"����� ����������"
#define PUBL_LAND_LAYERS_PARAM_NAME L"LAND_LAYERS"
#define PUBL_LAND_LAYERS_PARAM_TITLE L"���� �����"
#define PUBL_LAND_SETUP_PLACEHOLDER_NAME L"LAND_SETUP_PLACEHOLDER"
#define PUBL_LAND_SETUP_PLACEHOLDER_TITLE L"���������"
#define PUBL_LAND_LAYERS_MASK_PARAM_NAME L"LAND_LAYERS_MASK"
#define PUBL_LAND_LAYERS_MASK_PARAM_TITLE L"����� ����� ����"

#define PUBL_EXPLORE_XREFS_PARAM L"EXPLORE_XREFS"
#define PUBL_EXPLORE_XREFS_PARAM_TITLE L"���������� ����� XRef"
#define PUBL_LINK_DRAWING_PARAM L"LINK_DRAWING_OBJECTS"
#define PUBL_LINK_DRAWING_PARAM_TITLE L"��������� ����� �������� � ����������"
#define PUBL_PUBLISH_INVISIBLE_PARAM L"PUBLISH_INVISIBLE_OBJECTS"
#define PUBL_PUBLISH_INVISIBLE_PARAM_TITLE L"����������� ��������� �������"
#define PUBL_PUBLISH_LAYOUT_PARAM L"PUBLISH_LAYOUT_OBJECTS"
#define PUBL_PUBLISH_LAYOUT_PARAM_TITLE L"����������� �����"
#define PUBL_TAG_PREFIX_PARAM L"TAG_PREFIX"
#define PUBL_TAG_PREFIX_PARAM_TITLE L"������� ���� ����������"

#define PUBL_SACLE_FACTOR_PARAM L"SACLE_FACTOR"
#define PUBL_SACLE_FACTOR_PARAM_TITLE L"�������"
#define PUBL_SACLE_BASE_PT_PARAM L"SACLE_BASE_PT"
#define PUBL_SACLE_BASE_PT_PARAM_TITLE L"������� ����� ���������������"

#define PUBL_OFFSET_VT_PARAM L"OFFSET_VT"
#define PUBL_OFFSET_VT_PARAM_TITLE L"�������� ������� �����"
#define PUBL_ROTATION_XY_PARAM L"ROTATION_XY"
#define PUBL_ROTATION_XY_PARAM_TITLE L"������� � XY"
#define PUBL_ROTATION_BASE_PT_PARAM L"ROTATION_BASE_PT"
#define PUBL_ROTATION_BASE_PT_PARAM_TITLE L"������� ����� ��������" 

#define PUBL_LAND_SEPERATE_LANDS_BY_LAYERS_PARAM L"SEPERATE_LANDS_BY_LAYERS"
#define PUBL_LAND_SEPERATE_LANDS_BY_LAYERS_PARAM_TITLE L"��������� ������� �� �����"
//------------------------------------------------------------------------------------------------

//�������������� ��������� ���������� (�������)
#define ALL_TABLES_ID -1
#define ALL_TABLES_NAME _T("all_objects")
#define ALL_TABLES_CAPTION _T("[��� �������]")
#define UNDEFINED_TABLE_ID	-2 
#define UNDEFINED_TABLE_NAME _T("undefined_objects")
#define UNDEFINED_TABLE_CAPTION _T("[��������� �������]")





	//������� ����� �������� ����������, ����������� ��������� �� ���������.
	//������������� �� ��� ������ � �������������� ������ ����������� ������.
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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PUBLISH_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PUBLISH_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
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
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
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