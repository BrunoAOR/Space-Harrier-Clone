#ifndef H_REFERENCE_OWNER
#define H_REFERENCE_OWNER

#include <list>
#include <assert.h>
//#include "globals.h"
#include "Reference.h"
#include "ReferenceBase.h"


template<typename T>
class ReferenceOwner final
	: public Reference<T>
{
public:
	ReferenceOwner();
	ReferenceOwner(T* dataPtr);
	~ReferenceOwner();
	ReferenceOwner(const ReferenceOwner& source) = delete;
	ReferenceOwner(ReferenceOwner&& source);
	template<typename U>
	ReferenceOwner(ReferenceOwner<U>&& source);
	ReferenceOwner& operator=(const ReferenceOwner& source) = delete;
	ReferenceOwner& operator=(ReferenceOwner&& source);

	int getRefCount() const;
	Reference<T> getReference() const;
	template<typename U>
	Reference<U> getStaticCastedReference() const;
	template<typename U>
	Reference<U> getDynamicCastedReference() const;
	void deleteReferences();
};


template<typename T>
ReferenceOwner<T>::ReferenceOwner()
	: Reference<T>()
{
	//OutputLog("DEBUG: ReferenceOwner default constructor");
}


template<typename T>
ReferenceOwner<T>::ReferenceOwner(T* dataPtr)
	: Reference<T>(new std::list<ReferenceBase*>(), static_cast<void*>(dataPtr))
{
	//OutputLog("DEBUG: ReferenceOwner params constructor");
}


template<typename T>
ReferenceOwner<T>::~ReferenceOwner()
{
	//OutputLog("DEBUG: ReferenceOwner destructor");
	this->deleteReferences();
}


template<typename T>
ReferenceOwner<T>::ReferenceOwner(ReferenceOwner && source)
	: Reference<T>(source.m_referencesList, source.m_dataPtr)
{
	//OutputLog("DEBUG: ReferenceOwner move constructor");
	source.reset();
}


template<typename T>
template<typename U>
ReferenceOwner<T>::ReferenceOwner(ReferenceOwner<U>&& source)
	: Reference<T>(source.m_referencesList, source.m_dataPtr)
{
	//OutputLog("DEBUG: ReferenceOwner generalized move constructor");
	// This is only added to cause a compile-time error in case no implicit conversion exists to convert a U* into a T*
	T* ptr = source.get();
	source.reset();
}


template<typename T>
ReferenceOwner<T>& ReferenceOwner<T>::operator=(ReferenceOwner && source)
{
	//OutputLog("DEBUG: ReferenceOwner move assignment");
	if (&source == this)
	{
		return *this;
	}
	this->deleteReferences();

	this->m_referencesList = source.m_referencesList;
	this->m_dataPtr = source.m_dataPtr;
	this->addReference();
	source.reset();

	return *this;
}


template<typename T>
int ReferenceOwner<T>::getRefCount() const
{
	return this->m_referencesList != nullptr ? this->m_referencesList->size() : 0;
}


template<typename T>
Reference<T> ReferenceOwner<T>::getReference() const
{
	return Reference<T>(this->m_referencesList, this->m_dataPtr);;
}


template<typename T>
template<typename U>
Reference<U> ReferenceOwner<T>::getStaticCastedReference() const
{
	return this->static_reference_cast<U>();
}


template<typename T>
template<typename U>
Reference<U> ReferenceOwner<T>::getDynamicCastedReference() const
{
	return this->dynamic_reference_cast<U>();
}


template<typename T>
void ReferenceOwner<T>::deleteReferences()
{
	if (this->m_dataPtr == nullptr || this->m_referencesList == nullptr)
	{
		return;
	}

	delete static_cast<T*>(this->m_dataPtr);

	for (auto& ref : *(this->m_referencesList))
	{
		if (this != ref)
		{
			ref->m_dataPtr = nullptr;
			ref->m_referencesList = nullptr;
		}
	}
	
	delete this->m_referencesList;
	this->m_referencesList = nullptr;
}


#endif // !H_REFERENCE_OWNER
