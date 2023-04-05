#pragma once

#include "ms3DTypes.h"

//Интерфейсы ModelStudio API для работы с трёхмерной графикой
namespace MStudioGraphics
{
	//Интерфейс трёхмерной матрицы 4x4
	__interface IMatrix: IUnknown
	{
		//Трансформирует точку pt и возвращает трансформированную точку
		CSPOINTD TransformPoint(const CSPOINTD& pt) const;
		//Трансформирует вектор vt и возвращает трансформированную точку
		CSVECTORD3 TransformVector(const CSVECTORD3& vt) const;

		//Является ли матрица матрицей перемещения
		bool IsTranslationOnly() const;
		//Является ли матрица единичной
		bool IsIdentity() const;

		//Инвертирует матрицу (не всегда возможно)
		HRESULT Inverse();		

		//Устанавливает матрица в единичную матрицу
		HRESULT SetToIdentity();

		//Устанавливает матрицу трансформации из одной СК в другую
		HRESULT SetToAlignCoordSys(const CSPOINTD& ptOrigSrc,
			const CSPOINTD& vtXSrc,
			const CSPOINTD& vtYSrc,
			const CSPOINTD& vtZSrc,
			const CSPOINTD& ptOrigDest,
			const CSPOINTD& vtXDest,
			const CSPOINTD& vtYDest,
			const CSPOINTD& vtZDest);

		//Применяет к матрице векторное представление
		HRESULT SetMatrix(double matrixData[]);
		//Возвращает векторное представление матрицы
		double* GetMatrix();

		//Устанавливает матрицу в систему координат с вычислением вектора Z
		HRESULT SetToCoordSystem(const CSPOINTD& ptOrig,
			const CSVECTORD3& vtX,
			const CSVECTORD3& vtY);

		//Устанавливает матрицу в систему координат
		HRESULT SetToCoordSystem(const CSPOINTD& ptOrig,
			const CSVECTORD3& vtX,
			const CSVECTORD3& vtY,
			const CSVECTORD3& vtZ);		

		//Устанавливает матрицу в матрицу вращения вокруг оси X на угол fAngle в радианах
		HRESULT SetToRotationAroundX(double fAngle);
		//Устанавливает матрицу в матрицу вращения вокруг оси Y на угол fAngle в радианах
		HRESULT SetToRotationAroundY(double fAngle);
		//Устанавливает матрицу в матрицу вращения вокруг оси Z на угол fAngle в радианах 
		HRESULT SetToRotationAroundZ(double fAngle);
		//Устанавливает матрицу в матрицу вращения вокруг оси vtAxis на угол fAngle в радианах
		HRESULT SetToRotation(const CSVECTORD3& vtAxis,
			double fAngle);

		//Умножат матрицу на pMt (operator*)
		//Возвращает this
		IMatrix* PostMultiplyBy(IMatrix* pMt);

		//Умножат pMt на данную матрицу
		//Возвращает this
		IMatrix* PreMultiplyBy(IMatrix* pMt);

		//Устанавливает матрицу в результат произведения pMt1*pMt2
		//Возвращает this
		IMatrix* SetToProduct(IMatrix* pMt1, IMatrix* pMt2);

		//Сравнивает матрицу с pMt
		bool IsEquals(IMatrix* pMt);
	};

