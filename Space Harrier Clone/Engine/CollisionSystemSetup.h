#ifndef H_COLLISION_SYSTEM_SETUP
#define H_COLLISION_SYSTEM_SETUP

#include <vector>
#include <string>
#include <map>


struct CollisionSystemSetup
{
	friend class CollidersManager;

public:
	std::vector<std::string> layersNames;
	std::vector<std::vector<bool>> collisionMatrix;
	bool useZIndexWithinLayer;
	bool useZIndexAmongLayers;
	int zIndexCollisionRange;

private:
	std::map<std::string, int> namesToIndexMap;
};


#endif // !H_COLLISION_SYSTEM_SETUP
