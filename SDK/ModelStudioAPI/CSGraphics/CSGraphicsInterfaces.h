#pragma once

#include "ms3DTypes.h"

//���������� ModelStudio API ��� ������ � ��������� ��������
namespace MStudioGraphics
{
	//��������� ��������� ������� 4x4
	__interface IMatrix: IUnknown
	{
		//�������������� ����� pt � ���������� ������������������ �����
		CSPOINTD TransformPoint(const CSPOINTD& pt) const;
		//�������������� ������ vt � ���������� ������������������ �����
		CSVECTORD3 TransformVector(const CSVECTORD3& vt) const;

		//�������� �� ������� �������� �����������
		bool IsTranslationOnly() const;
		//�������� �� ������� ���������
		bool IsIdentity() const;

		//����������� ������� (�� ������ ��������)
		HRESULT Inverse();		

		//������������� ������� � ��������� �������
		HRESULT SetToIdentity();

		//������������� ������� ������������� �� ����� �� � ������
		HRESULT SetToAlignCoordSys(const CSPOINTD& ptOrigSrc,
			const CSPOINTD& vtXSrc,
			const CSPOINTD& vtYSrc,
			const CSPOINTD& vtZSrc,
			const CSPOINTD& ptOrigDest,
			const CSPOINTD& vtXDest,
			const CSPOINTD& vtYDest,
			const CSPOINTD& vtZDest);

		//��������� � ������� ��������� �������������
		HRESULT SetMatrix(double matrixData[]);
		//���������� ��������� ������������� �������
		double* GetMatrix();

		//������������� ������� � ������� ��������� � ����������� ������� Z
		HRESULT SetToCoordSystem(const CSPOINTD& ptOrig,
			const CSVECTORD3& vtX,
			const CSVECTORD3& vtY);

		//������������� ������� � ������� ���������
		HRESULT SetToCoordSystem(const CSPOINTD& ptOrig,
			const CSVECTORD3& vtX,
			const CSVECTORD3& vtY,
			const CSVECTORD3& vtZ);		

		//������������� ������� � ������� �������� ������ ��� X �� ���� fAngle � ��������
		HRESULT SetToRotationAroundX(double fAngle);
		//������������� ������� � ������� �������� ������ ��� Y �� ���� fAngle � ��������
		HRESULT SetToRotationAroundY(double fAngle);
		//������������� ������� � ������� �������� ������ ��� Z �� ���� fAngle � �������� 
		HRESULT SetToRotationAroundZ(double fAngle);
		//������������� ������� � ������� �������� ������ ��� vtAxis �� ���� fAngle � ��������
		HRESULT SetToRotation(const CSVECTORD3& vtAxis,
			double fAngle);

		//������� ������� �� pMt (operator*)
		//���������� this
		IMatrix* PostMultiplyBy(IMatrix* pMt);

		//������� pMt �� ������ �������
		//���������� this
		IMatrix* PreMultiplyBy(IMatrix* pMt);

		//������������� ������� � ��������� ������������ pMt1*pMt2
		//���������� this
		IMatrix* SetToProduct(IMatrix* pMt1, IMatrix* pMt2);

		//���������� ������� � pMt
		bool IsEquals(IMatrix* pMt);
	};

