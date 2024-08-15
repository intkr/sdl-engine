#pragma once

#include <vector>
#include <algorithm>

#include "SDL.h"

// spoiler - hitboxes arent boxes


class Hitbox {
public:
    // set parent to sprite display
    void setParentTransform(const Transform* parentTransform) {
        transform.parent = parentTransform;
    }

    virtual bool doesCollide(const CircleHitbox* other) = 0;
    virtual bool doesCollide(const ConvexHitbox* other) = 0;

protected:
    bool doesOverlap(const std::vector<SDL_FPoint>& projectionA, const std::vector<SDL_FPoint>& projectionB);
    SDL_FPoint getNormalizedNormal(const SDL_FPoint& pointA, const SDL_FPoint& pointB);
    SDL_FPoint projectVertex(const SDL_FPoint& axis, const SDL_FPoint& vertex);
    bool compare(const SDL_FPoint& a, const SDL_FPoint& b);

    SDL_FPoint getPos();

    bool active;
    Transform transform;
};

class CircleHitbox : public Hitbox {
public:
    void setRadius(float _radius);

    bool doesCollide(const CircleHitbox* other) override;
    bool doesCollide(const ConvexHitbox* other) override;

private:
    float radius;
};

class ConvexHitbox : public Hitbox {
public:
    void addVertex(SDL_FPoint point);

    bool doesCollide(const CircleHitbox* other) override;
    bool doesCollide(const ConvexHitbox* other) override;

private:
    std::vector<SDL_FPoint> vertices;
};