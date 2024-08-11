#include "collision_component.h"

bool CollisionComponent::doesCollide(const CollisionComponent& other) {
    for (Hitbox* myHitbox : hitboxes) {
        for (Hitbox* otherHitbox : other.hitboxes) {
            if (myHitbox.doesCollide(otherHitbox)) {
                return true;
            }
        }
    }
    return false;
}