#pragma once

// spoiler - hitboxes arent boxes


class Hitbox {
public:
    // set parent to sprite display
    void setParentTransform(const Transform* parentTransform) {
        transform.parent = parentTransform;
    }

protected:
    Transform transform;
};

class CircleHitbox : public Hitbox {
public:

private:

};

class ConvexHitbox : public Hitbox {
public:

private:
    Transform transform;
};