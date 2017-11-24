#ifndef H_REFERENCE_BASE
#define H_REFERENCE_BASE

#include <list>


class ReferenceBase
{
	template<typename T>
	friend class ReferenceOwner;
	friend bool operator== (const ReferenceBase& lhs, const ReferenceBase& rhs);

public:
	ReferenceBase();
	virtual ~ReferenceBase() = 0;
	ReferenceBase(const ReferenceBase& source) = delete;
	ReferenceBase& operator=(const ReferenceBase& source) = delete;
	ReferenceBase(ReferenceBase&& source) = delete;
	ReferenceBase& operator=(ReferenceBase&& source) = delete;

	operator bool() const;
	void reset();

protected:
	ReferenceBase(std::list<ReferenceBase*>* referencesList, void* dataPtr);
	void addReference();

	std::list<ReferenceBase*>* m_referencesList = nullptr;
	void* m_dataPtr = nullptr;
};

bool operator==(const ReferenceBase& lhs, const ReferenceBase& rhs);
bool operator!=(const ReferenceBase& lhs, const ReferenceBase& rhs);


#endif // !H_REFERENCE_BASE