	//Интерфейс класса для создания сетки в формате msm
	__interface IMeshCreator: IUnknown
	{
		//Сериализует сетку в бинарные данные
		//Данный класс сам освободит память, на которую возвращается указатель
		//в деструкторе, либо при следующем вызове метода GeneratePacked
		unsigned char* GeneratePacked(int& nSize,int& nHash, CSVECTORD3& vSize) const;

		//Устанавливает текущий материал (все методы Add будут добавлять грани этого материала)
		HRESULT SetCurrentMaterial(const CCSMaterial& vtMaterial);

		//Подготавливает класс для добавления заранее известного количества граней
		HRESULT PrepareToAddTriangles(int nTrianglesCount);

		//Трансформирует сетку
		HRESULT TransformBy(IMatrix* pMtTransform);
		//Трансформирует сетку
		HRESULT TransformBy(double* pMtTransform);
		//Трансформирует сетку
		HRESULT TranslateBy(const CSVECTORD3& vtTranslate);

		//Получение текущих экстентов сетки
		HRESULT GetExtents(CSPOINTD& ptResMin, CSPOINTD& ptResMax);
		//Получение экстентов трансформированной сетки (сама сетка остаётся неизменной)
		HRESULT GetTransformedExtents(IMatrix* pMtTransform, CSPOINTD& ptResMin, CSPOINTD& ptResMax);
		//Получение экстентов трансформированной сетки (сама сетка остаётся неизменной)
		HRESULT GetTransformedExtents(double* pMtTransform, CSPOINTD& ptResMin, CSPOINTD& ptResMax);

		//Добавляет положение вершины
		DWORD AddPosition(const CSPOINTD& ptPosition);
		//Добавляет нормаль вершины
		DWORD AddNormal(const CSVECTORD3& vtNormal);

		//Добавляет треугольник (грань)
		HRESULT AddTriangleFace(DWORD nPos1, DWORD nNorm1, DWORD nPos2, DWORD nNorm2,
			DWORD nPos3, DWORD nNorm3);  // 3 normals indexes

		//Добавляет треугольник (грань)
		HRESULT AddTriangleFace(const CSVERTEXD &v1, const CSVERTEXD &v2, const CSVERTEXD &v3);
		
		//Переносит графику сетки pOther в текущую сетку
		//После операции Сетка other остаётся пустой		
		HRESULT AddMesh(IMeshCreator *pOther);

		//Добавляет параллелограмм
		HRESULT AddSquereFace(const CSPOINTD& pt0, const CSPOINTD& pt1,
			const CSPOINTD& pt2, const CSPOINTD& pt3, bool bDualFace);

		//Добавляет оболочку по аналогии с методами автокада
		HRESULT AddShell(int nVertices, const CSPOINTD* arrVertexList,
			int nFacesListSize, const int* arrFaceList, bool bDualFaces,
			const CSVECTORD3* pVertexNormals = NULL);

		//Добавляет сеть по аналогии с методами автокада
		HRESULT AddMesh(const CSPOINTD* arrVertexList, int nRows, int nCols, bool bDualFaces);

		//Добавляет ссылку на вхождение другой сетки с заданием цвета и трансформации
		HRESULT AddMeshInstance(IMeshCreator *pOther, const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ, CCSMaterial* pMaterial);

		//Добавляет полилинию
		HRESULT AddPolyline(CSPOINTD* arrVertices, int nCount);
		//Добавляет окружность
		HRESULT AddCircle(const CSPOINTD& ptCenter, const CSVECTORD3& vtNormal, double fRadius);
		//Добавляет дугу окружности
		HRESULT AddCircleArc(const CSPOINTD& ptCenter, const CSVECTORD3& vtUAxis,
			const CSVECTORD3& vtVAxis, double fArcAngle);

		//Добавляет параллелепипед (тонкостенный, если fThickness > 0)
		HRESULT AddBox(double fLength, double fWidth, double fHeight, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет конус (тонкостенный, если fThickness > 0)
		HRESULT AddCone(double fRadius1, double fRadius2, double fHeight, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет эксцентрический конус (тонкостенный, если fThickness > 0)
		HRESULT AddConeEx(double fRadius1, double fRadius2, double fHeight, double fThickness,
			const CSVECTORD2 &vtOffset,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет цилиндр (тонкостенный, если fThickness > 0)
		HRESULT AddCylinder(double fRadius, double fHeight, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет сектор цилиндра (тонкостенный, если fThickness > 0)
		HRESULT AddCylSlope(double fRadius,	double fHeight,	double fBottonInclAngleDeg,
			double fBottonRotInclAngleDeg,	double fTopInclAngleDeg, double fTopRotInclAngleDeg,
			double fThickness, const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет блюдо (тонкостенное, если fThickness > 0)
		HRESULT AddDish(double fRadius, double fHeight,	double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет штуцер (тонкостенный, если fThickness > 0)
		HRESULT AddNozzle(double fLen, double fLen2, double fLen3,
			double fRadius, double fRadius2, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет пирамиду со смещённым центром (тонкостенную, если fThickness > 0)
		HRESULT AddPyramid(double fLength, double fWidth, double fHeight,
			double fLength2, double fWidth2, double fThickness,
			const CSVECTORD2 &vtOffset,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		///////////////////////////////////////////////////////////////////////////////////////
		//Подготавливает класс к введению нового контура выдавливания или вращения
		HRESULT Start2DProfile(int nPoints);		
		
		//Добавляет вершину отрезка контура (см. профиль XPG)
		HRESULT Add2DProfileLinePoint(double fProfilePointX, double fProfilePointY);
		
		//Добавляет вершину дуги контура (см. профиль XPG)
		//bCenterPtOnRight - находится ли центр справа
		HRESULT Add2DProfileArcPoint(double fProfilePointX, double fProfilePointY, 
			double fRadius, bool bCenterPtOnRight);

		//Добавляет фигуру выдавливания по профилю, заданному методами
		//Start2DProfile, Add2DProfileLinePoint, Add2DProfileArcPoint
		HRESULT AddExtrusion(double fHeight, 
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет фигуру вращения по профилю, заданному методами
		//Start2DProfile, Add2DProfileLinePoint, Add2DProfileArcPoint
		HRESULT AddRevolve(double fAngleDeg,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);
		///////////////////////////////////////////////////////////////////////////////////////

		//Добавляет сферу (тонкостенную, если fThickness > 0)
		HRESULT AddSphere(double fRadius, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет тор (тонкостенный, если fThickness > 0)
		HRESULT AddTorus(double fRadius, double fRadius2, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет сектор тора (тонкостенный, если fThickness > 0)
		HRESULT AddTorusArc(double fRadius, double fRadius2, double fAngleDeg, double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);

		//Добавляет клин (тонкостенный, если fThickness > 0)
		HRESULT AddWedge(double fLength, double fWidth, double fHeight,	double fThickness,
			const CSPOINTD& ptOrigin, const CSVECTORD3& vtX,
			const CSVECTORD3& vtY, const CSVECTORD3& vtZ);
	};

#define MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR 1
#define MSTUDIO_GRAPHICS_API_CUR_VER_MINOR 1

	__interface IFactoryInterface
	{
		//Получение версии возвращаемых интерфейсов (всегда первый метод)
		//Все версии интерфейсы внутри nMajorVer имеют обратную совместимость
		//Каждый модуль имеет свою собственную версию
		//Выдаваемые значения необходимо сравнить с MSTUDIO_GRAPHICS_API_CUR_VER_MAJOR и MSTUDIO_GRAPHICS_API_CUR_VER_MINOR
		void GetApiVersion(int &nMajorVer, int &nMinorVer);

		//Создаёт объект наполнения сетки
		HRESULT CreateMeshCreator(IMeshCreator** ppNewObj);

		//Создаёт матрицу
		HRESULT CreateMatrix(IMatrix** ppNewObj);
	};

#define MODEL_STUDIO_GRAPHICS_MODULE_NAME L"CSGraphics.dll"
#define MODEL_STUDIO_GRAPHICS_ENTRY_NAME "GetMStudioDataInterface"

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

			HINSTANCE hDataDll = AfxLoadLibrary(MODEL_STUDIO_GRAPHICS_MODULE_NAME);
			if (!hDataDll)
				return NULL;

			MSTPluginEntryFn* pGetFn = 
				(MSTPluginEntryFn*)GetProcAddress(hDataDll, MODEL_STUDIO_GRAPHICS_ENTRY_NAME);
			if (!pGetFn)
				return NULL;

			//Функция вернёт интерфейс последней версии в том случае, если переданная версия не поддерживается
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
					strErrorMsg.Format(L"Не поддерживаемая версия ModelStudio (модуль %s): %d.%d\nПредполагаемая версия: %d.>=%d",
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