#pragma once

#include <assert.h>
#include <math.h>

#ifdef _VIEWERCOMP
#include <DirectXMath.h>
using namespace DirectX;
#endif
//#include <xtgmath.h>

#ifdef _DEBUG
#ifndef CTPL_ASSERT
#define MS3DTYPES_ASSERT __noop
#pragma message (" No CTPL_ASSERT defined during compiling ms3DTypes.h asserts will be ignored")
#else
#define MS3DTYPES_ASSERT CTPL_ASSERT
#endif
#else
#define MS3DTYPES_ASSERT __noop
#endif

#pragma pack(push, ms3dtypes, 1)

//Compare and hashing defines
#define COMPARE_FLOATS_EPS 1e-5
#define CSDBL_EQUALS(fMember) (fabs(fMember - other.fMember) < COMPARE_FLOATS_EPS)
#define CSMEMBER_EQUALS(fMember) (fMember == other.fMember)
#define CSDBL_LESS(fMember) {if (fabs(fMember - other.fMember) > COMPARE_FLOATS_EPS) return fMember < other.fMember;}
#define CSMEMBER_LESS(fMember) {if (!(fMember == other.fMember)) return fMember < other.fMember;}
#define CSHASH_TYPE __int64
#define CSDBL_HASH(nSalt, fVal)	{nHash *= nSalt; nHash += CSHASH_TYPE(fVal);}
#define CSINT_HASH(nSalt, fVal)	{nHash *= nSalt; nHash += ((CSHASH_TYPE)fVal);}

inline double MS_ROUND(double value) { return value < 0 ? -floor(0.5 - value) : floor(0.5 + value); }
inline float MS_ROUND(float value) { return (float)( value < 0 ? -floor(0.5f - value) : floor(0.5f + value)); }

#define FACTOR 1000.0
#define FACTORf 1000.0f
// неудачная попытка округления с учётом масштаба
//#define NORMALIZE_ROUND(dValue) {int nExp(0); dValue = ldexp((MS_ROUND((frexp(dValue, &nExp) - 0.5) * 2.0 * FACTOR) / FACTOR) / 2.0 + 0.5, nExp);}
//#define NORMALIZE_ROUND_F(dValue) {int nExp(0); dValue = ldexp((MS_ROUND((frexp(dValue, &nExp) - 0.5f) * 2.0f * FACTORf) / FACTORf) / 2.0f + 0.5f, nExp);}
#define NORMALIZE_ROUND(dValue) {dValue = MS_ROUND(dValue*FACTOR)/FACTOR;}
#define NORMALIZE_ROUND_F(dValue) {dValue = MS_ROUND(dValue*FACTORf)/FACTORf;}

//Числа >= счиатются бесконечностью при поиске по экстентам
#define CS_INFD_POS 1e15;
#define CS_INFD_NEG -1e15;

