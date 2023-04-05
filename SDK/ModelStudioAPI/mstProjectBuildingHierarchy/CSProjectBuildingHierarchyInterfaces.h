#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"
#include "CSProjectBuildingHierarchyConstants.h"
#include "..\mstStructureDataHierarchyBase\constants.h"

namespace MStudioBuildingHierarchy
{
	//��������� ������� ������ � ����������� "������ � ����������"
	//�������� ��������(�������) -> ������(����������) -> ����� -> ���������(����)
	//+ �����(����), ������� ����� ���� ������� � ����������� �����������
	//��������� ����� ������������ �������� ������ ��� ������
	__interface IPBH: public IUnknown
	{
		//������� �� (����� ���� NULL)
		HRESULT GetDB(MStudioDB::IDataBase** pResDb);
		//��������� ������� �� (����� ���� NULL)
		//���� �������� �� ����� ��������, �� ��� ����� �������� �������� � �������� �� ����� ��������
		//��� ������� � ������������� ��������� �������� � ������������ ��������
		HRESULT SetDB(MStudioDB::IDataBase* pDb);

		//--------GUI-------------------------------------------
		//����� ������� �������������� ��������
		int ShowHierarchyEditDialog(HWND hParentWnd, int nRootObjectId);
		//���������� ������ ������(������ ������) ������� �������� 
		int ShowHierarchySelectDialog(HWND hParentWnd, int nRootObjectId);
		int ShowHierarchySiteSelectDialog(HWND hParentWnd, int nRootObjectId);
		int ShowHierarchyBuildingSelectDialog(HWND hParentWnd, int nRootObjectId);
		//����� ������������ ����������� ���� ������������ ���������� ��������
		HRESULT ShowHierarchyFilterDialog(HWND hParentWnd, HierarchyGraphicsFilterCallback callback);
		//�� ��������� � ���, ����� ������ ��� ����� ������� � �����������
		void CollectObjectsFactoryData();

		//legacy
		//���������� �������� ������� ��������, ���������� ������ �������� �� ������� ������
		HRESULT GetRootElement(MStudioData::IElement** pResElement);
		//������ ��� �������� ��� ����� ������� � ���������
		int GetOrCreateObjectToStructLinkType(MStudioDB::IObjectRelationType** pResLinkType);
	};

	//����� ������ ������ � �� CadLib ������.
	//!�������� �����, �.�. ��� ���������� ������ ������������ � ��� ��� CLP
	__interface IProjectDBUtils: public IUnknown
	{
		//0. ���������� �������� ��� � �� (�������/�������)
		HRESULT UpdateBldAndPSH();
		//1. �������� ���������� ��� ������ ������, ��� �� ������ (��. �������� �����)
		HRESULT CreatePublicationsForOldDB();
		//2.���������� ������ ������ ����������
		bool HasOldPublications(); //������� �� ����������, ����� �������� �������������� � ������ ���
		HRESULT UpdateOldPublications();
		//3. ����������/�������� ��������� ������������ ��������� ���������� (� ����� � ������)
		HRESULT CheckAndUpdateActualPublications();
		//4. �������� �������������� �����
		HRESULT DeleteUnusedMeshes();
	};

//��������! ����� ������ ����������� ��������� ��������� ������ � �����!
#define MSTUDIO_PBH_API_CUR_VER_MAJOR 1
#define MSTUDIO_PBH_API_CUR_VER_MINOR 6

	__interface IFactoryInterface
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ����������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_PBH_API_CUR_VER_MAJOR � MSTUDIO_PBH_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//�������� ������ ������� ��� ������ � ����������� "������ � ����������"
		HRESULT CreatePBH(IPBH **pNew);

		HRESULT CreateProjectDBUtils(MStudioDB::IDataBase *pDb, MStudioData::IProgressWnd *pProgress,
			IProjectDBUtils **pNew);
	};

#define MODEL_STUDIO_PBH_MODULE_NAME L"mstProjectBuildingHierarchy.dll"
#define MODEL_STUDIO_PBH_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PBH_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PBH_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
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
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
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