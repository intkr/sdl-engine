#pragma once
#include <vector>

#include "SDL.h"

#include "object_enum.h"
#include "transform.h"
#include "collider.h"

class CollisionComponent {
public:
    ~CollisionComponent();
	void initFromFile(std::string path);
    
    // Creates a convex collider shape binded to the given sprite's display.
    void addConvexCollider(const Transform* displayTransform);
    // Creates a circular collider shape binded to the given sprite's display.
    void addCircleCollider(const Transform* displayTransform);
    
    void setObjectTransform(const Transform* transform) {
        objectTransform = transform;
    }

    void update();
	bool doesCollide(const CollisionComponent& other);
    
private:
    bool doesAABBintersect(const CollisionComponent& other);
    bool doesColliderIntersect(const CollisionComponent& other);

    ObjectType objectType;
    // The AABB should be large enough to fit all collision shapes' movements.
    SDL_FRect aabb;

    std::vector<Collider*> colliders;

    const Transform* objectTransform;
};