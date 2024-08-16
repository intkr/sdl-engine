#include "collision_component.h"

bool CollisionComponent::doesCollide(const CollisionComponent& other) {
    if (doesAABBintersect(other)) {
        if (doesColliderIntersect(other)) {
            return true;
        }
    }
    return false;
}

bool CollisionComponent::doesAABBintersect(const CollisionComponent& other) {
    if (aabb.x+aabb.w < other.aabb.x || other.aabb.x+other.aabb.w < aabb.x) {
        return false;
    }
    if (aabb.y+aabb.h < other.aabb.y || other.aabb.y+other.aabb.h < aabb.y) {
        return false;
    }
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