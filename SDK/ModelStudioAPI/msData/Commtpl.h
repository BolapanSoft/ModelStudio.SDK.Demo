#if !defined(__commtpl_h)
#define __commtpl_h

#ifdef _WIN64
#define  idx_t __int64
#define NOT_FOUND (-1ll)
#else
#define  idx_t int
#define NOT_FOUND (-1)
#endif

#ifdef _DEBUG
#ifdef _DISABLE_MFC_ASSERT
#include <assert.h>
#define CTPL_ASSERT assert
#else
#define CTPL_ASSERT ASSERT
#endif
#else
#define CTPL_ASSERT(f)     ((void)0)
#endif

#ifdef _CTPL_MEMORY_SAFE_ALLOC_X_
#include <new>

#undef new
#undef delete

enum __formal {
	__f=0,
};


inline void* operator new(size_t sz, __formal a) {
	return ::malloc(sz) ;
}
inline void operator delete(void * p, __formal a) {
	::free(p) ;
}
inline void* operator new[](size_t sz, __formal a){
	return ::malloc(sz) ;
}
inline void operator delete[](void * p, __formal a) {
	::free(p) ;
}

#define __SAFENEW new(__f)
#define __SAFEDEL(p) ::operator delete (p,__f);
#define __SAFEDELV(p) ::operator delete[](p,__f);
#else 

#define __SAFENEW new
#define __SAFEDEL(p) delete (p)
#define __SAFEDELV(p) delete[](p)

#endif



// for file name/line number tracking using DEBUG_NEW


#ifdef _MS_HEAP_CONTROL_
//#define TMP_NEW new
//#define TMP_DELETE delete
//#undef new
//#undef delete
#if _MSC_VER >= 1200
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
#define MS_DECLARE_HEAP_CONTROL public: \
	void* PASCAL operator new(size_t nSize);\
	void* PASCAL operator new(size_t, void* p);\
	void PASCAL operator delete (void *p); \
	void PASCAL operator delete(void* p, void* pPlace);\
	void* PASCAL operator new[] (size_t size); \
	void PASCAL operator delete[] (void *p);\
	void* PASCAL operator new(size_t nSize, LPCSTR lpszFileName, int nLine);\
	void PASCAL operator delete(void *p, LPCSTR lpszFileName, int nLine);

#define MS_IMPLEMENT_HEAP_CONTROL(cls) \
	void* cls::operator new (size_t size){return ::operator new(size); }\
	void* cls::operator new(size_t size, void* p){return ::operator new(size,p); }\
	void cls::operator delete (void *p){::operator delete(p); }\
	void cls::operator delete (void *p,void* pPlace){::operator delete(p,pPlace); }\
	void* cls::operator new[] (size_t size){return ::operator new[](size); } \
	void cls::operator delete[] (void *p){ ::operator delete[] (p); }\
	void* cls::operator new(size_t nSize, LPCSTR lpszFileName, int nLine){return ::operator new[](nSize,lpszFileName,nLine); } \
	void cls::operator delete(void *p, LPCSTR lpszFileName, int nLine){ ::operator delete[] (p,lpszFileName,nLine); } 

#define MS_IMPLEMENT_HEAP_CONTROL_INLINE public: \
	void* operator new (size_t s_){return ::operator new(s_); }\
	void* operator new(size_t s_, void* p){return ::operator new(s_,p); }\
	void operator delete (void *p){::operator delete(p); }\
	void operator delete (void *p,void* pPlace){::operator delete(p,pPlace); }\
	void* operator new[] (size_t s_){return ::operator new[](s_); } \
	void operator delete[] (void *p){ ::operator delete[] (p); } \
	void* operator new(size_t nSize, LPCSTR lpszFileName, int nLine){return ::operator new[](nSize,lpszFileName,nLine); } \
	void operator delete(void *p, LPCSTR lpszFileName, int nLine){ ::operator delete[] (p,lpszFileName,nLine); } 
#else
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
#define MS_DECLARE_HEAP_CONTROL public: \
	void* PASCAL operator new(size_t nSize);\
	void* PASCAL operator new(size_t, void* p);\
	void PASCAL operator delete (void *p); \
	void PASCAL operator delete(void* p, void* pPlace);\
	void* PASCAL operator new[] (size_t size); \
	void PASCAL operator delete[] (void *p);\
	void* PASCAL operator new(size_t nSize, LPCSTR lpszFileName, int nLine);\
	void PASCAL operator delete(void *p, LPCSTR lpszFileName, int nLine);

#define MS_IMPLEMENT_HEAP_CONTROL(cls) \
	void* cls::operator new (size_t size){return ::operator new(size); }\
	void* cls::operator new(size_t size, void* p){return ::operator new(size,p); }\
	void cls::operator delete (void *p){::operator delete(p); }\
	void cls::operator delete (void *p,void* pPlace){::operator delete(p,pPlace); }\
	void* cls::operator new[] (size_t size){return ::operator new[](size); } \
	void cls::operator delete[] (void *p){ ::operator delete[] (p); } \
	void* cls::operator new(size_t nSize, LPCSTR lpszFileName, int nLine){return ::operator new[](nSize,lpszFileName,nLine); } \
	void cls::operator delete(void *p, LPCSTR lpszFileName, int nLine){ ::operator delete[] (p,lpszFileName,nLine); } 

#define MS_IMPLEMENT_HEAP_CONTROL_INLINE public: \
	void* operator new (size_t size){return ::operator new(size); }\
	void* operator new(size_t size, void* p){return ::operator new(size,p); }\
	void operator delete (void *p){::operator delete(p); }\
	void operator delete (void *p,void* pPlace){::operator delete(p,pPlace); }\
	void* operator new[] (size_t size){return ::operator new[](size); } \
	void operator delete[] (void *p){ ::operator delete[] (p); } \
	void* operator new(size_t nSize, LPCSTR lpszFileName, int nLine){return ::operator new[](nSize,lpszFileName,nLine); } \
	void operator delete(void *p, LPCSTR lpszFileName, int nLine){ ::operator delete[] (p,lpszFileName,nLine); } 
#else 
#define MS_DECLARE_HEAP_CONTROL public: \
	void* PASCAL operator new(size_t nSize);\
	void* PASCAL operator new(size_t, void* p);\
	void PASCAL operator delete (void *p); \
	void PASCAL operator delete(void* p, void* pPlace);\
	void* PASCAL operator new[] (size_t size); \
	void PASCAL operator delete[] (void *p);

#define MS_IMPLEMENT_HEAP_CONTROL(cls) \
	void* cls::operator new (size_t size){return ::operator new(size); }\
	void* cls::operator new(size_t size, void* p){return ::operator new(size,p); }\
	void cls::operator delete (void *p){::operator delete(p); }\
	void cls::operator delete (void *p,void* pPlace){::operator delete(p,pPlace); }\
	void* cls::operator new[] (size_t size){return ::operator new[](size); } \
	void cls::operator delete[] (void *p){ ::operator delete[] (p); } 

#define MS_IMPLEMENT_HEAP_CONTROL_INLINE public: \
	void* operator new (size_t size){return ::operator new(size); }\
	void* operator new(size_t size, void* p){return ::operator new(size,p); }\
	void operator delete (void *p){::operator delete(p); }\
	void operator delete (void *p,void* pPlace){::operator delete(p,pPlace); }\
	void* operator new[] (size_t size){return ::operator new[](size); } \
	void operator delete[] (void *p){ ::operator delete[] (p); } 