	//��������� ������ ��� �������� ����� � ������� msm
	__interface IMeshCreator: IUnknown
	{
		//����������� ����� � �������� ������
		//������ ����� ��� ��������� ������, �� ������� ������������ ���������
		//� �����������, ���� ��� ��������� ������ ������ GeneratePacked
		unsigned char* GeneratePacked(int& nSize,int& nHash, CSVECTORD3& vSize) const;

		//������������� ������� �������� (��� ������ Add ����� ��������� ����� ����� ���������)
		HRESULT SetCurrentMaterial(const CCSMaterial& vtMaterial);

		//�������������� ����� ��� ���������� ������� ���������� ���������� ������
		HRESULT PrepareToAddTriangles(int nTrianglesCount);

		//�������������� �����
		HRESULT TransformBy(IMatrix* pMtTransform);
		//�������������� �����
		HRESULT TransformBy(double* pMtTransform);
		//�������������� �����
		HRESULT TranslateBy(const CSVECTORD3& vtTranslate);

		//��������� ������� ��������� �����
		HRESULT GetExtents(CSPOINTD& ptResMin, CSPOINTD& ptResMax);
		//��������� ��������� ������������������ ����� (���� ����� ������� ����������)
		HRESULT GetTransformedExtents(IMatrix* pMtTransform, CSPOINTD& ptResMin, CSPOINTD& ptResMax);
		//��������� ��������� ������������������ ����� (���� ����� ������� ����������)
		HRESULT GetTransformedExtents(double* pMtTransform, CSPOINTD& ptResMin, CSPOINTD& ptResMax);

		//��������� ��������� �������
		DWORD AddPosition(const CSPOINTD& ptPosition);
		//��������� ������� �������
		DWORD AddNormal(const CSVECTORD3& vtNormal);

		//��������� ����������� (�����)
		HRESULT AddTriangleFace(DWORD nPos1, DWORD nNorm1, DWORD nPos2, DWORD nNorm2,
			DWORD nPos3, DWORD nNorm3);  // 3 normals indexes

		//��������� ����������� (�����)
		HRESULT AddTriangleFace(const CSVERTEXD &v1, const CSVERTEXD &v2, const CSVERTEXD &v3);
		
		//��������� ������� ����� pOther � ������� �����
		//����� �������� ����� other ������� ������		
		HRESULT AddMesh(IMeshCreator *pOther);

		//��������� ��������������
		HRESULT AddSquereFace(const CSPOINTD& pt0, const CSPOINTD& pt1,
			const CSPOINTD& pt2, const CSPOINTD& pt3, bool bDualFace);

		//��������� �������� �� �������� � �������� ��������
		HRESULT AddShell(int nVertices, const CSPOINTD* arrVertexList,
			int nFacesListSize, const int* arrFaceList, bool bDualFaces,
			const CSVECTORD3* pVertexNormals = NULL);

		//��������� ���� �� �������� � �������� ��������
		HRESULT AddMesh(const CSPOINTD* arrVertexList, int nRows, int nCols, bool bDualFaces);

		//��������� ������ �� ��������� ������ ����� � �������� ����� � �������������
		HRESULT AddMeshInstance(IMeshCreator *pOther, const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ, CCSMaterial* pMaterial);

		//��������� ���������
		HRESULT AddPolyline(CSPOINTD* arrVertices, int nCount);
		//��������� ����������
		HRESULT AddCircle(const CSPOINTD& ptCenter, const CSVECTORD3& vtNormal, double fRadius);
		//��������� ���� ����������
		HRESULT AddCircleArc(const CSPOINTD& ptCenter, const CSVECTORD3& vtUAxis,
			const CSVECTORD3& vtVAxis, double fArcAngle);

		//��������� �������������� (������������, ���� fThickness > 0)
		HRESULT AddBox(double fLength, double fWidth, double fHeight, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ����� (������������, ���� fThickness > 0)
		HRESULT AddCone(double fRadius1, double fRadius2, double fHeight, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ��������������� ����� (������������, ���� fThickness > 0)
		HRESULT AddConeEx(double fRadius1, double fRadius2, double fHeight, double fThickness,
			const CSVECTORD2 &vtOffset,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ������� (������������, ���� fThickness > 0)
		HRESULT AddCylinder(double fRadius, double fHeight, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ������ �������� (������������, ���� fThickness > 0)
		HRESULT AddCylSlope(double fRadius,	double fHeight,	double fBottonInclAngleDeg,
			double fBottonRotInclAngleDeg,	double fTopInclAngleDeg, double fTopRotInclAngleDeg,
			double fThickness, const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ����� (������������, ���� fThickness > 0)
		HRESULT AddDish(double fRadius, double fHeight,	double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ������ (������������, ���� fThickness > 0)
		HRESULT AddNozzle(double fLen, double fLen2, double fLen3,
			double fRadius, double fRadius2, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� �������� �� ��������� ������� (������������, ���� fThickness > 0)
		HRESULT AddPyramid(double fLength, double fWidth, double fHeight,
			double fLength2, double fWidth2, double fThickness,
			const CSVECTORD2 &vtOffset,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		///////////////////////////////////////////////////////////////////////////////////////
		//�������������� ����� � �������� ������ ������� ������������ ��� ��������
		HRESULT Start2DProfile(int nPoints);		
		
		//��������� ������� ������� ������� (��. ������� XPG)
		HRESULT Add2DProfileLinePoint(double fProfilePointX, double fProfilePointY);
		
		//��������� ������� ���� ������� (��. ������� XPG)
		//bCenterPtOnRight - ��������� �� ����� ������
		HRESULT Add2DProfileArcPoint(double fProfilePointX, double fProfilePointY, 
			double fRadius, bool bCenterPtOnRight);

		//��������� ������ ������������ �� �������, ��������� ��������
		//Start2DProfile, Add2DProfileLinePoint, Add2DProfileArcPoint
		HRESULT AddExtrusion(double fHeight, 
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ������ �������� �� �������, ��������� ��������
		//Start2DProfile, Add2DProfileLinePoint, Add2DProfileArcPoint
		HRESULT AddRevolve(double fAngleDeg,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);
		///////////////////////////////////////////////////////////////////////////////////////

		//��������� ����� (������������, ���� fThickness > 0)
		HRESULT AddSphere(double fRadius, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ��� (������������, ���� fThickness > 0)
		HRESULT AddTorus(double fRadius, double fRadius2, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ������ ���� (������������, ���� fThickness > 0)
		HRESULT AddTorusArc(double fRadius, double fRadius2, double fAngleDeg, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//��������� ���� (������������, ���� fThickness > 0)
		HRESULT AddWedge(double fLength, double fWidth, double fHeight,	double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);
	};

#define MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR 1
#define MSTUDIO_GRAPHICS_API_CUR_VER_MINOR 1

	__interface IFactoryInterface
	{
		//��������� ������ ������������ ����������� (������ ������ �����)
		//��� ������ ���������� ������ nMajorVer ����� �������� �������������
		//������ ������ ����� ���� ����������� ������
		//���������� �������� ���������� �������� � MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR � MSTUDIO_GRAPHICS_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//������ ������ ���������� �����
		HRESULT CreateMeshCreator(IMeshCreator** ppNewObj);

		//������ �������
		HRESULT CreateMatrix(IMatrix** ppNewObj);
	};

#define MODEL_STUDIO_GRAPHICS_MODULE_NAME L"CSGraphics.dll"
#define MODEL_STUDIO_GRAPHICS_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_GRAPHICS_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_GRAPHICS_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//������� ����� ��������� ��������� ������ � ��� ������, ���� ���������� ������ �� ��������������
			pRes = pGetFn(MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR, MSTUDIO_GRAPHICS_API_CUR_VER_MINOR);
			if (!pRes)
				return NULL;

			if (bCheckVersion)
			{
				int nMajorVer = 0;
				int nMinorVer = 0;
				pRes->GetApiVersion(nMajorVer, nMinorVer);
				if (nMajorVer != MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR ||
					nMinorVer < MSTUDIO_GRAPHICS_API_CUR_VER_MINOR)
				{
					CString strErrorMsg;
					strErrorMsg.Format(L"�� �������������� ������ ModelStudio (������ %s): %d.%d\n�������������� ������: %d.>=%d",
						MODEL_STUDIO_GRAPHICS_MODULE_NAME,
						nMajorVer, nMinorVer,
						MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR, MSTUDIO_GRAPHICS_API_CUR_VER_MINOR);
					throw strErrorMsg;
				}
			}

			return pRes;
		}
	};
}