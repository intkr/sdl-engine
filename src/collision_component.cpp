#include "collision_component.h"

bool CollisionComponent::doesCollide(const CollisionComponent& other) {
    if (doesAABBintersect(other)) {
        doesHitboxIntersect(other)) {
            return true;
        }
    }
    return false;
}

bool CollisionComponent::doesAABBintersect(const CollisionComponent& other) {
    return true;
    // idk how to implement this for now
    // problem 1) the transform may have rotation, as well its parent(s)
    //              -> check two rotating boxes, or aabb of the rotated box?
    // problem 2) each hitbox may change position/scale/rotation
    //              -> aabb needs to update, otherwise hitbox may go outside aabb
}

bool CollisionComponent::doesHitboxIntersect(const CollisionComponent& other) {
    for (Hitbox* myHitbox : hitboxes) {
        for (Hitbox* otherHitbox : other.hitboxes) {
            if (myHitbox.doesCollide(otherHitbox)) {
                return true;
            }
        }
    }
    return false;
}