#endif
#endif
#else
#define MS_DECLARE_HEAP_CONTROL public: \
	void* PASCAL operator new(size_t nSize);\	
void PASCAL operator delete (void *p); \
	void* PASCAL operator new[] (size_t size); \
	void PASCAL operator delete[] (void *p);

#define MS_IMPLEMENT_HEAP_CONTROL(cls) \
	void* cls::operator new (size_t size){return ::operator new(size); }\
	void cls::operator delete (void *p){::operator delete(p); }\
	void* cls::operator new[] (size_t size){return ::operator new[](size); } \
	void cls::operator delete[] (void *p){ ::operator delete[] (p); } 

#define MS_IMPLEMENT_HEAP_CONTROL_INLINE public: \
	void* operator new (size_t size){return ::operator new(size); }\
	void operator delete (void *p){::operator delete(p); }\
	void* operator new[] (size_t size){return ::operator new[](size); } \
	void operator delete[] (void *p){ ::operator delete[] (p); } 
#endif
//_NOCSNEW_
//	#define new TMP_NEW 
//	#define delete TMP_DELETE
#else
#define MS_DECLARE_HEAP_CONTROL 
#define MS_IMPLEMENT_HEAP_CONTROL(cls)
#define MS_IMPLEMENT_HEAP_CONTROL_INLINE
#endif

template<class T> 
class TStackTemplate
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
	class TStackItem
	{
		MS_IMPLEMENT_HEAP_CONTROL_INLINE
	public:
		TStackItem* prev;
		T Data;
		TStackItem(const T& data,TStackItem* _prev):prev(_prev),Data(data){}
	};
	TStackItem* StackTop;
public:
	TStackTemplate():StackTop(0){};
	void Flush();
	virtual ~TStackTemplate(){Flush();}
	bool IsEmpty(){return StackTop==0;}
	void Push(T x)
	{
		StackTop=__SAFENEW TStackItem(x,StackTop);
	};
	BOOL Pop(T& t)
	{
		if(StackTop)
		{
			t=StackTop->Data;
			TStackItem* si=StackTop;
			StackTop=StackTop->prev;
			__SAFEDEL(si);
			return TRUE;
		}
		return FALSE;
	};
	BOOL Peek(T& t)
	{
		if(StackTop)
		{
			t=StackTop->Data;
			return TRUE;
		}
		return FALSE;
	};
};

template<class T>
class CListTemplateBase
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
protected:
	class CListItem
	{

	public:
		CListItem* m_pPrev;
		CListItem* m_pNext;
		T Data;
		CListItem(const T& data, CListItem* _pprev, CListItem* _pnext):
		m_pPrev(_pprev),m_pNext(_pnext),Data(data){}		
	};
protected:
	CListItem* m_pTop;
	CListItem* m_pBottom;		
	idx_t m_nCount;
public:
	CListTemplateBase():m_pTop(0),m_pBottom(0),m_nCount(0){};
	virtual ~CListTemplateBase(){Flush();}

	void Flush();		
	bool IsEmpty(){return m_pTop==0;}
	idx_t GetCount(){return m_nCount;}		

	void Push(const T& x)
	{
		if(m_pTop)
		{
			m_pTop->m_pNext=__SAFENEW CListItem(x,m_pTop,0);
			m_pTop=m_pTop->m_pNext;
		}else m_pTop=m_pBottom=__SAFENEW CListItem(x,0,0);
		m_nCount++;
	}
	void Remove(const T& x)
	{
		CListItem* pItem=Find(x);
		if(pItem)
		{	
			Delete(pItem);				
		}
	}
protected:
	CListItem* Find(const T& x);
	void Delete(CListItem* pItem)
	{
		if(pItem->m_pPrev)
			pItem->m_pPrev->m_pNext=pItem->m_pNext;
		if(pItem->m_pNext)
			pItem->m_pNext->m_pPrev=pItem->m_pPrev;
		if(pItem==m_pTop)
		{
			m_pTop=pItem->m_pPrev;
		}
		if(pItem==m_pBottom)
		{
			m_pBottom=pItem->m_pNext;
		}
		__SAFEDEL(pItem);     
	}
};

template<class T> 
class CListTemplate:public CListTemplateBase<T>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
protected:
	CListTemplateBase<T>::CListItem* m_pCurrent;
public:
	CListTemplate():m_pCurrent(0){}
	virtual ~CListTemplate(){}
	BOOL First(T& t)
	{
		m_pCurrent=m_pBottom;
		if(m_pCurrent)
		{
			t=m_pCurrent->Data;
			return TRUE;
		}else
		{
			return FALSE;
		}
		return m_pCurrent!=0;
	}
	BOOL Last(T& t)
	{
		m_pCurrent=m_pTop;
		if(m_pCurrent)
		{
			t=m_pCurrent->Data;
			return TRUE;
		}else
		{
			return FALSE;
		}
		return m_pCurrent!=0;
	}
	BOOL Next(T& t)
	{
		if(!m_pCurrent)
			return FALSE;
		m_pCurrent=m_pCurrent->m_pNext;
		if(m_pCurrent)
		{
			t=m_pCurrent->Data;
			return TRUE;
		}else
		{
			return FALSE;
		}		
	}
	BOOL Prev(T& t)
	{
		if(!m_pCurrent)
			return FALSE;
		m_pCurrent=m_pCurrent->m_pPrev;
		if(m_pCurrent)
		{
			t=m_pCurrent->Data;
			return TRUE;
		}else
		{
			return FALSE;
		}		
	}
	BOOL DeleteCurrent()
	{
		if(!m_pCurrent)return FALSE;
		Delete(m_pCurrent);
		m_pCurrent=0;
		return TRUE;
	}
	void Append(const T& x)
	{
		if(m_pBottom)
		{
			m_pBottom->m_pPrev=__SAFENEW CListItem(x,0,m_pBottom);
			m_pBottom=m_pBottom->m_pPrev;
		}else m_pTop=m_pBottom=__SAFENEW CListItem(x,0,0);
		m_nCount++;
	}
	BOOL InsertAfter(const T& t)
	{
		if(!m_pCurrent)return FALSE;
		CListItem* pItem=__SAFENEW CListItem(t,m_pCurrent,m_pCurrent->m_pNext);
		m_pCurrent->m_pNext=pItem;
		if(m_pBottom==m_pCurrent)
			m_pBottom=pItem;
		m_pCurrent=pItem;
		return TRUE;
	}
};


template<class T> 
class TQueueTemplate:public CListTemplateBase<T>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	TQueueTemplate(){};
	virtual ~TQueueTemplate(){}

	BOOL Pop(T& t)
	{
		if(m_pTop)
		{
			t=m_pTop->Data;
			m_nCount--;

			CListItem* si=m_pTop;
			m_pTop=m_pTop->m_pPrev;
			__SAFEDEL(si);

			if(!m_pTop)m_pBottom=0;
			else m_pTop->m_pNext=0;
			return TRUE;
		}
		return FALSE;
	};
	BOOL Extract(T& t)
	{
		if(m_pBottom)
		{
			t=m_pBottom->Data;
			m_nCount--;

			CListItem* si=m_pBottom;
			m_pBottom=m_pBottom->m_pNext;
			__SAFEDEL(si);
			if(!m_pBottom)m_pTop=0;
			else m_pBottom->m_pPrev=0;

			return TRUE;
		}
		return FALSE;
	};
};

