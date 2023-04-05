#pragma once

#include "..\msData\CSDataInterfaces.h"

namespace MStudioCable
{
	__interface IJournalCable; //forward declaration
	
	//����� ���������� ����� (�����) � ����������� � �������
	__interface IJournalEdge: public IUnknown
	{
		//��������� �������������� ������� ����� (���������)
		AcDbObjectId GetTrayId();
		//��������� �������������� ����� �� ����� (���������)
		int GetShelfId();

		//����� �����
		double GetLength();
		//������ �����
		double GetWidth();
		//������ �����
		double GetHeight();

		HRESULT GetBuilding(BSTR *pStrRes);

		int GetDivisionsCount();
		HRESULT GetDivisionAt(int nDivisionIndex, BSTR* pStrRes);

		//���������� �������, ����������� �� �����
		int GetCablesCount();
		//��������� ���������� � ����������� ������ �� �������
		HRESULT GetCableAt(int nCableIndex, IJournalCable** pResCable);
	};

	//���������� �� ������� ���� ������
	__interface ICableOnTrayInfo: public IUnknown
	{
		//��������� �������������� ������� ����� (���������)
		AcDbObjectId GetTrayId();
		//��������� �������������� ����� �� ����� (���������)
		int GetShelfId();

		//����� ������, ������������ �� �����
		double GetLength();
		//��������� ������ �� ����� �� ���������
		double GetHorizontalPosition();
		//��������� ������ �� ����� �� �����������
		double GetVerticalPosition();

		//��������� ����������� ������ ������ � ������� �����������
		double GetHeightMin();
		//��������� ������������ ������ ������ � ������� �����������
		double GetHeightMax();

		//��������� ������ �����
		double GetTrayHeight();
		//��������� ������ �����
		double GetTrayWidth();
	};

	//���������� � ��������� ������
	__interface IJournalCable: public IUnknown
	{
		//��������� �������������� ������� ������
		AcDbObjectId GetCableId();
		//��������� �������������� ����, � �������� ���������� ������ ������
		AcDbObjectId GetNodeStartId();
		//��������� �������������� ����, � �������� ��������� ����� ������
		AcDbObjectId GetNodeEndId();

		//������ ������
		double GetRadius();

		HRESULT GetAbbriviation(BSTR *pStrRes);
		HRESULT GetDivision(BSTR *pStrRes);

		//������
		UINT GetGoroup();

		//��������� ���������� �������� ����, �� ������� �������� ������
		int GetTraysCount();
		//��������� ���������� �� ������� ���� ��������� ������ �� �������
		HRESULT GetTrayAt(int nTrayIndex, ICableOnTrayInfo** pResInfo);
	};

	//��������� ������ ���������� �������
	__interface ICableJournal: public IUnknown
	{
		//�������������� ��������� ������, ���������� ������ ������� ������ ��������
		HRESULT Init();

		//��������� ���������� ����� (����) ���������� ����� 
		int GetEdgesCount();
		//��������� ����� (�����) ���������� ����� �� �������
		HRESULT GetEdgeAt(int nEdgeIndex, IJournalEdge** pResEdge);

		//��������� ���������� ������� � �������
		int GetCablesCount();
		//��������� ������ �� �������
		HRESULT GetCableAt(int nCableIndex, IJournalCable** pResCable);
	};


#define MSTUDIO_CABLE_API_CUR_VER_MAJOR 1
#define MSTUDIO_CABLE_API_CUR_VER_MINOR 7

	__interface IFactoryInterface
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_CABLE_API_CUR_VER_MAJOR � MSTUDIO_CABLE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//�������� ������ ������� ���������� �������
		HRESULT CreateCableJournal(ICableJournal** pNewCableJournal);

		//��������� ������ ������ (mstCable)
		AcRxClass* GetCableClass();
		//��������� ����� ��������� (mstRoutePrototype)
		AcRxClass* GetPrototypeClass();
		//��������� �������� ������ ����������� ��������� - ����� � �.�.(mstRouteConstructionBase)
		AcRxClass* GetPrototypeConstructionBaseClass();
	};

#ifndef NCAD
#define MODEL_STUDIO_CABLE_MODULE_NAME L"mstRouteUi.arx"
#else
#define MODEL_STUDIO_CABLE_MODULE_NAME L"mstRouteUi.nrx"
#endif 
#define MODEL_STUDIO_CABLE_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_CABLE_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_CABLE_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
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
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
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