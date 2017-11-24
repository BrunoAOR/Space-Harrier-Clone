#include "ReferenceBase.h"

#include <assert.h>


bool operator==(const ReferenceBase& lhs, const ReferenceBase& rhs)
{
	return (lhs.m_referencesList && rhs.m_referencesList && lhs.m_referencesList == rhs.m_referencesList);
}


bool operator!=(const ReferenceBase & lhs, const ReferenceBase & rhs)
{
	return !operator==(lhs, rhs);
}


ReferenceBase::ReferenceBase()
{
}


ReferenceBase::ReferenceBase(std::list<ReferenceBase*>* referencesList, void * dataPtr)
	: m_referencesList(referencesList), m_dataPtr(dataPtr)
{
	addReference();
}


ReferenceBase::~ReferenceBase()
{
	reset();
}


ReferenceBase::operator bool() const
{
	return m_dataPtr != nullptr;
}


void ReferenceBase::addReference()
{
	if (m_referencesList != nullptr)
	{
		m_referencesList->push_back(this);
	}
}


void ReferenceBase::reset()
{
	if (m_referencesList != nullptr)
	{
		auto it = std::find(m_referencesList->begin(), m_referencesList->end(), this);
		m_referencesList->erase(it);
		if (m_referencesList->size() == 0)
		{
			delete m_referencesList;
		}
		m_referencesList = nullptr;
		m_dataPtr = nullptr;
	}
}