template<class C> 
class CQueueIndirectTemplate:public TQueueTemplate<C*>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CQueueIndirectTemplate(){};
	virtual ~CQueueIndirectTemplate(){Flush();};
	void Flush();
};
template<class C> 
class CQueueUniqueTemplate:public TQueueTemplate<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CQueueUniqueTemplate(){}
	void Delete(const C& x)
	{
		CListItem* pItem=Find(x);
		if(!pItem)
			return;

		if(pItem->m_pNext)
			pItem->m_pNext->m_pPrev=pItem->m_pPrev;
		if(pItem->m_pPrev)
			pItem->m_pPrev->m_pNext=pItem->m_pNext;
		if(m_pBottom==pItem)
			m_pBottom=pItem->m_pNext;
		if(m_pTop==pItem)
			m_pTop=pItem->m_pPrev;				

		__SAFEDEL(pItem);
	}
	bool Contains(const C& x)
	{
		return Find(x)!=0;
	}
	void Push(C x)
	{
		if(!Contains(x))TQueueTemplate<C>::Push(x);			
	}			
};

template <class T>
void CListTemplateBase<T>::Flush()
{
	while (m_pTop)
	{
		CListItem* si=m_pTop;
		m_pTop=m_pTop->m_pPrev;
		__SAFEDEL(si);
	}
}

template <class C>
void CQueueIndirectTemplate<C>::Flush()
{
	while (m_pTop)
	{
		CListItem* si=m_pTop;
		m_pTop=m_pTop->m_pPrev;

		if(si->Data)delete si->Data;
		__SAFEDEL(si);
	}
}
template <class T>
typename CListTemplateBase<T>::CListItem* CListTemplateBase<T>::Find(const T& x)
{
	CListItem* pResult=m_pBottom;
	while(pResult)
	{
		if(pResult->Data==x)
			return pResult;
		pResult=pResult->m_pNext;
	}
	return 0;		
}

template <class T>
void TStackTemplate<T>::Flush()
{
	while (StackTop)
	{
		TStackItem* si=StackTop;
		StackTop=StackTop->prev;
		__SAFEDEL(si);
	}
}
#define DELTA_NO_LIMIT			-1
#define DELTA_NO_INCREASE		0

template<class T> 
class TArrayTemplate
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
protected:
	idx_t size;
	idx_t delta;
	idx_t delta_max;
	T * array;
	idx_t count;

public:
	TArrayTemplate(idx_t _size=1,idx_t _delta=10,idx_t _delta_limit=DELTA_NO_LIMIT):
		size(_size), delta(_delta > 0 ? _delta : 1), delta_max(_delta_limit), count(0), array(0)
	{
		if(size) array=__SAFENEW T[size];
	}
	TArrayTemplate(const TArrayTemplate<T>& a);

	virtual ~TArrayTemplate()
	{
		if(array) __SAFEDELV(array);
	}
	const T& operator[](idx_t x) const {CTPL_ASSERT(x<count && x>=0);return array[x];}
	T& operator[](idx_t x) {CTPL_ASSERT(x<count && x>=0);return array[x];}
	const T& At(idx_t x) const {CTPL_ASSERT(x<count && x>=0);return array[x];}
	T& At(idx_t x) {CTPL_ASSERT(x<count && x>=0);return array[x];}
	T& First() {CTPL_ASSERT(count); return array[0];}
	const T& First() const {CTPL_ASSERT(count); return array[0];}
	T& Last() {CTPL_ASSERT(count); return array[count-1];}
	const T& Last() const {CTPL_ASSERT(count); return array[count-1];}
	const T* AsVector() const {return array;}
	T* AsVector() {return array;}
	//operator const T*(){return array;}

	// begin() and end() methods return iterators which allow things like
	// range based for loops, std::sort, std::for_each etc to use AcArrays
	// E.g.: for (const auto & elt : arr) sum += elt; 
	//
	T* begin() { return array; }
	T* end() { return array + count; }

	const T* begin() const { return array; }
	const T* end() const { return array + count; }

	//////////////////////////////////////////////////////////////////////////

	bool IsEmpty() const {return !count;}

	bool operator==(const TArrayTemplate<T>& a) const;
	idx_t GetSize() const {return size;} //will be replaced with GetPhysicalLength
	idx_t GetPhysicalLength() const {return size;}
	idx_t GetCount() const {return count;}
	size_t GetDataSize() const { return count * sizeof(T); } // return count in bytes
	void Flush()
	{
		__SAFEDELV(array);
		if(delta)
			size=delta;
		array=__SAFENEW T[size];		
		count=0;
	}

	void Add(const T far& x){
		if(size<=count)
		{
			if (!Resize(size + delta))
				return;

			UpdateDelta();			
		}
		array[count++]=x;
	}

	void AddRange(const TArrayTemplate<T> far& arrToAdd)
	{
		idx_t addCount = arrToAdd.count;
		if (!addCount)
			return;

		if (size <= count + addCount)
		{
			if (addCount < delta)
			{
				if (!Resize(size + delta))
					return;

				UpdateDelta();
			}
			else
				if (!Resize(size + addCount))
					return;
		}

		for (idx_t i = 0; i < addCount; i++)
			array[count++]=arrToAdd.array[i];
	}

	void AddRange(const TArrayTemplate<T> far& arrToAdd, idx_t nStartIndex, idx_t nCount = 0)
	{
		idx_t addCount = nCount ? nCount : (arrToAdd.count - nStartIndex);
		if (!addCount)
			return;

		CTPL_ASSERT(nStartIndex + addCount <= arrToAdd.count);

		if (size <= count + addCount)
		{
			if (addCount < delta)
			{
				if (!Resize(size + delta))
					return;

				UpdateDelta();
			}
			else
				if (!Resize(size + addCount))
					return;
		}

		for (idx_t i = nStartIndex; i < nStartIndex + addCount; i++)
			array[count++]=arrToAdd.array[i];
	}

	void SetAt(idx_t idx,const T& x){
		CTPL_ASSERT(idx>=0);
		idx_t res=1;
		if(size<=idx) 
		{
			res=Resize(idx+delta);
			UpdateDelta();
		}
		if (!res)return;
		else
		{
			array[idx]=x;
			if(count<idx+1)count = idx+1;
		}
	}
	void InsertAt(idx_t idx,const T& x);
	void Delete(idx_t idx);
	void DeleteFirst();
	void DeleteLast();
	void Clear(){count=0;}
	idx_t Find(const T& t,idx_t pos=0)const;
	void Grow(idx_t s){if(Resize(s))count=s;}

	void PrepareToAdd(idx_t nCountToAdd) //Call this before adding known amount of items
	{
		if (size + delta < count + nCountToAdd)
			SetPhisicalLength(count + nCountToAdd);
	}

	void SetPhisicalLength(idx_t nNewSize) 
	{
		if (nNewSize <= 0)
			nNewSize = 1;

		if (size < nNewSize)
			Resize(nNewSize);
		else if (size > nNewSize)
		{
			if (count > nNewSize)
				count = nNewSize;

			T *tmp;
			size=nNewSize;
			tmp=__SAFENEW T[size];
			for(idx_t i=0;i<count;i++)tmp[i]=array[i];
			__SAFEDELV(array);
			array=tmp;
		}	
	}

	void TrimExcess()
	{
		if (size * 0.9 < count)
			return;
		SetPhisicalLength(count);
	}

	TArrayTemplate<T>& operator=(const TArrayTemplate<T>& a );
	idx_t Resize(idx_t s);

	void Reverse();
