#ifndef H_REFERENCE
#define H_REFERENCE

//#include "globals.h"
#include "ReferenceBase.h"


template<typename T>
class Reference
	: public ReferenceBase
{
	template<typename U>
	friend class Reference;
	template<typename U>
	friend class ReferenceOwner;

public:
	Reference();
	virtual ~Reference();
	Reference(const Reference& source);
	template<typename U>
	Reference(const Reference<U>& source);
	Reference& operator=(const Reference& source);

	template<typename U>
	Reference<U> static_reference_cast() const;
	template<typename U>
	Reference<U> dynamic_reference_cast() const;

	T* get();
	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();

private:
	Reference(std::list<ReferenceBase*>* referencesList, void* dataPtr);
};


template<typename T>
Reference<T>::Reference()
	: ReferenceBase()
{
	//OutputLog("DEBUG: Reference default constructor");
}


template<typename T>
Reference<T>::Reference(std::list<ReferenceBase*>* referencesList, void * dataPtr)
	: ReferenceBase(referencesList, dataPtr)
{
	//OutputLog("DEBUG: Reference params constructor");
}


template<typename T>
Reference<T>::~Reference()
{
	//OutputLog("DEBUG: Reference destructor");
	// ReferenceBase will call removeReference upon destruction.
}


template<typename T>
Reference<T>::Reference(const Reference& source)
	: ReferenceBase(source.m_referencesList, source.m_dataPtr)
{
	//OutputLog("DEBUG: Reference copy constructor");
}


template<typename T>
template<typename U>
Reference<T>::Reference(const Reference<U>& source)
	: ReferenceBase(source.m_referencesList, source.m_dataPtr)
{
	//OutputLog("DEBUG: Reference generalized copy constructor");
	// This is only added to cause a compile-time error in case no implicit conversion exists to convert a U* into a T*
	const T* ptr = static_cast<U*>(source.m_dataPtr);
}


template<typename T>
Reference<T>& Reference<T>::operator=(const Reference & source)
{
	//OutputLog("DEBUG: Reference copy assignment");
	if (&source == this)
	{
		return *this;
	}
	reset();
	m_referencesList = source.m_referencesList;
	m_dataPtr = source.m_dataPtr;
	addReference();
	return *this;
}


template<typename T>
template<typename U>
Reference<U> Reference<T>::static_reference_cast() const
{
	return Reference<U>(this->m_referencesList, this->m_dataPtr);
}


template<typename T>
template<typename U>
Reference<U> Reference<T>::dynamic_reference_cast() const
{
	if (dynamic_cast<U*>(static_cast<T*>(this->m_dataPtr)))
	{
		return Reference<U>(this->m_referencesList, this->m_dataPtr);
	}
	else
	{
		return Reference<U>();
	}
}


template<typename T>
T* Reference<T>::get()
{
	return static_cast<T*>(m_dataPtr);
}

template<typename T>
const T& Reference<T>::operator*() const
{
	return *(static_cast<T*>(m_dataPtr));
}


template<typename T>
T& Reference<T>::operator*()
{
	return *(static_cast<T*>(m_dataPtr));
}


template<typename T>
const T* Reference<T>::operator->() const
{
	return static_cast<T*>(m_dataPtr);
}


template<typename T>
T* Reference<T>::operator->()
{
	return static_cast<T*>(m_dataPtr);
}


#endif // !H_REFERENCE
