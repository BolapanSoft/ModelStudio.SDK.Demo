#pragma once

#include "..\msData\CSDataInterfaces.h"
#include "..\mstudioDB\CSDBInterfaces.h"

//���������� ��� ������ � ��������������� ModelStudio
namespace MStudioCore
{
#define MSTUDIO_CORE_API_CUR_VER_MAJOR 1
#define MSTUDIO_CORE_API_CUR_VER_MINOR 7

	__interface IMStudioCore
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_CORE_API_CUR_VER_MAJOR � MSTUDIO_CORE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//��������� ������� �� ����������� �������� ��������� ������ �������� (�������� �� �������� ModelStudio)
		bool IsDataObject(AcDbObject* pObj);
		//��������� ������� �� ����������� �������� ��������� ������ �������� (�������� �� �������� ModelStudio)
		bool IsDataObject(const AcDbObjectId& idObj);

		//---������ � ����������� �������----------------------------------------------------------
		//��������� ������ ���������� ������� �� ObjectId
		//� ������, ���� ������ �� ������������ ���������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT GetObjectParameters(const AcDbObjectId& idObject, MStudioData::IElement **pResParams, void* pContext=NULL);

		//��������� ������ ���������� �������
		//� ������, ���� ������ �� ������������ ���������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT GetObjectParameters(AcDbObject* pObj, MStudioData::IElement **pResParams, void* pContext=NULL);

		//��������� �������� ������� � ������������ � �������� �� �������� (������������ �� ����������� ���������)
		//� ������, ���� ������ �� ������������ ���������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT GetObjectDescription(AcDbObject* pObject, BSTR* pStrResult);
		//��������� ����� �������
		//� ������, ���� ������ �� ������������ ���������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT GetObjectName(AcDbObject* pObject, BSTR* pStrResult);

		//������ ����� ������ ���������� �������
		//idObject - ������������� �������
		//pParams - ������ ����������, ������� ���������� ���������
		//bStandard - ��������������� � true, ���� ������ ����������� �� ����������, ����� false (��� ������������ ��������� ������������ �������)
		//� ������, ���� ������ �� ������������ ������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT SetObjectParameters(const AcDbObjectId& idObject, MStudioData::IElement *pParams, bool bStandard);

		//������ ����� ������ ���������� �������
		//pDestObject - ������ ����������
		//pParams - ������ ����������, ������� ���������� ���������
		//bStandard - ��������������� � true, ���� ������ ����������� �� ����������, ����� false (��� ������������ ��������� ������������ �������)
		//� ������, ���� ������ �� ������������ ������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT SetObjectParameters(AcDbObject* pDestObject, MStudioData::IElement *pParams, bool bStandard);

		//��������� ����������, ����������� � pParams - ����� ��������� ������ ��������� ���������
		//idObject - ������������� �������
		//pParams - ��������� ������� ��� ���������� (��. IParamsOwner::ApplyParameter)
		//bStandard - ��������������� � true, ���� ������ ����������� �� ����������, ����� false (��� ������������ ��������� ������������ �������)
		//� ������, ���� ������ �� ������������ ������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT SetObjectParameters(const AcDbObjectId& idObject, MStudioData::IParamsOwner *pParams, bool bStandard);

		//��������� ����������, ����������� � pParams - ����� ��������� ������ ��������� ���������
		//pDestObject - ������ ����������
		//pParams - ��������� ������� ��� ���������� (��. IParamsOwner::ApplyParameter)
		//bStandard - ��������������� � true, ���� ������ ����������� �� ����������, ����� false (��� ������������ ��������� ������������ �������)
		//� ������, ���� ������ �� ������������ ������� ���������� ��� ��������� ������ ���������� S_FALSE
		HRESULT SetObjectParameters(AcDbObject* pDestObject, MStudioData::IParamsOwner *pParams, bool bStandard);

		//---������ � GUID �������-----------------------------------------------------------------
		//���������� GUID ������� (������������� ��� ���������� ������ � �� � ����������� ����� � ��) ��� GUID_NULL
		GUID GetObjectGUID(const AcDbObject* pEnt);

		//������������� ����� GUID ������� (����� XData)
		HRESULT SetObjectGUID(AcDbObject* pEnt, GUID guid);

		//---������������ ������� � ������������---------------------------------------------------
		//�������� ����������� �������������� �������������� �� �������
		//pEnt - �������� ��� ��������� AABB
		//ptOrig, vX, vY, vZ - �������������� �������� ����� � ��� ��������������
		//� ������ ������ ���������� S_FALSE
		HRESULT GetEntityBoundingBox(const AcDbEntity* pEnt, AcGePoint3d& ptOrig, AcGeVector3d& vX, AcGeVector3d& vY, AcGeVector3d& vZ);

		//���������� �������� ����� ��������
		//pEnt - �������� ��� ��������� �������� �����
		//ptOrig - �������������� �������� ����� ��������
		//� ������ ������ ���������� S_FALSE
		HRESULT GetEntityOrigin(const AcDbEntity* pEnt, AcGePoint3d& ptOrig);
	};

#ifndef NCAD
#define MODEL_STUDIO_CORE_MODULE_NAME L"UnitsCS.dbx"
#else
#define MODEL_STUDIO_CORE_MODULE_NAME L"UnitsCS.nrx"
#endif 
#define MODEL_STUDIO_CORE_ENTRY_NAME "GetMStudioCoreInterface"

	//����� ��� ��������� �������� ���������� API ModelStudio ������� ������
	//������ ��� ������ ���� �������� � ������
	class CMStudioDataInterface
	{
	public:
		typedef IMStudioCore* MSTPluginEntryFn(int nClientMajorVer, int nClientMinorVer);

		//��������� �������� ���������� API ModelStudio ������� ������
		//���� ���������� bCheckVersion, �� ����� ����������� �������� ������������� ������ ������������
		//������ � ������� API � � ������ ��������������� ��������� ���������� ���� CString
		static IMStudioCore* Get(bool bCheckVersion=true)
		{
			//�������� ���������� ������ ������� ����������� ������
			static IMStudioCore* pRes = NULL;
			if (pRes)
				return pRes;

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_CORE_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_CORE_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
			pRes = pGetFn(MSTUDIO_CORE_API_CUR_VER_MAJOR, MSTUDIO_CORE_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_CORE_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_CORE_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
						MODEL_STUDIO_CORE_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_CORE_API_CUR_VER_MAJOR, MSTUDIO_CORE_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}