protected:
	void UpdateDelta()
	{
		if (delta_max && count > 64) //delta optimization
		{
			if(delta_max<0)
				delta *= 2;
			else if(delta<delta_max)
			{
				delta *= 2;
				if(delta>delta_max)
					delta=delta_max;
			}
		}
	}	
	idx_t ResizeAndInsert(idx_t s,idx_t nIdx,const T& xInserted);
};

template<class T>
void TArrayTemplate<T>::Reverse()
{
	idx_t nMax=count/2;
	idx_t i;
	idx_t j;
	for(i=0,j=count-1;i<nMax;i++,j--)
	{
		T x=array[i];
		array[i]=array[j];
		array[j]=x;
	}
}

//------------------------------------------------------------------------------
template<class C> 
class CSortedArray:public TArrayTemplate<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CSortedArray(idx_t _size=1, idx_t _delta=10, idx_t _delta_max=DELTA_NO_LIMIT):
		TArrayTemplate<C>(_size,_delta,_delta_max){};

	void Add(const C& t)
	{
		if(count==0||t==array[count-1]||array[count-1]<t)
		{
			TArrayTemplate<C>::Add(t);
		}else
		{
			idx_t idx; 
			FindSorted(t,idx);
			InsertAt(idx,t);
		}		
	}
	bool AddUnique(const C& t)
	{
		idx_t nElementIndex;
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	bool AddUnique(const C& t, idx_t& nElementIndex)
	{
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	idx_t Insert(const C& t)
	{
		idx_t idx;
		FindSorted(t,idx);
		InsertAt(idx,t);
		return idx;
	}
	idx_t Find(const C& t,idx_t& inspos)const
	{
		return FindSorted(t,inspos);
	}
	idx_t Find(const C& t)const
	{
		idx_t pos;
		return FindSorted(t,pos);
	}	

	void AddRange(const TArrayTemplate<C>& arrToAdd)
	{
		idx_t addCount = arrToAdd.GetCount();
		if (!addCount)
			return;

		PrepareToAdd(addCount);

		idx_t idx;
		for (idx_t i = 0; i < addCount; i++)
		{
			//similar to Add();
			FindSorted(arrToAdd[i], idx);
			InsertAt(idx, arrToAdd[i]);
		}		
	}

	void AddRange(const TArrayTemplate<C>& arrToAdd, idx_t nStartIndex, idx_t nCount = 0)
	{
		CTPL_ASSERT(nStartIndex + nCount <= arrToAdd.GetCount());

		if (!nCount && !arrToAdd.GetCount())
			return;

		PrepareToAdd(nCount);

		idx_t addHigh = nCount ? nStartIndex + nCount : arrToAdd.GetCount();
		idx_t idx;
		for (idx_t i = nStartIndex; i < addHigh; i++)
		{
			//similar to Add();
			FindSorted(arrToAdd[i], idx);
			InsertAt(idx, arrToAdd[i]);
		}		
	}

	void AddRange(const CSortedArray<C>& arrToAdd)
	{
		//если массив пустой - добавим отсортированный массив как есть
		if (!count)
		{
			TArrayTemplate<C>::AddRange(arrToAdd);
			return;
		}
		idx_t addCount = arrToAdd.count;
		if (!addCount)
			return;

		PrepareToAdd(addCount);

		//ѕроще добавить по одному
		if (addCount <= 2)
		{
			Add(arrToAdd.array[0]);
			if (addCount == 2)
				Add(arrToAdd.array[1]);
			return;
		}

		//≈сли можно - добавим в конец как есть
		if (arrToAdd.array[0] >= array[count - 1])
		{
			TArrayTemplate<C>::AddRange(arrToAdd);
			return;
		}

		//найдЄм куда вставл€ть массив
		idx_t idxStart;
		idx_t idxEnd;
		FindSorted(arrToAdd[0], idxStart);
		FindSorted(arrToAdd[addCount - 1], idxEnd);

		//мы не можем вставить куском
		if (idxStart != idxEnd)
		{
			AddRange(*((const TArrayTemplate<C>*)&arrToAdd));
			return;
		}

		//¬ставим в необходимое место
		for (idx_t i = 0; i < addCount; i++)
			InsertAt(idxStart + i, arrToAdd.array[i]);
	}
	
	void DeleteItem(const C& item)
	{
		idx_t nFound = Find(item);
		if (nFound != NOT_FOUND)
			Delete(nFound);
	}

protected:
	idx_t FindSorted(const C& t,idx_t& insPos)const;
	void InsertAt(idx_t idx,const C& x)
	{
		TArrayTemplate<C>::InsertAt(idx,x);
	}	
};
//------------------------------------------------------------------------------
template<class C, int (*CompareFunc)(const C&, const C&)> 
class CCustomSortedArrayT:public TArrayTemplate<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CCustomSortedArrayT(idx_t _size=1, idx_t _delta=10, idx_t _delta_max=DELTA_NO_LIMIT):
		TArrayTemplate<C>(_size, _delta, _delta_max){};
	CCustomSortedArrayT(const CCustomSortedArrayT<C,CompareFunc>& ctx): TArrayTemplate<C>(ctx){}

	void Add(const C& t)
	{
		if(count==0||CompareFunc(t,array[count-1])>=0)
		{
			TArrayTemplate<C>::Add(t);
		}else
		{
			idx_t idx;
			FindSorted(t,idx);
			InsertAt(idx,t);
		}
	}
	idx_t Insert(const C& t)
	{
		idx_t idx;
		FindSorted(t,idx);
		InsertAt(idx,t);
		return idx;
	}
	idx_t Find(const C& t,idx_t& pos)const
	{
		return FindSorted(t,pos);
	}
	idx_t Find(const C& t)const
	{
		idx_t pos=0;
		return FindSorted(t,pos);
	}	
	idx_t FindSorted(const C& t,idx_t& insPos)const;

	void AddRange(const TArrayTemplate<C>& arrToAdd)
	{
		idx_t addCount = arrToAdd.GetCount();
		if (!addCount)
			return;

		PrepareToAdd(addCount);

		idx_t idx;
		for (idx_t i = 0; i < addCount; i++)
		{
			//similar to Add();
			FindSorted(arrToAdd[i], idx);
			InsertAt(idx, arrToAdd[i]);
		}		
	}

	bool AddUnique(const C& t)
	{
		idx_t nElementIndex;
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	bool AddUnique(const C& t, idx_t& nElementIndex)
	{
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}
protected:	
	void InsertAt(idx_t idx,const C& x)
	{
		TArrayTemplate<C>::InsertAt(idx,x);
	}	
};
template<class C> 
class CCustomSortedArray:public TArrayTemplate<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	typedef int (*CompareFunc)(const C&, const C&);
protected:
	CompareFunc m_pcbCompare;
public:
	CCustomSortedArray(CompareFunc cbCompare, idx_t _size=1, idx_t _delta=10, idx_t _delta_max=DELTA_NO_LIMIT):
		TArrayTemplate<C>(_size, _delta, _delta_max), m_pcbCompare(cbCompare){};

	void Add(const C& t)
	{
		if(count==0||m_pcbCompare(t,array[count-1])>=0)
		{
			TArrayTemplate<C>::Add(t);
		}else
		{
			idx_t idx;
			FindSorted(t,idx);
			InsertAt(idx,t);
		}
	}
	idx_t Insert(const C& t)
	{
		idx_t idx;
		FindSorted(t,idx);
		InsertAt(idx,t);
		return idx;
	}
	idx_t Find(const C& t)const
	{
		idx_t pos=0;
		return FindSorted(t,pos);
	}
	idx_t Find(const C& t,idx_t& pos)const
	{
		return FindSorted(t,pos);
	}	
	idx_t FindSorted(const C& t,idx_t& insPos)const;

	bool AddUnique(const C& t)
	{
		idx_t nElementIndex;
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	bool AddUnique(const C& t, idx_t& nElementIndex)
	{
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

protected:	
	void InsertAt(idx_t idx,const C& x)
	{
		TArrayTemplate<C>::InsertAt(idx,x);
	}	
};

//------------------------------------------------------------------------------
template<class C> 
class CIndirectArray:public TArrayTemplate<C*>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CIndirectArray(idx_t _size=1,idx_t _delta=10,bool bOwner=false,idx_t _delta_max=DELTA_NO_LIMIT):
		TArrayTemplate<C*>(_size,_delta,_delta_max),m_bOwner(bOwner){};

	bool SetOwnership(bool o=true)
	{
		m_bOwner=o;
		return m_bOwner;
	}

	void Add(C* x);
	void AddRange(const CIndirectArray<C>& arrToAdd);
	void AddRange(const CIndirectArray<C>& arrToAdd, idx_t nStartIndex, idx_t nCount = 0);
	void SetAt(idx_t idx, C* x);  

	//ѕереносит все элементы и владение элементами данного массива в массив назначени€
	//ќба массива должны владеть элементами - OwnsElements()
	void MoveTo(CIndirectArray<C>& arrDest)
	{
		CTPL_ASSERT(OwnsElements());
		CTPL_ASSERT(arrDest.OwnsElements());

		m_bOwner = false;
		arrDest.AddRange(*this);
		Flush();
		m_bOwner = true;
	}

	~CIndirectArray(){
		if(m_bOwner)
			DeleteContainment();
	}

	CIndirectArray& operator=(const CIndirectArray& ia)
	{
		if(m_bOwner)DeleteContainment();
		TArrayTemplate<C*>::operator =(ia);
		return *this;
	}

	void Delete(idx_t idx)
	{
		if(m_bOwner)delete array[idx];
		TArrayTemplate<C*>::Delete(idx);
	}  
	void DeleteFirst()
	{
		if(m_bOwner)delete array[0];
		TArrayTemplate<C*>::DeleteFirst();
	}  
	void DeleteLast()
	{
		CTPL_ASSERT(count);
		if(m_bOwner)delete array[count-1];
		count--;//TArrayTemplate<C*>::Delete(idx);
	}  
	void Clear(){
		if(m_bOwner)DeleteContainment();
		TArrayTemplate<C*>::Clear();
	}

	void Flush()
	{
		if(m_bOwner)DeleteContainment();
		TArrayTemplate<C*>::Flush();
	}	  
	void Grow(idx_t s);
	void SetPhisicalLength(idx_t nNewSize);
	void PrepareToAdd(idx_t nCountToAdd) //Call this before adding known amount of items
	{
		if (size + delta < count + nCountToAdd)
			SetPhisicalLength(count + nCountToAdd);
	}
	void TrimExcess();
	idx_t Find(const C* pT, idx_t pos=0) const {return TArrayTemplate<C*>::Find(const_cast<C*>(pT),pos);}
	idx_t Find(const C& t, idx_t pos=0) const;

	bool OwnsElements() const {return m_bOwner;}
	void InsertAt(idx_t idx, C* x); //using memcpy	
	idx_t Resize(idx_t s); //using memcpy	
protected:
	bool m_bOwner;
	void DeleteContainment();		
	idx_t ResizeAndInsert(idx_t s,idx_t nIdx, C* xInserted); //using memcpy
};

template<class C>
void CIndirectArray<C>::InsertAt( idx_t idx, C* x )
{
	if(idx>=count)
	{
		SetAt(idx,x);
		return;
	}
	if(size<=count)
	{
		ResizeAndInsert(size + delta,idx,x);
		UpdateDelta();
		return;
	}

	memmove(array+idx+1, array+idx, (count-idx)*sizeof(C*));

	count++;
	array[idx]=x;
}

template<class C>
idx_t CIndirectArray<C>::ResizeAndInsert(idx_t s,idx_t nIdx, C* xInserted )
{
	if(size>=s)return 1;
	if(!delta)return 0;
	C **tmpArray;

	size=s;
	tmpArray=__SAFENEW C*[size];

	//for(i=0;i<nIdx;i++)tmpArray[i]=array[i];
	memcpy(tmpArray, array, nIdx * sizeof(C*));

	tmpArray[nIdx]=xInserted;

	//for(i=nIdx;i<count;i++)tmpArray[i+1]=array[i];	
	memcpy(tmpArray + nIdx + 1, array + nIdx, (count - nIdx) * sizeof(C*));

	__SAFEDELV(array);
	array=tmpArray;
	count++;
	return 1;
}

template<class C> 
class CSortedIndirectArray:public CIndirectArray<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CSortedIndirectArray(idx_t _size=1, idx_t _delta=10, bool bOwner=false, idx_t _delta_max=DELTA_NO_LIMIT):
		CIndirectArray<C>(_size, _delta, bOwner, _delta_max){}

	void Add(C* t)
	{
		if(count==0||(*array[count-1])<(*t)||(*t)==(*array[count-1]))
		{
			CIndirectArray<C>::Add(t);
		}else
		{
			idx_t idx;
			FindSorted(t,idx);
			InsertAt(idx,t);
		}
	}

	bool AddUnique(C* t)
	{
		idx_t nElementIndex;
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	bool AddUnique(C* t, idx_t& nElementIndex)
	{
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	void AddRange(const CIndirectArray<C>& arrToAdd) //new method (not overrides inherited)
	{
		CTPL_ASSERT(!(m_bOwner && arrToAdd.OwnsElements()));

		idx_t addCount = arrToAdd.GetCount();
		if (!addCount)
			return;

		PrepareToAdd(addCount);

		idx_t idx;
		for (idx_t i = 0; i < addCount; i++)
		{
			//similar to Add();
			FindSorted(arrToAdd[i], idx);
			InsertAt(idx, arrToAdd[i]);
		}
	}

	void AddRange(const CIndirectArray<C>& arrToAdd, idx_t nStartIndex, idx_t nCount = 0) //new method (not overrides inherited)
	{
		CTPL_ASSERT(!(m_bOwner && arrToAdd.OwnsElements()));
		CTPL_ASSERT(nStartIndex + nCount <= arrToAdd.GetCount());

		if (!nCount && !arrToAdd.GetCount())
			return;

		PrepareToAdd(nCount);

		idx_t addHigh = nCount ? nStartIndex + nCount : arrToAdd.GetCount();
		idx_t idx;
		for (idx_t i = nStartIndex; i < addHigh; i++)
		{
			//similar to Add();
			FindSorted(arrToAdd[i], idx);
			InsertAt(idx, arrToAdd[i]);
		}
	}

	void AddRange(const CSortedIndirectArray<C>& arrToAdd) //new method (not overrides inherited)
	{
		CTPL_ASSERT(!(m_bOwner && arrToAdd.m_bOwner));

		//если массив пустой - добавим отсортированный массив как есть
		if (!count)
		{
			CIndirectArray<C>::AddRange(arrToAdd);
			return;
		}
		idx_t addCount = arrToAdd.count;
		if (!addCount)
			return;

		PrepareToAdd(addCount);

		//ѕроще добавить по одному
		if (addCount <= 2)
		{
			Add(arrToAdd.array[0]);
			if (addCount == 2)
				Add(arrToAdd.array[1]);
			return;
		}

		//≈сли можно - добавим в конец как есть
		if (*array[count - 1]<*arrToAdd.array[0])
		{
			CIndirectArray<C>::AddRange(arrToAdd);
			return;
		}

		//найдЄм куда вставл€ть массив
		idx_t idxStart;
		idx_t idxEnd;
		FindSorted(arrToAdd[0], idxStart);
		FindSorted(arrToAdd[addCount - 1], idxEnd);

		//мы не можем вставить куском
		if (idxStart != idxEnd)
		{
			AddRange(*((const CIndirectArray<C>*)&arrToAdd));
			return;
		}

		//¬ставим в необходимое место
		for (idx_t i = 0; i < addCount; i++)
			InsertAt(idxStart + i, arrToAdd.array[i]);	
	}

	//ѕереносит все элементы и владение элементами данного массива в массив назначени€
	//ќба массива должны владеть элементами - OwnsElements()
	void MoveTo(CIndirectArray<C>& arrDest)
	{
		CTPL_ASSERT(OwnsElements());
		CTPL_ASSERT(arrDest.OwnsElements());

		m_bOwner = false;
		arrDest.AddRange(*this);
		Flush();
		m_bOwner = true;
	}

	//ѕереносит все элементы и владение элементами данного массива в массив назначени€
	//ќба массива должны владеть элементами - OwnsElements()
	void MoveTo(CSortedIndirectArray<C>& arrDest)
	{
		CTPL_ASSERT(OwnsElements());
		CTPL_ASSERT(arrDest.OwnsElements());

		m_bOwner = false;
		arrDest.AddRange(*this);
		Flush();
		m_bOwner = true;
	}

	idx_t Find(const C& t,idx_t& inspos) const {return FindSorted(&t,inspos);}
	idx_t Find(const C& t) const {idx_t pos; return FindSorted(&t,pos);}

	//¬ерси€ поиска дл€ неконстантных операторов < и ==
	idx_t Find(C& t,idx_t& inspos) const {return FindSorted(&t,inspos);}
	idx_t Find(C& t) const {idx_t pos; return FindSorted(&t,pos);}

	idx_t FindPtr(const C* pT,idx_t pos=0) const { return CIndirectArray<C>::Find(pT); }

	void Sort()
	{
		if(count<2)
			return;
		idx_t nCnt=count;
		count=1;
		while(count<nCnt)
		{
			Add(array[count]);
		}
	}
protected:
	idx_t FindSorted(const C* t,idx_t& insPos)const;
	idx_t FindSorted(C* t,idx_t& insPos)const;
	void InsertAt(idx_t idx, C* x){CIndirectArray<C>::InsertAt(idx,x);}
};

template<class C, int (*CompareFunc)(const C&, const C&)> 
class CCustomSortedIndirectArrayT:public CIndirectArray<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	CCustomSortedIndirectArrayT(idx_t _size=1, idx_t _delta=10, bool bOwner=false, idx_t _delta_max=DELTA_NO_LIMIT):
		CIndirectArray<C>(_size,_delta,bOwner,_delta_max) {}

	void Add(C* t)
	{
		if(count==0||CompareFunc(*t,*array[count-1])>=0)
		{
			CIndirectArray<C>::Add(t);
		}else
		{
			idx_t idx;
			FindSorted(t,idx);
			InsertAt(idx,t);
		}
	}
	idx_t Find(const C& t)const{idx_t pos=0;return FindSorted(&t,pos);}
	idx_t Find(const C& t,idx_t& pos)const{	return FindSorted(&t,pos);}
	idx_t FindPtr(const C* pT,idx_t pos=0)const{ return CIndirectArray<C>::Find(pT);}
	idx_t FindSorted(const C* t,idx_t& insPos)const;
	
	bool AddUnique(C* t)
	{
		idx_t nElementIndex;
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	bool AddUnique(C* t, idx_t& nElementIndex)
	{
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}
protected:		
	void InsertAt(idx_t idx,C* x){CIndirectArray<C>::InsertAt(idx,x);}
};
template<class C> 
class CCustomSortedIndirectArray:public CIndirectArray<C>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	typedef int (*CompareFunc)(const C&, const C&);
protected:
	CompareFunc m_pcbCompare;
public:
	CCustomSortedIndirectArray(CompareFunc cbCompare, idx_t _size=1, idx_t _delta=10, bool bOwner=false, idx_t _delta_max=DELTA_NO_LIMIT):
		CIndirectArray<C>(_size, _delta, bOwner, _delta_max), m_pcbCompare(cbCompare){}

	void Add(C* t)
	{
		if(count==0||m_pcbCompare(*t,*array[count-1])>=0)
		{
			CIndirectArray<C>::Add(t);
		}else
		{
			idx_t idx;
			FindSorted(t,idx);
			InsertAt(idx,t);
		}
	}
	bool AddUnique(C* t)
	{
		idx_t nElementIndex;
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	bool AddUnique(C* t, idx_t& nElementIndex)
	{
		if (FindSorted(t, nElementIndex) == NOT_FOUND)
		{
			InsertAt(nElementIndex, t);
			return true;
		}
		return false;
	}

	idx_t Find(const C& t,idx_t& pos)const{	return FindSorted(&t,pos);}
	idx_t Find(const C& t)const{idx_t pos=0;	return FindSorted(&t,pos);}
	idx_t FindPtr(C* pT,idx_t pos=0)const{ return CIndirectArray<C>::Find(pT);}
	idx_t FindSorted(const C* t,idx_t& insPos)const;
protected:		
	void InsertAt(idx_t idx,C* x){CIndirectArray<C>::InsertAt(idx,x);}
};

class TIntegerArray:public TArrayTemplate<idx_t>
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE
public:
	TIntegerArray(idx_t _size=1,idx_t _delta=10,idx_t _delta_max=DELTA_NO_LIMIT):TArrayTemplate<idx_t>(_size,_delta,_delta_max){}
	TIntegerArray(const TIntegerArray& a):TArrayTemplate<idx_t>(a){}
};


// Common Templates Source files

template <class T>
TArrayTemplate<T>::TArrayTemplate(const TArrayTemplate<T>& a ):size(a.size),delta(a.delta),delta_max(a.delta_max),count(a.count)
{
	array=__SAFENEW T[a.size];
	

	for(idx_t i=0;i<a.count;i++)array[i]=a.array[i];
}
template <class T>
TArrayTemplate<T>& TArrayTemplate<T>::operator=(const TArrayTemplate<T>& a )
{
	Clear();
	if(size<a.size)
	{
		__SAFEDELV(array);
		array=__SAFENEW T[a.size];
		size=a.size;
	}
	count=a.count;
	delta=a.delta;
	delta_max=a.delta_max;

	for(idx_t i=0;i<count;i++)array[i]=a.array[i];
	return *this;
}
template <class T>
idx_t TArrayTemplate<T>::Find(const T& t,idx_t pos)const
{
	for(idx_t i=pos;i<count;i++)if(array[i]==t)return i;
	return NOT_FOUND;
}
template <class T>
idx_t TArrayTemplate<T>::ResizeAndInsert(idx_t s,idx_t nIdx,const T& xInserted)
{
	if(size>=s)return 1;
	if(!delta)return 0;
	T *tmp;
	idx_t i;

	size=s;
	tmp=__SAFENEW T[size];
	for(i=0;i<nIdx;i++)tmp[i]=array[i];
	tmp[nIdx]=xInserted;
	for(i=nIdx;i<count;i++)tmp[i+1]=array[i];	
	__SAFEDELV(array);
	array=tmp;
	count++;
	return 1;	
}
template <class T>
idx_t TArrayTemplate<T>::Resize(idx_t s)
{
	if(size>=s)return 1;
	
	//if(!delta)return 0; «ачем?

	T *tmp;
	size=s;
	tmp=__SAFENEW T[size];
	for(idx_t i=0;i<count;i++)tmp[i]=array[i];
	__SAFEDELV(array);
	array=tmp;
	return 1;
}
template <class T>
void TArrayTemplate<T>::InsertAt(idx_t idx,const T& x)
{
	if(idx>=count)
	{
		SetAt(idx,x);
		return;
	}
	if(size<=count)
	{
		ResizeAndInsert(size + delta,idx,x);
		UpdateDelta();
		return;
	}

	for(idx_t i=count;i>idx;i--)
		array[i]=array[i-1];
	count++;
	array[idx]=x;
}
template <class T>
void TArrayTemplate<T>::Delete(idx_t idx)
{
	CTPL_ASSERT(idx>=0 && idx<count);
	for(idx_t i=idx;i<count-1;i++)array[i]=array[i+1];
	count--;
}
template <class T>
void TArrayTemplate<T>::DeleteFirst()
{
	CTPL_ASSERT(count);
	for(idx_t i=0;i<count-1;i++)array[i]=array[i+1];
	count--;
}
template <class T>
void TArrayTemplate<T>::DeleteLast()
{
	CTPL_ASSERT(count);
	count--;
}
template <class T>
bool TArrayTemplate<T>::operator==(const TArrayTemplate<T>& a) const
{
	if(count!=a.count)return 0;
	for(idx_t i=0;i<count;i++)if(!(array[i]==a.array[i]))return 0;
	return 1;
}
//---------------------------------------------------------------
template<class C> 
idx_t CSortedArray<C>::FindSorted(const C& t,idx_t& insPos)const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		if( array[insPos] == t ) return insPos;
		else
			if( t <  array[insPos] ) down=insPos-1;
			else up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}
