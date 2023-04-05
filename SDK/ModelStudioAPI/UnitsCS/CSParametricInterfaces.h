#pragma once

#include "..\msData\CSDataInterfaces.h"

//���������� ��� ������ � ��������������� �������������
namespace MStudioParametric
{
	//��������� ����� ���������������� ������������ (linCSNode)
	//��������� ������� ������, ���� �� ������� ����� DetachNodes
	__interface IParametricNodes: public IUnknown
	{
		//��������� ���������� �����
		idx_t GetCount();
		//��������� ���� (linCSNode) �� �������
		AcDbEntity* GetNode(idx_t nNode);

		//������������ ����� - ��������� �� ������ �� � �����������
		void DetachNodes();
		//�������� �� ��������� ���������� ����� (false ����� ������ DetachNodes)
		bool IsNodesOwner();

		//������������� ����� � ����������� ��������������� �������� (linCSParametricSolidBase)
		//���� ����������� � �� �� AcDbBlockTableRecord � ������� ��������� pParametric
		//pTrans - ���������� � ������ ������� ���������� ����������
		//bTransformNodes - ������� �� ���������������� ���� � ������� ��������� pParametric
		Acad::ErrorStatus AttachNodesToParametric(AcDbEntity* pParametric, AcTransaction* pTrans,
			bool bTransformNodes=true);
	};

	//��������� ������-������ ��� ��������������� ���������
	//������ ��������� ��������� �������� ��������������� ��������� pParametricEnt
	//pParametricEnt ������ ���� ������������� �� linCSParametricSolidBase
	//���� �������� ������� ��� ������, �� ���������� �������� ������� ������� ��� ������������ const
	__interface IParametricEntWrapper: public IUnknown
	{
		//----������� ��������� �������------------------------------------------------------------
		//��������� ������� ��������� � ���������
		void GetCoordSystem(AcGeMatrix3d& mtCoordSystem) const;
		//��������� ������� ��������� � ���������
		void GetCoordSystem(AcGePoint3d &ptPosition, AcGeVector3d &vX, AcGeVector3d &vY, AcGeVector3d &vZ) const;

		//��������� ���������
		AcGePoint3d GetPosition() const;
		//��������� ����������� ��� X
		AcGeVector3d GetDirX() const;
		//��������� ����������� ��� Y
		AcGeVector3d GetDirY() const;
		//��������� ����������� ��� Z
		AcGeVector3d GetDirZ() const;
		//��������� ��������
		double GetScale() const;

		//��������� ���������
		Acad::ErrorStatus SetPosition(const AcGePoint3d& ptPosition);
		//��������� ����������� ��� X
		Acad::ErrorStatus SetDirX(const AcGeVector3d& vtDirX);
		//��������� ����������� ��� Y
		Acad::ErrorStatus SetDirY(const AcGeVector3d& vtDirY);
		//��������� ����������� ��� Z
		Acad::ErrorStatus SetDirZ(const AcGeVector3d& vtDirZ);
		//��������� ��������
		Acad::ErrorStatus SetScale(double fScale=1.0);

		//----��������������� ������� � ��������---------------------------------------------------
		//��������� ������ �� ������ � ��������������� �������� ��� 2D ��� 3D �������
		Acad::ErrorStatus GetGraphicsRoot(MStudioData::IElement **pParametric, bool b3DMode);
		//��������� ������ �� ������ � ����������� �������
		Acad::ErrorStatus GetParametersRoot(MStudioData::IElement **pParameters);
		//���������� ������ � ���������� ������� �������, ����� ��������� �������� �������� � ����
		Acad::ErrorStatus UpdateData();

		//��������� �������� ������ ����������� ������� (2D ��� 3D)
		bool Is3DMode();
		//��������� �������� ������ ����������� ������� (2D ��� 3D)
		void Set3dMode(bool bMode3d);

		//----XML ������������---------------------------------------------------------------------
		//������� ��������������� �������� � XML ���� (������ XPG)
		bool ExportToXmlFile(LPCTSTR pszFileName);
		//������� ��������������� �������� � XML ������ (������ XPG)
		bool ExportToXmlString(BSTR* pStrResXML);
		//������ ��������������� �������� �� XML ����� (������ XPG, XPGX)
		//pResNodes - ��������� ����, ������� ���������� �������� � ������ �������
		bool ImportFromXmlFile(LPCTSTR pszFileName, IParametricNodes** pResNodes=NULL);
		//������ ��������������� �������� �� XML ������ (������ XPG)
		//pResNodes - ��������� ����, ������� ���������� �������� � ������ �������
		bool ImportFromXmlString(LPCTSTR pszSourXML, IParametricNodes** pResNodes=NULL);

		//----������ � ��������, �������� � ������ ������-----------------------------------------
		//��������� ����������� ��������������� �������� linCSParametricSolidBase
		AcDbEntity* GetWrappedEnity();
		//��������� ����������� ��������������� �������� linCSParametricSolidBase
		//��������� ������������ �����, ����������� ������ ��������� ��� ��������� ��������� ���������
		Acad::ErrorStatus SetWrappedEnity(AcDbEntity* pEnt);

		//----������ ���������� � XPG--------------------------------------------------------------
		//������ ��������� � ������� ������������ ��� ��������
		//pSourPoly - �������� ��������� (�������������� ����)
		//pDestParent - ���� ��������������� ������� � ������� ���������� ������������� ������� (������������ ��� ��������)
		//mtTransform - ������� ������������� ����� �������
		Acad::ErrorStatus ImportProfile(const AcDbPolyline* pSourPoly, MStudioData::IElement* pDestParent,
			const AcGeMatrix3d& mtTransform,bool bCloseIfPolyClosed);

		//��������� ������� ������������� ������� ��������������� �������� � ��������
		//bAskAngle - �������� �� ������ ����
		//pBasePoint - ��������� ������ ����� �������. � ���� ������ ���������� ������ ������ ���� ���
		// ������ ����� (��. PE_PARAM_INSERTION_SECOND_POINT)
		//���������� true, ���� �������� ������� ��������� � �� ��������
		bool PlaceWithJig(bool bAskAngle = true, const AcGePoint3d* pBasePoint = NULL);
	};
	
#define MSTUDIO_PARAMETRIC_API_CUR_VER_MAJOR 1
#define MSTUDIO_PARAMETRIC_API_CUR_VER_MINOR 9

