#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"
#include "CSProjectStructureHierarchyConstants.h"

namespace MStudioStructureHierarchy
{
	//��������� ������� ���������� "��������� �������� �������"
	//�������� ������� ������� -> ������ ������� -> ��������� -> �����
	__interface IPSH: public IUnknown
	{
		//������� �� (����� ���� NULL)
		HRESULT GetDB(MStudioDB::IDataBase** pResDb);
		//��������� ������� �� (����� ���� NULL)
		//���� �������� �� ����� ��������, �� ��� ����� �������� �������� � �������� �� ����� ��������
		//��� ������� � ������������� ��������� �������� � ������������ ��������
		HRESULT SetDB(MStudioDB::IDataBase* pDb);

		//--------GUI----------------------------------------
		//����� ������� �������������� ��������
		int ShowHierarchyEditDialog(HWND hParentWnd, int nRootObjectId);
		//���������� ������ ������ ������� ��������(������ ������)
		int ShowHierarchySelectDialog(HWND hParentWnd, int nRootObjectId);

		//����������� �������� �� �����, ������ �� ���������� ������� ��������
		bool XmlImportFromFile(LPCTSTR pszFileName);	
	};

//��������! ����� ������ ����������� ��������� ��������� ������ � �����!
#define MSTUDIO_PSH_API_CUR_VER_MAJOR 1
#define MSTUDIO_PSH_API_CUR_VER_MINOR 3

	__interface IFactoryInterface
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ����������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_PSH_API_CUR_VER_MAJOR � MSTUDIO_PSH_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//�������� ������ ������� ��� ������ � ����������� "������ � ����������"
		HRESULT CreatePBH(IPSH** pNew);
	};

#define MODEL_STUDIO_PSH_MODULE_NAME L"mstProjectStructureHierarchy.dll"
#define MODEL_STUDIO_PSH_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PSH_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PSH_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
			pRes = pGetFn(MSTUDIO_PSH_API_CUR_VER_MAJOR, MSTUDIO_PSH_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_PSH_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_PSH_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
						MODEL_STUDIO_PSH_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_PSH_API_CUR_VER_MAJOR, MSTUDIO_PSH_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}