//---------------------------------------------------------------
template<class C, int (*CompareFunc)(const C&, const C&)>
idx_t CCustomSortedArrayT<C,CompareFunc>::FindSorted(const C& t,idx_t& insPos)const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		int nCompareRes=CompareFunc(t, array[insPos]);

		if(  nCompareRes == 0 ) 
			return insPos;
		else if( nCompareRes<0 ) 
			down=insPos-1;
		else 
			up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}
template<class C>
idx_t CCustomSortedArray<C>::FindSorted(const C& t,idx_t& insPos)const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		int nCompareRes=m_pcbCompare(t, array[insPos]);

		if(  nCompareRes == 0 ) 
			return insPos;
		else if( nCompareRes<0 ) 
			down=insPos-1;
		else 
			up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}

//------------------------------------------------------------------
template<class C> 
void CIndirectArray<C>::Grow(idx_t s)
{
	idx_t prevCnt=count;
	if(m_bOwner)
	{
		for(idx_t i=s;i<count;i++)
			delete array[i];
	}

	if (prevCnt >= s)
	{
		count = s;
		return;
	}

	if(Resize(s))
		count=s;  //similar to TArrayTemplate<C*>::Grow(s);

	memset(array + prevCnt, 0, (count - prevCnt) * sizeof(C*)); //similar to for(idx_t i=prevCnt;i<s;i++)	array[i]=0;
}