	__interface IFactoryInterface
	{
	public:
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_CORE_API_CUR_VER_MAJOR � MSTUDIO_CORE_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//�������� ����������-������ ��� ��������������� ���������
		// ��. �������� IParametricEntWrapper
		//� ������ �� ������� ���� �������� ��������� Acad::eWrongObjectType
		Acad::ErrorStatus CreateParametricWrapper(IParametricEntWrapper** pWrapper, AcDbEntity* pParametricEnt);

		//������ ��������� �������� ���������������� ������������ linCSParametricSolid
		//��� ����� ������� � � �������������� RTTI ��������
		//����� ����� ������� �������� �� XPG (���� ��� ������) � ������� ������ IParametricEntWrapper
		AcDbEntity* CreatePlainParametricEntity();

		//���������� ������� ����� ��� ���� ��������������� ��������� (�� ����� ���� ��������������)
		AcRxClass* GetParametricEntBaseClass();
		//���������� ����� ���������������� ������������
		AcRxClass* GetParametricEntClass();
		//���������� ����� ����
		AcRxClass* GetNodeClass();
		//�������� �� �������� ��������������� �������������
		bool IsParametricEntity(const AcDbEntity *pEnt);

		//---������ � ������� ���������------------------------------------------------------------
		//���������� ����� ��������������� ��������� � ����
		//��� ������� �������� ��������� ������������ � ������ ��������� �������� ��������������
		//��� ��������� �������� ��������� ������������ ��� ���������� ������� ������ ���������� ��������������
		//������ ������ � ��� �� �������, � ������� ����������� �������� �������� � arrSource
		AcDbEntity* CreateMergedParametricEntitiy(const AcDbVoidPtrArray& arrSource);

		// ���������� �������������� 3� ����� ��� ���������� ����
		// ���� pDb = Null �� ��������� ��� ������� ���� ������
		bool Is3dMode(AcDbDatabase* pDb = NULL);

		//������������� 3� ����� ��� ���������� ����
		// ���� pDb = Null �� ������������� ��� ������� ���� ������
		void Set3dMode(bool b3dMode, AcDbDatabase* pDb=NULL);
	};

#ifndef NCAD
#define MODEL_STUDIO_PARAMETRIC_MODULE_NAME L"UnitsCS.dbx"
#else
#define MODEL_STUDIO_PARAMETRIC_MODULE_NAME L"UnitsCS.nrx"
#endif 
#define MODEL_STUDIO_PARAMETRIC_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_PARAMETRIC_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_PARAMETRIC_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
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
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
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