#ifndef H_TRIGGER_COLLISION_CACHE
#define H_TRIGGER_COLLISION_CACHE

#include <vector>
#include "Reference.h"
class Collider;


using CollidersPair = std::pair<Reference<Collider>, Reference<Collider>>;
class TriggerCollisionCache final
{
public:
	bool cache(const CollidersPair& collPair);
	void refresh();

private:
	int indexOf(const std::vector<CollidersPair>& collPairVector, const CollidersPair& collPair);

	std::vector<CollidersPair> m_collPairs;
	std::vector<CollidersPair> m_registeredCollPairs;
};


#endif // !H_TRIGGER_COLLISION_CACHE