template<class C> 
void CIndirectArray<C>::SetPhisicalLength(idx_t nNewSize)
{
	if (nNewSize <= 0)
		nNewSize = 1;

	if (size > nNewSize)
	{	
		if (count > nNewSize)
		{
			if(m_bOwner)
			{
				for(idx_t i=nNewSize;i<count;i++)
					delete array[i];
			}
			count = nNewSize;
		}

		//Shrink
		C **tmpArray;
		size=nNewSize;
		tmpArray=__SAFENEW C*[size];
		memcpy(tmpArray, array, count * sizeof(C*)); //for(idx_t i=0;i<count;i++)tmp[i]=array[i];
		__SAFEDELV(array);
		array=tmpArray;
	}
	else if (size < nNewSize)
	{
		Resize(nNewSize);
	}
}

template<class C> 
void CIndirectArray<C>::TrimExcess()
{
	if (size * 0.9 < count)
		return;
	SetPhisicalLength(count);
}

//This is not overloaded method but new method
template<class C> 
void CIndirectArray<C>::Add(C* x)
{
	//TArrayTemplate<C*>::Add(x);
	if(size<=count)
	{
		if (!Resize(size + delta)) //call indirect resize method!
			return;

		UpdateDelta();
	}
	array[count++]=x;
}

//This is not overloaded method but new method
template<class C> 
void CIndirectArray<C>::AddRange(const CIndirectArray<C>& arrToAdd)
{
	CTPL_ASSERT(!(m_bOwner && arrToAdd.m_bOwner));

	if (!arrToAdd.count)
		return;

	idx_t addCount = arrToAdd.count;
	if (size <= count + addCount)
	{
		if (addCount < delta)
		{
			if (!Resize(size + delta)) //call indirect resize method!
				return;

			UpdateDelta();
		}
		else
			if (!Resize(size + addCount))
				return;
	}

	memcpy(array + count, arrToAdd.array, addCount * sizeof(C*));
	count += addCount;
}