#define GetBValueFromARGB(argb)      (LOBYTE(argb))
#define GetGValueFromARGB(argb)      (LOBYTE(((WORD)(argb)) >> 8))
#define GetRValueFromARGB(argb)      (LOBYTE((argb)>>16))
#define GetAValueFromARGB(argb)      (LOBYTE((argb)>>24))
#define INT_ARGB(a,r,g,b) \
	((int)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

#ifdef _WIN64
#define  idx_t __int64
#else
#define  idx_t int
#endif

//---------DEFINED OPERATIONS------------
#define DISTSQR(v1,v2) \
	(v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y)+(v1.z-v2.z)*(v1.z-v2.z)

#define CROSS(dest,v1,v2) \
	dest.x=v1.y*v2.z-v1.z*v2.y; \
	dest.y=v1.z*v2.x-v1.x*v2.z; \
	dest.z=v1.x*v2.y-v1.y*v2.x; 

#define DOT(v1,v2) (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z)

#define SUB(dest,v1,v2) \
	dest.x=v1.x-v2.x; \
	dest.y=v1.y-v2.y; \
	dest.z=v1.z-v2.z; 

#define FINDMINMAX(x0,x1,x2,min,max) \
	min = max = x0;   \
	if(x1<min) min=x1;\
	if(x1>max) max=x1;\
	if(x2<min) min=x2;\
	if(x2>max) max=x2;

#define ADDTOMAXMIN(value,max,min) \
	if(value>max)max = value;\
	if(value<min)min = value;
//--------------------------------------

#define CSVECTORD3_EPS 1e-8f //используется и для double и для float
#define ZERO_TOLERANCE_F 1e-06f
#define ZERO_TOLERANCE_SQR_F 1e-03f
#define ACAD_TOLERANCE 1e-6
#define ACAD_SPLIT_TOLERANCE 1e-3
#define CS_PI 3.14159265358979323846264338327950288

#define ASSERT_UNIT_LENGTH(vt) MS3DTYPES_ASSERT(fabs(vt.Length() - 1.0f) < ZERO_TOLERANCE_F)
#define CHECK_VECTOR_INVALID(vt) (_finite(vt.x)==0 || vt.x>1e20 || vt.x<-1e20 || _finite(vt.y)==0 || vt.y>1e20 || vt.y<-1e20 || _finite(vt.z)==0 || vt.z>1e20 || vt.z<-1e20)

//для безопасности приводить структуры точек в массивы точек необходимо, используя следующие определения:
//это позволит осуществить проверку на double или float
#ifdef DEBUG
//Conversion with type check
//to float pointer (from vector)
#define toPf(vt) ((float*)PointFn::ConvertToVoidWithCheckFloat(vt))
//to double pointer (from vector)
#define toPd(vt) ((double*)PointFn::ConvertToVoidWithCheckDouble(vt))
//to float pointer (from vector pointer)
#define toPfP(vt) ((float*)PointFn::ConvertToVoidWithCheckFloatP(vt))
//to double pointer (from vector pointer)
#define toPdP(vt) ((double*)PointFn::ConvertToVoidWithCheckDoubleP(vt))
//from double pointer to CSVECTORD3
#define fromPdP(vt) PointFn::ConvertTo64VecWithCheckDoubleP(vt)
//from float pointer to CSVECTOR3
#define fromPfP(vt) PointFn::ConvertTo32VecWithCheckDoubleP(vt)
#else
//to float pointer (from vector)
#define toPf(vt) ((float*)&(vt))
//to double pointer (from vector)
#define toPd(vt) ((double*)&(vt))
//to float pointer (from vector pointer)
#define toPfP(vt) ((float*)(vt))
//to double pointer (from vector pointer)
#define toPdP(vt) ((double*)(vt))
//from double pointer to CSVECTORD3
#define fromPdP(vt) ((CSVECTORD3*)(vt))
//from float pointer to CSVECTOR3
#define fromPfP(vt) ((CSVECTOR3*)(vt))
#endif

//Преобразование AcGeVector3d или любого другого вектора из double[3] в ссылку на CSVECTORD3 - CSVECTORD3&
#define MS_MAKE_VTG_REF(anyVectorD3) (*((CSVECTORD3*)&anyVectorD3))
//Преобразование AcGeVector3d или любого другого вектора из double[3] в ссылку на CSPOINTD - CSPOINTD&
#define MS_MAKE_PTG_REF(anyVectorD3) (*((CSPOINTD*)&anyVectorD3))

//--------------------------
// 3D Vector
//--------------------------
typedef struct tagCSVECTOR3
{
public:
	tagCSVECTOR3()
	{
		x = 0;
		y = 0;
		z = 0;
	};
	tagCSVECTOR3( FLOAT fX, FLOAT fY, FLOAT fZ )
	{
		x = fX;
		y = fY;
		z = fZ;
	};

	void Set(FLOAT fX, FLOAT fY, FLOAT fZ)
	{
		x = fX;
		y = fY;
		z = fZ;
	}

#ifdef _VIEWERCOMP

	tagCSVECTOR3(const FXMVECTOR vec)
	{
		Set(vec);
	}
	tagCSVECTOR3(const XMFLOAT3 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	void Set(const FXMVECTOR vec)
	{
		XMStoreFloat3((XMFLOAT3*)this, vec);		
	}

	XMVECTOR XMVector3() const
	{
		return XMLoadFloat3((XMFLOAT3*)this);
	}

	XMVECTOR XMVector3(float fw) const
	{
		return XMLoadFloat4(&this->XMFloat4(fw));
	}

	XMFLOAT3 XMFloat3() const
	{
		return *((XMFLOAT3*)this);
	}
	XMFLOAT4 XMFloat4(float fw = 0.0f) const
	{
		return XMFLOAT4(x, y, z, fw);		
	}
#endif
	// binary operators
	BOOL operator == ( const tagCSVECTOR3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
	BOOL operator != ( const tagCSVECTOR3& other) const
	{
		return x != other.x || y != other.y || z != other.z;
	}
	BOOL operator < ( const tagCSVECTOR3& other) const
	{
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		return z < other.z;
	}

	CSHASH_TYPE GetHash() const
	{
		return ((-4987452+CSHASH_TYPE(x))*15+CSHASH_TYPE(y))*41+CSHASH_TYPE(z);
	}

	//Both must be UNIT vectors!
	float AngleTo(const tagCSVECTOR3& vtOther) const
	{
		MS3DTYPES_ASSERT(fabs(Length() - 1.0f) < ZERO_TOLERANCE_F);
		MS3DTYPES_ASSERT(fabs(vtOther.Length() - 1.0f) < ZERO_TOLERANCE_F);

		float fDot = Dot(vtOther);
		if (fDot < -1.0f)
			fDot = -1.0f;
		else if (fDot > 1.0f)
			fDot = 1.0f;
		return (float)acos(fDot);
	}

	tagCSVECTOR3 operator + (const tagCSVECTOR3& vtOther) const
	{
		return tagCSVECTOR3(x + vtOther.x, y + vtOther.y, z + vtOther.z);
	}

	void operator += (const tagCSVECTOR3& vtOther)
	{
		x += vtOther.x;
		y += vtOther.y;
		z += vtOther.z;
	}

	void operator -= (const tagCSVECTOR3& vtOther)
	{
		x -= vtOther.x;
		y -= vtOther.y;
		z -= vtOther.z;
	}

	tagCSVECTOR3 operator - (const tagCSVECTOR3& vtOther) const
	{
		return tagCSVECTOR3(x - vtOther.x, y - vtOther.y, z - vtOther.z);
	}

	tagCSVECTOR3 operator- () const {return tagCSVECTOR3(-x, -y, -z);}

	operator tagCSVECTOR3* () {return this;}	

	tagCSVECTOR3 tagCSVECTOR3::operator * (float fVal) const
	{
		return tagCSVECTOR3(x * fVal, y * fVal, z * fVal);
	}

	void operator *= (FLOAT fVal)
	{
		x *= fVal;
		y *= fVal;
		z *= fVal;
	}

	tagCSVECTOR3 operator / ( FLOAT fVal) const
	{
		return tagCSVECTOR3(x / fVal, y / fVal, z / fVal);
	}

	bool IsZeroLength() const
	{
		return fabs(x) + fabs(y) + fabs(z) < CSVECTORD3_EPS;
	}

	bool IsEqualEps(const tagCSVECTOR3& vtOther, float fEpsilon = CSVECTORD3_EPS) const
	{
		return !(fabs(x - vtOther.x) > fEpsilon ||
			fabs(y - vtOther.y) > fEpsilon ||	
			fabs(z - vtOther.z) > fEpsilon);
	}

	bool IsValid()
	{
		return x < 1e10f && x > -1e10f &&
			y < 1e10f && y > -1e10f &&
			z < 1e10f && z > -1e10f;
	}

	float DistanceSqr(tagCSVECTOR3 pt2) const
	{
		pt2.x -= x;
		pt2.y -= y;
		pt2.z -= z;
		return pt2.x*pt2.x + pt2.y*pt2.y + pt2.z*pt2.z;
	}

	float SquaredLength() const
	{
		return x*x + y*y + z*z;
	}

	float Length() const
	{
		return (float)sqrt(x*x + y*y + z*z);
	}

	void Inverse()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	float Normalize()
	{
		float length = Length();

		if (length > CSVECTORD3_EPS)
		{
			float invLength = 1.0f/length;
			x *= invLength;
			y *= invLength;
			z *= invLength;
		}
		else
		{
			length = 0.0f;
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		return length;
	}

	//this must be unit vector
	tagCSVECTOR3 PerpVector() const
	{
		//If the absolute values of the X and Y components are each less than 1/64, then:
		//orthoVec.x is set to vec.z orthoVec.y is set to 0.0 orthoVec.z is set to -vec.x
		//Otherwise: orthoVec.x is set to -vec.y orthoVec.y is set to vec.x orthoVec.z is set to 0.0 
		MS3DTYPES_ASSERT(fabs(Length() - 1.0f) < ZERO_TOLERANCE_F);
		if (fabs(x) < 1.0f/64.0f && fabs(y) < 1.0f/64.0f)
			return tagCSVECTOR3(z, 0.0f, -x);
		return tagCSVECTOR3(-y, x, 0.0f);
	}

	float Dot(const tagCSVECTOR3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	tagCSVECTOR3 Cross(const tagCSVECTOR3& vec) const
	{
		return tagCSVECTOR3
			(
			y*vec.z - z*vec.y,
			z*vec.x - x*vec.z,
			x*vec.y - y*vec.x
			);
	}

	// This must be a nonzero vector. The output is an orthonormal basis
	// {U,V,THIS}.  THIS is going to be normalized by this function.  If you know
	// THIS is already unit length, use GenerateComplementBasis to compute U
	// and V.
	void GenerateOrthonormalBasis (tagCSVECTOR3& u, tagCSVECTOR3& v)
	{
		Normalize();
		GenerateComplementBasis(u, v);
	}

	//----------------------------------------------------------------------------
	// THIS must be a unit-length vector. The output vectors {U,V} are
	// unit length and mutually perpendicular, and {U,V,W} is an orthonormal
	// basis.
	void GenerateComplementBasis (tagCSVECTOR3& u, tagCSVECTOR3& v) const
	{
		MS3DTYPES_ASSERT(fabs(Length() - 1.0f) < ZERO_TOLERANCE_F);

		float invLength;

		if (fabs(x) >= fabs(y))
		{
			// x or z is the largest magnitude component, swap them
			invLength = (float)sqrt(x*x + z*z);
			if (invLength != 0.0f)
				invLength = 1.0f / invLength;
			else
			{MS3DTYPES_ASSERT(false);}
			u.x = -z*invLength;
			u.y = 0.0f;
			u.z = +x*invLength;
			v.x = y*u.z;
			v.y = z*u.x - x*u.z;
			v.z = -y*u.x;
		}
		else
		{
			// y or z is the largest magnitude component, swap them		
			invLength = (float)sqrt(y*y + z*z);
			if (invLength != 0.0f)
				invLength = 1.0f / invLength;
			else
			{MS3DTYPES_ASSERT(false);}
			u.x = 0.0f;
			u.y = +z*invLength;
			u.z = -y*invLength;
			v.x = y*u.z - z*u.y;
			v.y = -x*u.z;
			v.z = x*u.y;
		}
	}

	float x;
	float y;
	float z;
} CSVECTOR3, CSPOINT;

//--------------------------
// 3D Vector
//--------------------------
typedef struct CSVECTOR4
{
public:
	CSVECTOR4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	};
	CSVECTOR4( FLOAT fX, FLOAT fY, FLOAT fZ, FLOAT fW )
	{
		x = fX;
		y = fY;
		z = fZ;
		w = fW;
	};	

	CSVECTOR4(const CSVECTOR3& vt3, FLOAT fW )
	{
		x = vt3.x;
		y = vt3.y;
		z = vt3.z;
		w = fW;
	};	

	void Set(FLOAT fX, FLOAT fY, FLOAT fZ, FLOAT fW)
	{
		x = fX;
		y = fY;
		z = fZ;
		w = fW;
	}

	CSVECTOR3 GetVector3()
	{
		return CSVECTOR3(x, y, z);
	}

	// binary operators
	BOOL operator == ( const CSVECTOR4& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	BOOL operator != ( const CSVECTOR4& other) const
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}
	BOOL operator < ( const CSVECTOR4& other) const
	{
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		if (z != other.z)
			return z < other.z;
		return w < other.w;
	}

	CSVECTOR4 operator + (const CSVECTOR4& vtOther) const
	{
		return CSVECTOR4(x + vtOther.x, y + vtOther.y, z + vtOther.z, w + vtOther.w);
	}

	void operator += (const CSVECTOR4& vtOther)
	{
		x += vtOther.x;
		y += vtOther.y;
		z += vtOther.z;
		w += vtOther.w;
	}

	void operator -= (const CSVECTOR4& vtOther)
	{
		x -= vtOther.x;
		y -= vtOther.y;
		z -= vtOther.z;
		w -= vtOther.w;
	}

	CSVECTOR4 operator - (const CSVECTOR4& vtOther) const
	{
		return CSVECTOR4(x - vtOther.x, y - vtOther.y, z - vtOther.z, w - vtOther.w);
	}

	CSVECTOR4 CSVECTOR4::operator * (float fVal) const
	{
		return CSVECTOR4(x * fVal, y * fVal, z * fVal, w * fVal);
	}

	void operator *= (FLOAT fVal)
	{
		x *= fVal;
		y *= fVal;
		z *= fVal;
		w *= fVal;
	}

	CSVECTOR4 operator / ( FLOAT fVal) const
	{
		return CSVECTOR4(x / fVal, y / fVal, z / fVal, w / fVal);
	}


	bool IsEqualEps(const CSVECTOR4& vtOther, float fEpsilon = CSVECTORD3_EPS) const
	{
		return !(fabs(x - vtOther.x) > fEpsilon ||
			fabs(y - vtOther.y) > fEpsilon ||	
			fabs(z - vtOther.z) > fEpsilon ||	
			fabs(w - vtOther.w) > fEpsilon);
	}

	float x;
	float y;
	float z;
	float w;
} CSVECTOR4;

//--------------------------
// 3D Vector Double
//--------------------------
typedef struct CSVECTORD3
{
public:
	CSVECTORD3()
	{
		x = 0;
		y = 0;
		z = 0;
	};
	CSVECTORD3( double fX, double fY, double fZ )
	{
		x = fX;
		y = fY;
		z = fZ;
	};

	CSVECTORD3(const CSVECTOR3 &ptF)
	{
		x = (double)ptF.x;
		y = (double)ptF.y;
		z = (double)ptF.z;
	};

	void Set(double fX, double fY, double fZ)
	{
		x = fX;
		y = fY;
		z = fZ;
	}

#ifdef _VIEWERCOMP
	void Set(const FXMVECTOR vec)
	{
		XMFLOAT3 f;
		XMStoreFloat3(&f, vec);
		x = f.x;
		y = f.y;
		z = f.z;
	}
#endif
	void Set(const CSVECTOR3 &ptF)
	{
		x = (double)ptF.x;
		y = (double)ptF.y;
		z = (double)ptF.z;
	}

	bool IsEqualEps(const CSVECTORD3& vtOther, double fEpsilon = CSVECTORD3_EPS) const
	{
		return !(fabs(x - vtOther.x) > fEpsilon ||
			fabs(y - vtOther.y) > fEpsilon ||	
			fabs(z - vtOther.z) > fEpsilon);
	}

	bool IsEqual(const CSVECTORD3 &other, double fEps = COMPARE_FLOATS_EPS) const
	{
		return (fabs(x - other.x) < fEps) &&
			(fabs(y - other.y) < fEps) &&
			(fabs(z - other.z) < fEps);
	}

	void Inverse()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	double Dot(const CSVECTORD3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	CSVECTORD3 Cross(const CSVECTORD3& vec) const
	{
		return CSVECTORD3
			(
			y*vec.z - z*vec.y,
			z*vec.x - x*vec.z,
			x*vec.y - y*vec.x
			);
	}

	CSVECTOR3 To32bitVector() const
	{
		return CSVECTOR3((float)x, (float)y, (float)z);
	}

	CSVECTOR3 To32bitVector(const CSVECTOR3& vtMove) const
	{
		return CSVECTOR3((float)(x + vtMove.x), (float)(y  + vtMove.y), (float)(z  + vtMove.z));
	}

	CSVECTOR3 To32bitVector(const CSVECTORD3& vtMove) const
	{
		return CSVECTOR3((float)(x + vtMove.x), (float)(y  + vtMove.y), (float)(z  + vtMove.z));
	}

	double DistanceSqr(CSVECTORD3 pt2) const
	{
		pt2.x -= x;
		pt2.y -= y;
		pt2.z -= z;
		return pt2.x*pt2.x + pt2.y*pt2.y + pt2.z*pt2.z;
	}

	//Оба вектора должны быть единичной длины!!!
	double AngleTo(const CSVECTORD3& vtOther) const
	{
		MS3DTYPES_ASSERT(fabs(Length() - 1.0) < ZERO_TOLERANCE_F);
		MS3DTYPES_ASSERT(fabs(vtOther.Length() - 1.0) < ZERO_TOLERANCE_F);

		double fDot = Dot(vtOther);
		if (fDot < -1.0)
			fDot = -1.0;
		else if (fDot > 1.0)
			fDot = 1.0;
		return acos(fDot);
	}

	double Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	double SquaredLength() const
	{
		return x*x + y*y + z*z;
	}

	double Normalize()
	{
		double length = Length();

		if (length > CSVECTORD3_EPS)
		{
			double invLength = 1.0/length;
			x *= invLength;
			y *= invLength;
			z *= invLength;
		}
		else
		{
			length = 0.0;
			x = 0.0;
			y = 0.0;
			z = 0.0;
		}

		return length;
	}

	//this must be unit vector
	CSVECTORD3 PerpVector() const
	{
		//If the absolute values of the X and Y components are each less than 1/64, then:
		//orthoVec.x is set to vec.z orthoVec.y is set to 0.0 orthoVec.z is set to -vec.x
		//Otherwise: orthoVec.x is set to -vec.y orthoVec.y is set to vec.x orthoVec.z is set to 0.0 
		MS3DTYPES_ASSERT(fabs(Length() - 1.0) < ZERO_TOLERANCE_F);
		if (fabs(x) < 1.0/64.0 && fabs(y) < 1.0/64.0)
			return CSVECTORD3(z, 0.0, -x);
		return CSVECTORD3(-y, x, 0.0);
	}

	// This must be a nonzero vector. The output is an orthonormal basis
	// {U,V,THIS}.  THIS is going to be normalized by this function.  If you know
	// THIS is already unit length, use GenerateComplementBasis to compute U
	// and V.
	void GenerateOrthonormalBasis (CSVECTORD3& u, CSVECTORD3& v)
	{
		Normalize();
		GenerateComplementBasis(u, v);
	}

	//----------------------------------------------------------------------------
	// THIS must be a unit-length vector. The output vectors {U,V} are
	// unit length and mutually perpendicular, and {U,V,W} is an orthonormal
	// basis.
	void GenerateComplementBasis (CSVECTORD3& u, CSVECTORD3& v) const
	{
		MS3DTYPES_ASSERT(fabs(Length() - 1.0f) < ZERO_TOLERANCE_F);

		double invLength;

		if (fabs(x) >= fabs(y))
		{
			// x or z is the largest magnitude component, swap them
			invLength = sqrt(x*x + z*z);
			if (invLength != 0.0f)
				invLength = 1.0f / invLength;
			else
			{MS3DTYPES_ASSERT(false);}
			u.x = -z*invLength;
			u.y = 0.0f;
			u.z = +x*invLength;
			v.x = y*u.z;
			v.y = z*u.x - x*u.z;
			v.z = -y*u.x;
		}
		else
		{
			// y or z is the largest magnitude component, swap them		
			invLength = sqrt(y*y + z*z);
			if (invLength != 0.0f)
				invLength = 1.0f / invLength;
			else
			{MS3DTYPES_ASSERT(false);}
			u.x = 0.0f;
			u.y = +z*invLength;
			u.z = -y*invLength;
			v.x = y*u.z - z*u.y;
			v.y = -x*u.z;
			v.z = x*u.y;
		}
	}


	operator CSVECTORD3* () {return this;}

	// binary operators
	BOOL operator == ( const CSVECTORD3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
	BOOL operator != ( const CSVECTORD3& other) const
	{
		return x != other.x || y != other.y || z != other.z;
	}

	bool operator < ( const CSVECTORD3& other) const
	{
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		return z < other.z;
	}

	CSVECTORD3 operator + (const CSVECTORD3& vtOther) const
	{
		return CSVECTORD3(x + vtOther.x, y + vtOther.y, z + vtOther.z);
	}

	CSVECTORD3 operator + (const CSVECTOR3& vtOther) const
	{
		return CSVECTORD3(x + vtOther.x, y + vtOther.y, z + vtOther.z);
	}

	void operator += (const CSVECTORD3& vtOther)
	{
		x += vtOther.x;
		y += vtOther.y;
		z += vtOther.z;
	}

	void operator += (const CSVECTOR3& vtOther)
	{
		x += vtOther.x;
		y += vtOther.y;
		z += vtOther.z;
	}

	void operator -= (const CSVECTORD3& vtOther)
	{
		x -= vtOther.x;
		y -= vtOther.y;
		z -= vtOther.z;
	}

	void operator -= (const CSVECTOR3& vtOther)
	{
		x -= vtOther.x;
		y -= vtOther.y;
		z -= vtOther.z;
	}

	void operator *= (double fFactor)
	{
		x *= fFactor;
		y *= fFactor;
		z *= fFactor;
	}

	CSVECTORD3 operator - (const CSVECTORD3& vtOther) const
	{
		return CSVECTORD3(x - vtOther.x, y - vtOther.y, z - vtOther.z);
	}

	CSVECTORD3 operator - (const CSVECTOR3& vtOther) const
	{
		return CSVECTORD3(x - vtOther.x, y - vtOther.y, z - vtOther.z);
	}

	CSVECTORD3 operator * ( double fVal) const
	{
		return CSVECTORD3(x * fVal, y * fVal, z * fVal);
	}

	CSVECTORD3 operator / ( double fVal) const
	{
		return CSVECTORD3(x / fVal, y / fVal, z / fVal);
	}

	bool IsZeroLength() const
	{
		return fabs(x) + fabs(y) + fabs(z) < 0.000000001;
	}

	CSVECTORD3 operator -() const
	{
		return CSVECTORD3(-x, -y, -z);
	}

	CSHASH_TYPE GetHash() const
	{
		return ((-4987452+CSHASH_TYPE(x))*15+CSHASH_TYPE(y))*41+CSHASH_TYPE(z);
	}

	bool IsLess(const CSVECTORD3 &other, double fEps = COMPARE_FLOATS_EPS) const
	{
		if (fabs(x - other.x) > fEps)
			return x < other.x;
		if (fabs(y - other.y) > fEps)
			return y < other.y;
		if (fabs(z - other.z) > fEps)
			return z < other.z;
		return false; //Equals
	}

	//TODO: write this Angle method
	// 	Standard_Real gp_Dir::AngleWithRef (const gp_Dir& Other,
	// 		const gp_Dir& Vref) const
	// 	{
	// 		Standard_Real Ang;
	// 		gp_XYZ XYZ = coord.Crossed (Other.coord);
	// 		Standard_Real nCos = coord.Dot(Other.coord);
	// 		Standard_Real nSin   = XYZ.Modulus ();
	// 		if (nCos > -0.70710678118655 && nCos < 0.70710678118655)
	// 			Ang =  acos (nCos);
	// 		else {
	// 			if(nCos < 0.0)  Ang = M_PI - asin (nSin);
	// 			else               Ang =      asin (nSin);
	// 		}
	// 		if (XYZ.Dot (Vref.coord) >= 0.0)  return  Ang;
	// 		else                              return -Ang;
	// 	} 

	//TODO: write this Angle method
	// 	Standard_Real gp_Dir::Angle (const gp_Dir& Other) const
	// 	{
	// 		//    Commentaires :
	// 		//    Au dessus de 45 degres l'arccos donne la meilleur precision pour le
	// 		//    calcul de l'angle. Sinon il vaut mieux utiliser l'arcsin.
	// 		//    Les erreurs commises sont loin d'etre negligeables lorsque l'on est
	// 		//    proche de zero ou de 90 degres.
	// 		//    En 3d les valeurs angulaires sont toujours positives et comprises entre
	// 		//    0 et PI
	// 		Standard_Real nCos = coord.Dot (Other.coord);
	// 		if (nCos > -0.70710678118655 && nCos < 0.70710678118655)
	// 			return acos (nCos);
	// 		else {
	// 			Standard_Real nSin = (coord.Crossed (Other.coord)).Modulus ();
	// 			if(nCos < 0.0)  return M_PI - asin (nSin);
	// 			else               return      asin (nSin);
	// 		}
	// 	}


	double x;
	double y;
	double z;
} CSVECTORD3, CSPOINTD;

//--------------------------
// 3D Plane
//--------------------------
typedef struct CSPLANE
{
	CSVECTOR3 vtNormal; // normal (A, B, C)
	float fDist; //distance to origin
} CSPLANE;

//--------------------------
// Pyramid right, left, bottom, top, far, near planes
//--------------------------
typedef struct CSFRUSTRUM
{
	CSPLANE planes[6];
} CSFRUSTRUM;

//--------------------------
// 2D Vector
//--------------------------
template<class TYPE> 
struct CSVECTOR2templ
{
public:
	CSVECTOR2templ() {x = 0; y = 0;}
	CSVECTOR2templ(TYPE fX, TYPE fY) {x = fX; y = fY;}

	void Set(TYPE fX, TYPE fY) {x = fX; y = fY;}

	CSVECTOR2templ operator + (const CSVECTOR2templ& vtOther) const
	{
		return CSVECTOR2templ(x + vtOther.x, y + vtOther.y);
	}

	CSVECTOR2templ operator - (const CSVECTOR2templ& vtOther) const
	{
		return CSVECTOR2templ(x - vtOther.x, y - vtOther.y);
	}

	void operator += (const CSVECTOR2templ& vtOther)
	{
		x += vtOther.x;
		y += vtOther.y;
	}

	void operator -= (const CSVECTOR2templ& vtOther)
	{
		x -= vtOther.x;
		y -= vtOther.y;
	}

	CSVECTOR2templ operator * ( TYPE fVal) const
	{
		return CSVECTOR2templ(x * fVal, y * fVal);
	}

	void operator *= (TYPE fFactor)
	{
		x *= fFactor;
		y *= fFactor;
	}

	CSVECTOR2templ operator / ( TYPE fVal) const
	{
		return CSVECTOR2templ(x / fVal, y / fVal);
	}

	void operator /= (TYPE fFactor)
	{
		x /= fFactor;
		y /= fFactor;
	}

	//Makes Y from X in right handed coord system
	CSVECTOR2templ PerpVector() const
	{
		return CSVECTOR2templ(-y, x);
	}

	//Makes Y from X in left handed coord system
	CSVECTOR2templ PerpVectorReverse() const
	{
		return CSVECTOR2templ(y, -x);
	}

	//dot product
	TYPE operator & (const CSVECTOR2templ& vtOther) const
	{
		return x * vtOther.x + y * vtOther.y;
	}

	TYPE Dot(const CSVECTOR2templ& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	TYPE Cross(const CSVECTOR2templ& vec) const
	{
		return x * vec.y - y * vec.x;
	}

	TYPE QuadLength() const
	{
		return x*x + y*y;
	}

	TYPE AngleTo(const CSVECTOR2templ& vtOther) const
	{
		const TYPE nThisLen = Length();
		const TYPE nOtherLen = vtOther.Length();
		if (nThisLen <= (TYPE)ZERO_TOLERANCE_F || nOtherLen <= (TYPE)ZERO_TOLERANCE_F)
			return (TYPE)0.0; //no angle!

		const TYPE nDet = nThisLen * nOtherLen;
		const TYPE nCos = Dot(vtOther) / nDet;
		const TYPE nSin = Cross(vtOther) / nDet;
		if (nCos > (TYPE)-0.70710678118655 && nCos < (TYPE)0.70710678118655)
		{
			if (nSin > (TYPE)0.0)
				return acos(nCos);
			else
				return -acos(nCos); 
		}
		else
		{
			if (nCos > (TYPE)0.0) 
				return asin(nSin);
			else
			{ 
				if (nSin > (TYPE)0.0)
					return (TYPE)(M_PI - asin(nSin));
				else             
					return (TYPE)(-M_PI - asin(nSin));
			}
		}  
	}

	CSHASH_TYPE GetHash()
	{
		//учитывается только целая часть!
		return idx_t(x)*75 + idx_t(y)*14 + 982;
	}

	bool IsEqualEps(const CSVECTOR2templ& vtOther, TYPE fEpsilon = CSVECTORD3_EPS) const
	{
		return !(fabs(x - vtOther.x) > fEpsilon ||
			fabs(y - vtOther.y) > fEpsilon);
	}

	// binary operators
	BOOL operator == (const CSVECTOR2templ& other) const
	{
		return x == other.x && y == other.y;
	}
	BOOL operator != (const CSVECTOR2templ& other) const
	{
		return x != other.x || y != other.y;
	}

	bool operator < (const CSVECTOR2templ& other) const
	{
		if (x != other.x)
			return x < other.x;
		return y < other.y;
	}

	TYPE Length() const
	{
		return sqrt(x*x + y*y);
	}

	bool IsZeroLength() const
	{
		return fabs(x) + fabs(y) < (TYPE)0.000000001;
	}

	bool IsParallelTo(CSVECTOR2templ vt2, TYPE fEpsilon =  ZERO_TOLERANCE_SQR_F) const
	{
		double d = fabs(Cross(vt2));
		return d < fEpsilon;
	}

	bool IsPerpendicularTo(CSVECTOR2templ vt2, TYPE fEpsilon =  ZERO_TOLERANCE_SQR_F) const
	{
		return fabs(x*vt2.x + y * vt2.y) < fEpsilon;
	}

	CSVECTOR2templ operator-() const
	{
		return CSVECTOR2templ(-x, -y);
	}

	TYPE DistanceSqr(CSVECTOR2templ pt2) const
	{
		pt2.x -= x;
		pt2.y -= y;
		return pt2.x*pt2.x + pt2.y*pt2.y;
	}

	TYPE DistanceTo(CSVECTOR2templ pt2) const
	{
		pt2.x -= x;
		pt2.y -= y;
		return sqrt(pt2.x*pt2.x + pt2.y*pt2.y);
	}

	TYPE Normalize()
	{
		double length = Length(); //anyway double is here

		if (length > CSVECTORD3_EPS)
		{
			double invLength = 1.0/length;
			x = (TYPE) (x *invLength);
			y = (TYPE) (y *invLength);
		}
		else
		{
			length = 0.0;
			x = (TYPE)0.0;
			y = (TYPE)0.0;
		}

		return (TYPE)length;
	}

	TYPE x, y;
};

typedef CSVECTOR2templ<float> CSVECTOR2;
typedef CSVECTOR2templ<double> CSVECTORD2;
typedef CSVECTOR2templ<float> CSPOINT2;
typedef CSVECTOR2templ<double> CSPOINTD2;

#define PT2DtoPT2(pt2d) CSPOINT2((float)pt2d.x, (float)pt2d.y)

class PointFn
{
public:
	static CSPOINT2 makePT2(const CSPOINTD2& pt2d) {return CSPOINT2((float)pt2d.x, (float)pt2d.y);}

#ifdef DEBUG
	static void* ConvertToVoidWithCheckFloat(const CSPOINT& pt) {return (void*)&pt;}
	static void* ConvertToVoidWithCheckDouble(const CSPOINTD& pt) {return (void*)&pt;}
	static void* ConvertToVoidWithCheckFloatP(const CSPOINT* pt) {return (void*)pt;}
	static void* ConvertToVoidWithCheckDoubleP(const CSPOINTD* pt) {return (void*)pt;}
	static void* ConvertToVoidWithCheckFloat(const CSPOINT2& pt) {return (void*)&pt;}
	static void* ConvertToVoidWithCheckDouble(const CSPOINTD2& pt) {return (void*)&pt;}
	static void* ConvertToVoidWithCheckFloatP(const CSPOINT2* pt) {return (void*)pt;}
	static void* ConvertToVoidWithCheckDoubleP(const CSPOINTD2* pt) {return (void*)pt;}
	static CSVECTORD3* ConvertTo64VecWithCheckDoubleP(double *pBuff) {return (CSVECTORD3*)pBuff;}
	static const CSVECTORD3* ConvertTo64VecWithCheckDoubleP(const double *pBuff) {return (const CSVECTORD3*)pBuff;}
	static CSVECTOR3* ConvertTo32VecWithCheckDoubleP(float *pBuff) {return (CSVECTOR3*)pBuff;}
	static const CSVECTOR3* ConvertTo32VecWithCheckDoubleP(const float *pBuff) {return (const CSVECTOR3*)pBuff;}
#endif
};

// Material properties per mesh subset
#define MATERIAL_INDEX_BY_LAYER_ALPHA 7777.7f //специальный флаг цвета "По слою" (цвет передаётся извне при загрузке)
#define MATERIAL_INDEX_BY_ENTITY_ALPHA 8888.8f //специальный флаг цвета "По блоку" (цвет передаётся извне при загрузке)
#define MATERIAL_INDEX_BY_LAYER 7777
#define MATERIAL_INDEX_BY_ENTITY 8888
typedef struct CCSMaterial
{
public:
	WCHAR strName[20];

	CSVECTOR3 vAmbient;
	CSVECTOR3 vDiffuse;
	CSVECTOR3 vSpecular;

	int nShininess;
	float fAlpha;

	bool bSpecular;

	CCSMaterial()
	{
		memset(strName, 0, 20*2);
		bSpecular = false;
		fAlpha = 1.0f;
		nShininess = 0;
	}

	//конструктор материала "по слою" или "по блоку"
	CCSMaterial(bool bByLayer, /*or*/bool bByEntity):fAlpha(0.0)
	{
		strName[0] = 0;
		bSpecular = false;
		if (bByEntity)
			fAlpha = MATERIAL_INDEX_BY_ENTITY_ALPHA;
		if (bByLayer)
			fAlpha = MATERIAL_INDEX_BY_LAYER_ALPHA;
		nShininess = 0;
		vAmbient.Set(0.0f, 0.0f, 0.0f);	
		vDiffuse.Set(0.0f, 0.0f, 0.0f);	
		vSpecular.Set(0.0f, 0.0f, 0.0f);	
	}	

	CCSMaterial(const CSVECTOR3& color)
	{
		memset(strName, 0, 20*2);

		bSpecular = false;
		fAlpha = 1.0f;
		nShininess = 0;
		vAmbient = color;
		vDiffuse = color;
		vSpecular.Set(0.0f, 0.0f, 0.0f);		
	}

	bool IsByLayer() const
	{
		return fAlpha == MATERIAL_INDEX_BY_LAYER_ALPHA;
	}
	bool IsByEntity() const
	{
		return fAlpha == MATERIAL_INDEX_BY_ENTITY_ALPHA;
	}

	int ToARGB() const
	{
		BYTE nA = (BYTE)(fAlpha*255);
		BYTE nR = (BYTE)(vAmbient.x*255);
		BYTE nG = (BYTE)(vAmbient.y*255);
		BYTE nB = (BYTE)(vAmbient.z*255);
		return INT_ARGB(nA, nR, nG, nB);
	}

	void FromARGB(int nARGB)
	{
		fAlpha = GetAValueFromARGB(nARGB) / 255.0f;
		if (fAlpha < 0.1f || fAlpha > 1.0f)
			fAlpha = 1.0f;

		vAmbient.x = GetRValueFromARGB(nARGB) / 255.0f;
		if (vAmbient.x > 1.0f)
			vAmbient.x = 1.0f;
		else if (vAmbient.x < 0.00001f)
			vAmbient.x = 0.0f;

		vAmbient.y = GetGValueFromARGB(nARGB) / 255.0f;
		if (vAmbient.y > 1.0f)
			vAmbient.y = 1.0f;
		else if (vAmbient.y < 0.00001f)
			vAmbient.y = 0.0f;

		vAmbient.z = GetBValueFromARGB(nARGB) / 255.0f;
		if (vAmbient.z > 1.0f)
			vAmbient.z = 1.0f;
		else if (vAmbient.z < 0.00001f)
			vAmbient.z = 0.0f;		

		vDiffuse = vAmbient;
	}

	bool operator ==(const CCSMaterial& other) const
	{
		return CSDBL_EQUALS(vAmbient.x) &&
			CSDBL_EQUALS(vAmbient.y) &&
			CSDBL_EQUALS(vAmbient.z) &&
			CSDBL_EQUALS(vDiffuse.x) &&
			CSDBL_EQUALS(vDiffuse.y) &&
			CSDBL_EQUALS(vDiffuse.z) &&
			CSDBL_EQUALS(vSpecular.x) &&
			CSDBL_EQUALS(vSpecular.y) &&
			CSDBL_EQUALS(vSpecular.z) &&
			CSDBL_EQUALS(fAlpha);
	}

	bool operator <(const CCSMaterial& other) const
	{
		CSDBL_LESS(vAmbient.x);
		CSDBL_LESS(vAmbient.y);
		CSDBL_LESS(vAmbient.z);
		CSDBL_LESS(vDiffuse.x);
		CSDBL_LESS(vDiffuse.y);
		CSDBL_LESS(vDiffuse.z);
		CSDBL_LESS(vSpecular.x);
		CSDBL_LESS(vSpecular.y);
		CSDBL_LESS(vSpecular.z);
		CSDBL_LESS(fAlpha);
		return false; //Equals
	}

	CSHASH_TYPE GetHash() const
	{
		CSHASH_TYPE nHash = 458;
		CSDBL_HASH(95, idx_t(vAmbient.x*1e4f));
		CSDBL_HASH(85, idx_t(vAmbient.y*1e4f));
		CSDBL_HASH(75, idx_t(vAmbient.z*1e4f));
		CSDBL_HASH(95, idx_t(vDiffuse.x*1e4f));
		CSDBL_HASH(85, idx_t(vDiffuse.y*1e4f));
		CSDBL_HASH(75, idx_t(vDiffuse.z*1e4f));
		CSDBL_HASH(95, idx_t(vSpecular.x*1e4f));
		CSDBL_HASH(85, idx_t(vSpecular.y*1e4f));
		CSDBL_HASH(75, idx_t(vSpecular.z*1e4f));
		CSDBL_HASH(5, idx_t(fAlpha*100.0f));
		return nHash;
	}
	//DB.NET compatible hash
	int GetHashCode()const
	{
		unsigned char color[4];
		color[3] = (unsigned char)(vAmbient.x*255.0);
		color[2] = (unsigned char)(vAmbient.x*255.0);
		color[1] = (unsigned char)(vAmbient.x*255.0);
		color[0] = (unsigned char)(fAlpha*255.0);
		
		return *(int*)color;
	}
} CCSMaterial;

// Vertex format with double
typedef struct CSVERTEXD
{
	CSPOINTD position;
	CSVECTORD3 normal;

	bool operator ==(const CSVERTEXD& other) const
	{
		return position == other.position &&
			normal == other.normal;
	}

	bool operator <(const CSVERTEXD& other) const
	{		
		return position.x <	other.position.x ||
			position.y < other.position.y ||
			position.z < other.position.z;
	}
} CSVERTEXD;

// Vertex format
typedef struct CSVERTEX
{
	CSVERTEX()
	{

	}

	CSVERTEX(const CSPOINT &ptPosition, const CSVECTOR3 &vtNormal)
	{
		position = ptPosition;
		normal = vtNormal;
	}

	CSPOINT position;
	CSVECTOR3 normal;

	bool operator ==(const CSVERTEX& other) const
	{
		return position == other.position &&
			normal == other.normal;
	}

	bool operator <(const CSVERTEX& other) const
	{		
		return position.x <	other.position.x ||
			position.y < other.position.y ||
			position.z < other.position.z;
	}
} CSVERTEX;

//Вершина со сжатой нормалью
typedef struct CSVertexCompressed
{
	CSVertexCompressed()
	{
		memset(vtNormal, 0, sizeof(byte) * 3);
	}

	CSVertexCompressed(const CSPOINT &ptPos, const CSVECTOR3 &vtNorm)
	{
		ptPosition = ptPos;

		//нормаль должна быть единичным вектором
		//MS3DTYPES_ASSERT(fabs(vtNorm.Length()-1.0f) < 1e-5f);
		vtNormal[0] = (byte)((vtNorm.x * 0.5f + 0.5f) * 255.0f);
		vtNormal[1] = (byte)((vtNorm.y * 0.5f + 0.5f) * 255.0f);
		vtNormal[2] = (byte)((vtNorm.z * 0.5f + 0.5f) * 255.0f);
	}

	CSVertexCompressed(const CSPOINT &ptPos, const byte vtNorm[3])
	{
		this->ptPosition = ptPos;
		vtNormal[0] = vtNorm[0];
		vtNormal[1] = vtNorm[1];
		vtNormal[2] = vtNorm[2];
	}

	void SetNormal(const CSVECTOR3& vtNorm)
	{
		//нормаль должна быть единичным вектором
		MS3DTYPES_ASSERT(fabs(vtNorm.Length()-1.0f) < 1e-2f); 
		vtNormal[0] = (byte)((vtNorm.x * 0.5f + 0.5f) * 255.0f);
		vtNormal[1] = (byte)((vtNorm.y * 0.5f + 0.5f) * 255.0f);
		vtNormal[2] = (byte)((vtNorm.z * 0.5f + 0.5f) * 255.0f);
	}

	static inline void MakeCompressedNormal(const CSVECTOR3& vtNormal, byte vtDestNormal[3])
	{
		MS3DTYPES_ASSERT(fabs(vtNormal.Length()-1.0f) < 1e-2f); 
		vtDestNormal[0] = (byte)((vtNormal.x * 0.5f + 0.5f) * 255.0f);
		vtDestNormal[1] = (byte)((vtNormal.y * 0.5f + 0.5f) * 255.0f);
		vtDestNormal[2] = (byte)((vtNormal.z * 0.5f + 0.5f) * 255.0f);
	}

	static inline CSVECTOR3 GetUncompressedNormal(const byte vtNormal[3])
	{
		return CSVECTOR3(
			2.0f*vtNormal[0]/255.0f-1.0f,
			2.0f*vtNormal[1]/255.0f-1.0f,
			2.0f*vtNormal[2]/255.0f-1.0f);
	}

	CSVECTOR3 GetUncompressedNormal() const 
	{
		return CSVECTOR3(
			2.0f*vtNormal[0]/255.0f-1.0f,
			2.0f*vtNormal[1]/255.0f-1.0f,
			2.0f*vtNormal[2]/255.0f-1.0f);
	}

	void normalizeRound()
	{	
		NORMALIZE_ROUND_F(ptPosition.x);
		NORMALIZE_ROUND_F(ptPosition.y);
		NORMALIZE_ROUND_F(ptPosition.z);
// 		CSVECTOR3 vNormal = GetUncompressedNormal();
// 		NORMALIZE_ROUND_F(vNormal.x);
// 		NORMALIZE_ROUND_F(vNormal.y);
// 		NORMALIZE_ROUND_F(vNormal.z);
// 		SetNormal(vNormal);
	}

	CSPOINT ptPosition;
	byte vtNormal[3];

	bool operator ==(const CSVertexCompressed& other) const
	{
		return ptPosition == other.ptPosition &&
			vtNormal[0] == other.vtNormal[0] &&
			vtNormal[1] == other.vtNormal[1] &&
			vtNormal[2] == other.vtNormal[2];
	}

	bool operator <(const CSVertexCompressed& other) const
	{		
		return ptPosition.x < other.ptPosition.x ||
			ptPosition.y < other.ptPosition.y ||
			ptPosition.z < other.ptPosition.z ||
			vtNormal[0] < other.vtNormal[0] ||
			vtNormal[1] < other.vtNormal[1] ||
			vtNormal[2] < other.vtNormal[2];
	}
} CSVertexCompressed;

typedef struct CSAttributeTableRecord
{
	CSAttributeTableRecord():m_nAttribute(0), m_nFaceStart(0), m_nFaceCount(0){};

	CSAttributeTableRecord(DWORD nAttribute, DWORD nFaceStart, DWORD nFaceCount)
	{
		m_nAttribute = nAttribute;
		m_nFaceStart = nFaceStart;
		m_nFaceCount = nFaceCount;
	}

	void Set(DWORD nAttribute, DWORD nFaceStart, DWORD nFaceCount)
	{
		m_nAttribute = nAttribute;
		m_nFaceStart = nFaceStart;
		m_nFaceCount = nFaceCount;
	}

	DWORD m_nAttribute;
	DWORD m_nFaceStart;
	DWORD m_nFaceCount;
} CSAttributeTableRecord;

//------constants--------
const CSPOINT PT_Origin(0.0f, 0.0f, 0.0f);
const CSVECTOR3 VT_Zero(0.0f, 0.0f, 0.0f);
const CSVECTOR3 VT_X(1.0f, 0.0f, 0.0f);
const CSVECTOR3 VT_Y(0.0f, 1.0f, 0.0f);
const CSVECTOR3 VT_Z(0.0f, 0.0f, 1.0f);

const CSPOINTD PT_OriginD(0, 0, 0);
const CSVECTOR3 VT_ZeroD(0, 0, 0);
const CSVECTORD3 VT_Xd(1, 0, 0);
const CSVECTORD3 VT_Yd(0, 1, 0);
const CSVECTORD3 VT_Zd(0, 0, 1);

const CSPOINTD2 PT_OriginD2(0, 0);
const CSVECTOR2 VT_ZeroD2(0, 0);
const CSVECTORD2 VT_Xd2(1, 0);
const CSVECTORD2 VT_Yd2(0, 1);
//-----------------------

//////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)
//структура описания треугольника поверхности
struct CAABBI
{
	CAABBI() {}

	CAABBI(const CSPOINTD& min, const CSPOINTD& max) :
		ptMin(min), ptMax(max) {}

	CSPOINTD ptMin;
	CSPOINTD ptMax;
};
#pragma pack (pop)
//////////////////////////////////////////////////////////////////////////

#define CS_CURVE_POINT		1 
#define CS_CURVE_POLYLINE	2
#define CS_CURVE_CIRCLE -100 //defined by ptCenter, vtNormal, radius: 3*4+3*4+4 = 28 bytes
#define CS_CURVE_CIRCLE_ARC -101 //defined by ptCenter, vtU, vtV, fArcAngle: 40 bytes. vtU and vtV length is radius

//Dump version 1 header format:
//At the beginning the phrase: "ModelStudio 3D Mesh v." + 5 characters version
//Next goes the version in float format
//Next goes CS3DHeader structure //end offset: 54+4+20 = 78
//Next goes the string size: int and mesh name string
//Then go materials CCSMaterial[]
//Then goes MESH: vertices CSVERTEX[]; index DWORD[]; material index DWORD[]
//And finally curves: points (int(size or type) + defenition(array or type > 0)) CSPOINT[][];
//Then in version below 1.4 material index DWORD[] or above 1.3 CSAttributeTableRecord[nCurvesAttrTableSize]
//if size of curve is negative value - this is TYPE of curve like CS_CURVE_CIRCLE


typedef struct CS3DHeader
{
	DWORD nMaterials;
	DWORD nVertices;
	DWORD nVertIndex;
	DWORD nCurves;
	DWORD nSize; //whole mesh size to allocate memory	
} CS3DHeader;

//Mesh header after version 1.3
typedef struct CS3DHeader3
{
	DWORD nMaterials;
	DWORD nVertices;
	DWORD nVertIndex;
	DWORD nCurves;
	DWORD nSize; //whole mesh size to allocate memory

	bool bHasNormals;
	bool bHasIndex; //the false means what 
	//nVertices==nVertIndex and Vertices are sequential and there are no index data!
	bool bHasFacesMaterialArray; //true =  material index DWORD[]; false = CSAttributeTableRecord[nAttributeTableSize]
	bool bHasVertexReductionMap; //if true there are VertexReduction info after curves
	DWORD nVerticesReduced; //if this is reduced mesh - number of vertices reduced otherwise zero
	DWORD nFacesAttrTableSize;
	DWORD nCurvesAttrTableSize;
	DWORD nCurvesSize; //common size of curves info ("points (size(int) + array) CSPOINT[][]; material table CSAttributeTableRecord[]")
	DWORD nReductionInitVerticesCount;	
} CS3DHeader3;

#define MSM_BLOCK_TYPE_MESH 100 //тип блока - сетка

typedef struct CS3DHeader5
{
	//---BLOCK HEADER---
	//два поля идентификации блока данных находятся в начале каждого блока
	DWORD nBlockSize; //this mesh block size
	WORD nBlockType; //всегда MSM_BLOCK_TYPE_MESH
	//END---BLOCK HEADER---END

	DWORD nMaterials;
	DWORD nVertices;
	DWORD nVertIndex;
	DWORD nFacesAttrTableSize;
	DWORD nEdgeVisibleArraySize;
	DWORD nOsnapPointsArraySize;

	DWORD nCurves;
	DWORD nCurvesSize; //common size of curves info ("points (size(int) + array) CSPOINT[][]; material table CSAttributeTableRecord[]")
	DWORD nCurvesAttrTableSize;

	DWORD nMeshSize; //whole mesh size to allocate memory (with related blocks)
} CS3DHeader5;

typedef struct CS3DHeader6
{
	//---BLOCK HEADER---
	//два поля идентификации блока данных находятся в начале каждого блока
	DWORD nBlockSize; //this mesh block size
	WORD nBlockType; //всегда MSM_BLOCK_TYPE_MESH
					 //END---BLOCK HEADER---END

	DWORD nMaterials;
	DWORD nVertices;
	DWORD nVertIndex;
	DWORD nFacesAttrTableSize;
	DWORD nEdgeVisibleArraySize;
	DWORD nOsnapPointsArraySize;

	//Линейная графика - отдельно
	DWORD nCurvesGraphics;
	DWORD nCurvesGraphicsSize; //common size of curves info ("points (size(int) + array) CSPOINT[][]; material table CSAttributeTableRecord[]")
	DWORD nCurvesGraphicsAttrTableSize;

	DWORD nMeshSize; //whole mesh size to allocate memory (with related blocks)

	//Изолинии
	DWORD nCurvesIsolines;
	DWORD nCurvesIsolinesSize; //common size of curves info ("points (size(int) + array) CSPOINT[][]; material table CSAttributeTableRecord[]")
	DWORD nCurvesIsolinesAttrTableSize;


} CS3DHeader6;


//ver 1.100 - точки храняться в относительных координатах относительно ptMin экстентов
//ver 1.200 - в вершинах нет описания нормалей, нормали подсчитываются после загрузки
//ver 1.300 - Расширеный хэдер с дополнительной информацией
//          - Может не быть "material index DWORD[]" для фэйсов и кривых. Вместо них таблицы материалов с описанием
//            индекса начала, количества фэйсов и номера материала CSAttributeTableRecord[nFacesAttrTableSize]
//          - В конце данных может быть массив с информацией о прогрессивной сетке
//            DWORD[] permutation[nReductionInitVerticesCount], DWORD[] VertexReductionMap[nReductionInitVerticesCount]
//ver 1.400 - Если в типе кривой положительное число, то это полилиния и далее идёт указанное число вершин,
//            если число отрицательно, то это тип кривой и далее идёт определение кривой (размер зависит от типа)
//            также вместо индексного массива материалов кривых используется таблица материалов CSAttributeTableRecord[nCurvesAttrTableSize]
//ver 1.500 - все сетки должны иметь нормали (для авто вычисления нормалей они д.б. (-1.0, -1.0, -1.0)), индексы граней, таблицы материалов для кривых и граней,
//			  вершины теперь с упакованными нормалями (в виде трёх байт) - CSVertexCompressed
//			  индексы граней могут быть массивом WORD[] если вершин меньше чем MAXWORD, иначе индексы DWORD[] как раньше
//			  после массива индексов граней идёт массив видимости рёбер размером nEdgeVisibleArraySize в нём ПОБИТНО записана
//			  видимость рёбер исходящих из вершин в порядке индекса (VertIndex)
//			  Затем идут кривые с их таблицей материалов
//			  Затем идёт массив DWORD[nOsnapPointsArraySize] ссылок на точки привязки, где последний байт - тип точки привязки (24bit+8bit)
//			  Подразумевается, что файл имеет блочную структуру. Каждый блок начинается с nBlockSize, nBlockType
//            Поле nMeshSize содержит размер блока сетки и последующих блоков, связанных с ней (например тексты, картинки и т.д.)
//			  Блочная структура позволяет размещать много сеток в одном файле
//ver 1.600 -Добавлено сжатие MSM LoDetail и XPG

#define MESH_DUMPER_VERSION_OLD 1.5f // не должна превышать MESH_DUMPER_VERSION_ZIP
#define MESH_DUMPER_STRING_OLD _T("ModelStudio 3D Mesh v.1.500") //version must be 5 characters long!


#define MESH_DUMPER_VERSION 2.0f // не должна превышать MESH_DUMPER_VERSION_ZIP
#define MESH_DUMPER_STRING _T("ModelStudio 3D Mesh v.2.000") //version must be 5 characters long!
#define MESH_DUMPER_STRING_SIZE (22 + 5)*2

#define MESH_DUMPER_VERSION_ZIP 2.1f
#define MESH_DUMPER_STRING_ZIP _T("ModelStudio 3D Mesh v.2.100") //version must be 5 characters long!

#define XPG_DUMPER_STRING_ZIP _T("XPGX")
#define XPG_DUMPER_STRING_ZIP_LEN (4*sizeof(TCHAR))

#pragma pack(pop, ms3dtypes)
