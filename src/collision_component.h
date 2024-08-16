#pragma once
#include <vector>

#include "SDL.h"

#include "object_enum.h"
#include "transform.h"
#include "hitbox.h"

class CollisionComponent {
public:
	void initFromFile(std::string path);
    // TODO: this
    void addConvexCollider(const Transform* parentTransform);
    void addCircleCollider(const Transform* parentTransform);
    // set parent to object
    void setParentTransform(const Transform* parentTransform) {
        transform.parent = parentTransform;
    }

	bool doesCollide(const CollisionComponent& other);
    
private:
    bool doesAABBintersect(const CollisionComponent& other);
    bool doesColliderIntersect(const CollisionComponent& other);

    ObjectType objectType;
    // The AABB should be large enough to fit all collision shapes' movements.
    SDL_FRect aabb;

    std::vector<Collider*> hitboxes;
    Transform transform;
};