//This is not overloaded method but new method
template<class C> 
void CIndirectArray<C>::AddRange(const CIndirectArray<C>& arrToAdd, idx_t nStartIndex, idx_t nCount /*= 0*/)
{
	CTPL_ASSERT(!(m_bOwner && arrToAdd.m_bOwner));
	CTPL_ASSERT(nStartIndex + nCount <= arrToAdd.count);

	idx_t addCount = nCount ? nCount : arrToAdd.count;
	if (!addCount)
		return;
	if (size <= count + addCount)
	{
		if (addCount < delta)
		{
			if (!Resize(size + delta)) //call indirect resize method!
				return;

			UpdateDelta();
		}
		else
			if (!Resize(size + addCount))
				return;
	}

	memcpy(array + count, arrToAdd.array + nStartIndex, addCount * sizeof(C*));
	count += addCount;
}

//This is not overloaded method but new method
template<class C>
idx_t CIndirectArray<C>::Resize( idx_t s )
{
	if(size>=s)
		return 1;

	C **tmpArray;
	size=s;
	tmpArray=__SAFENEW C*[size];
	memcpy(tmpArray, array, count * sizeof(C*)); //for(idx_t i=0;i<count;i++)tmp[i]=array[i];
	__SAFEDELV(array);
	array=tmpArray;
	return 1;
}

