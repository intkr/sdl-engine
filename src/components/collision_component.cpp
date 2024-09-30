#include "collision_component.h"

CollisionComponent::~CollisionComponent() {
    for (Collider* collider : colliders) {
        delete collider;
    }
}

void CollisionComponent::addConvexCollider(const Transform* displayTransform) {
    ConvexCollider* collider = new ConvexCollider();
    collider.setDisplayTransform(displayTransform);
    colliders.push_back(collider);
}

void CollisionComponent::addCircleCollider(const Transform* displayTransform) {
    CircleCollider* collider = new ConvexCollider();
    collider.setDisplayTransform(displayTransform);
    colliders.push_back(collider);
}

void CollisionComponent::update() {
    for (Collider* collider : colliders) {
        collider->update(spriteTransform);
    }
}

bool CollisionComponent::doesCollide(const CollisionComponent& other) {
    if (doesAABBintersect(other)) {
        if (doesColliderIntersect(other)) {
            return true;
        }
    }
    return false;
}

bool CollisionComponent::doesAABBintersect(const CollisionComponent& other) {
/*  add AABB later at home when profiling is possible,
    because working on AABB data for each sprite may be overkill if it doesnt do much

     if (aabb.x+aabb.w < other.aabb.x || other.aabb.x+other.aabb.w < aabb.x) {
        return false;
    }
    if (aabb.y+aabb.h < other.aabb.y || other.aabb.y+other.aabb.h < aabb.y) {
        return false;
    } */
    return true;
}

bool CollisionComponent::doesColliderIntersect(const CollisionComponent& other) {
    for (Collider* collider : hitboxes) {
        for (Collider* otherCollider : other.hitboxes) {
            if (collider.doesCollide(otherCollider)) {
                return true;
            }
        }
    }
    return false;
}