#pragma once
#include <vector>

#include "SDL.h"

#include "object_enum.h"
#include "transform.h"
#include "motion.h"

class CollisionComponent {
public:
	void initFromFile(std::string path);
    // set parent to object
    void setParentTransform(const Transform* parentTransform) {
        transform.parent = parentTransform;
    }

	bool doesCollide(const CollisionComponent& other);
    
private:
    ObjectType objectType;
    std::vector<Hitbox> hitboxes;
    Transform transform;
};