template<class C> 
void CIndirectArray<C>::SetAt(idx_t idx,C* x)
{
	if(count>idx && m_bOwner)
		delete array[idx];  

	if(size<=idx)
	{
		if(!Resize(idx+delta))
			return;
		else
			UpdateDelta();
	}

	array[idx]=x;
	if(count<idx+1)
	{
		//for(idx_t i=count;i<=idx;i++)	array[i]=0;
		if (idx > count)
			memset(array + count, 0, (idx - count) * sizeof(C*));
		count = idx+1;
	}
};
template<class C> 
idx_t CIndirectArray<C>::Find(const C& t,idx_t pos)const
{
	for(idx_t i=pos;i<count;i++)if((*array[i])==t)return i;
	return NOT_FOUND;
}
template<class C> 
void CIndirectArray<C>::DeleteContainment()
{
	for(idx_t i=0;i<count;i++)
		delete array[i];
}
//----------------------------------------------------------------------
template<class C> 
idx_t CSortedIndirectArray<C>::FindSorted(const C* t,idx_t& insPos) const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		if( (*array[insPos]) == (*t) ) 
			return insPos;
		else
			if( (*t) <  (*array[insPos]) ) down=insPos-1;
			else up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}

//¬ерси€ поиска дл€ неконстантных операторов < и ==
template<class C> 
idx_t CSortedIndirectArray<C>::FindSorted(C* t,idx_t& insPos) const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		if( (*array[insPos]) == (*t) ) 
			return insPos;
		else
			if( (*t) <  (*array[insPos]) ) down=insPos-1;
			else up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}
//----------------------------------------------------------------------
template<class C, int (*CompareFunc)(const C&, const C&)> 
idx_t CCustomSortedIndirectArrayT<C,CompareFunc>::FindSorted(const C* t,idx_t& insPos)const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		int nCompareRes=CompareFunc(*t,*array[insPos]);

		if( nCompareRes==0 ) 
			return insPos;
		else if( nCompareRes < 0) 
			down=insPos-1;
		else 
			up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}
//----------------------------------------------------------------------
template<class C> 
idx_t CCustomSortedIndirectArray<C>::FindSorted(const C* t,idx_t& insPos)const
{
	insPos=0;
	idx_t down=GetCount()-1;
	idx_t up=0;
	if(down<up) return NOT_FOUND;
	do
	{
		insPos = (up+down)/2;

		int nCompareRes=m_pcbCompare(*t,*array[insPos]);

		if( nCompareRes==0 ) 
			return insPos;
		else if( nCompareRes < 0) 
			down=insPos-1;
		else 
			up=++insPos;
	}
	while(up<=down);
	return NOT_FOUND;
}
//-------------------------------------------------------------------------
//—ортировочна€ запись, будет отсортированна по данным (data)
//¬нимание! - не мен€йте данные, если запись уже добавлена в отсортированный массив,
//т.к. положение записи не обновитс€
template<class DataType, class IdxType> 
class CIndexRecord
{
	MS_IMPLEMENT_HEAP_CONTROL_INLINE;
protected:
	DataType m_data;
	IdxType m_index;
public:
	CIndexRecord():m_data(),m_index(){}
	virtual ~CIndexRecord(){}
	CIndexRecord(const DataType& data):m_data(data){}
	CIndexRecord(const DataType& data,const IdxType& index):m_data(data),m_index(index){}
	CIndexRecord(const CIndexRecord& ir):m_data(ir.m_data),m_index(ir.m_index){}
	CIndexRecord& operator=(const CIndexRecord& ir)
	{
		if(this==&ir)return *this;
		m_data=ir.m_data;
		m_index=ir.m_index;
		return *this;
	}
	bool operator==(const CIndexRecord& ir)const{return m_data==ir.m_data;}
	bool operator>=(const CIndexRecord& ir)const{return m_data>=ir.m_data;}
	bool operator<=(const CIndexRecord& ir)const{return m_data<=ir.m_data;}
	bool operator>(const CIndexRecord& ir)const{return m_data>ir.m_data;}
	bool operator<(const CIndexRecord& ir)const{return m_data<ir.m_data;}
	bool operator!=(const CIndexRecord& ir)const{return m_data!=ir.m_data;}

	IdxType& GetIndex(){return m_index;}
	const IdxType& GetIndex() const {return m_index;}
	void SetIndex(const IdxType& i){m_index=i;}

	DataType& GetData() {return m_data;}
	const DataType& GetData() const {return m_data;}
	void SetData(const DataType& d){m_data=d;}
};

template<class DataType, class IdxType> inline
	CIndexRecord<DataType, IdxType>	MakeIndexRecord(const DataType& data, const IdxType& index)
{	// return CIndexRecord composed from arguments
	return CIndexRecord<DataType, IdxType>(data, index);
}

template<class DataType, class IdxType> inline
	CIndexRecord<DataType, IdxType>	*CreateIndexRecord(const DataType& data, const IdxType& index)
{	// return CIndexRecord composed from arguments
	return new CIndexRecord<DataType, IdxType>(data, index);
}

//—ортировочна€ запись с указателем на данные, будет отсортированна по данным (data)
//¬нимание! - не мен€йте данные, если запись уже добавлена в отсортированный массив,
//т.к. положение записи не обновитс€
template<class DataType,class IdxType> 
class CIndirectIndexRecord
{

protected:
	DataType* m_pData;
	IdxType m_index;
public:
	CIndirectIndexRecord():m_pData(0){}
	virtual ~CIndirectIndexRecord(){}
	CIndirectIndexRecord(DataType* pData, IdxType index):m_pData(pData),m_index(index){}
	CIndirectIndexRecord(const CIndirectIndexRecord& ir):m_pData(ir.m_pData),m_index(ir.m_index){}
	CIndirectIndexRecord& operator=(const CIndirectIndexRecord& ir)
	{
		if(this==&ir)return *this;
		m_pData=ir.m_pData;
		m_index=ir.m_index;
		return *this;
	}
	bool operator==(const CIndirectIndexRecord& ir)
	{
		if(m_pData && ir.m_pData)return (*m_pData)==(*(ir.m_pData));
		else return 0;
	}
	bool operator>=(const CIndirectIndexRecord& ir)const
	{
		if(m_pData && ir.m_pData)return (*m_pData)>=(*(ir.m_pData));		
		else return 0;
	}
	bool operator<=(const CIndirectIndexRecord& ir)const
	{
		if(m_pData && ir.m_pData)return (*m_pData)<=(*(ir.m_pData));
		else return 0;
	}
	bool operator>(const CIndirectIndexRecord& ir)const
	{
		if(m_pData && ir.m_pData)return (*m_pData)>(*(ir.m_pData));
		else return false;
	}
	bool operator<(const CIndirectIndexRecord& ir)const
	{
		if(m_pData && ir.m_pData)return (*m_pData)<(*(ir.m_pData));
		else return false;
	}
	bool operator!=(const CIndirectIndexRecord& ir)const
	{
		if(m_pData && ir.m_pData)return (*m_pData)!=(*(ir.m_pData));
		else return 0;
	}

	IdxType GetIndex() {return m_index;}
	const IdxType GetIndex() const {return m_index;}
	void SetIndex(IdxType i){m_index=i;}

	DataType* GetData() {return m_pData;}
	const DataType* GetData() const {return m_pData;}
	void SetData(DataType* d) {m_pData=d;}
};

//-------------------------------------------------------------------------
#endif
