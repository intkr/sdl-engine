#pragma once
#include <vector>

#include "SDL.h"

#include "engine/object_enum.h"
#include "engine/transform.h"
#include "engine/collider.h"

class CollisionComponent {
public:
    CollisionComponent(const Transform* transform) : spriteTransform(transform) {}
    ~CollisionComponent();
    
	void initFromFile(std::string path);
    
    // Creates a convex collider shape binded to the given sprite.
    void addConvexCollider(const Transform* spriteTransform);
    // Creates a circular collider shape binded to the given sprite.
    void addCircleCollider(const Transform* spriteTransform);

    void update();
	bool doesCollide(const CollisionComponent& other);
    
private:
    bool doesAABBintersect(const CollisionComponent& other);
    bool doesColliderIntersect(const CollisionComponent& other);

    ObjectType objectType;
    // The AABB should be large enough to fit all collision shapes' movements.
    SDL_FRect aabb;

    std::vector<Collider*> colliders;

    const Transform* spriteTransform;
};

/*
TODO: need to rewrite collision component / collider code

- spriteTransform (previously objectTransform) is completely unused rn, it serves no purpose
- CircleCollider has no variable for the center point - it just assumes the center is (0,0) for some reason
- since displayTransform (in collider) is just spriteTransform (in collision component) now,
  code should reflect that change accordingly
- collider data may need changes that sync enough with the sprite texture changes (i.e. animations),
*/