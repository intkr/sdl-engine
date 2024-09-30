#pragma once

#include <vector>
#include <algorithm>

#include "SDL.h"

class Collider {
public:
    void setDisplayTransform(const Transform* transform) {
        displayTransform = transform;
    }

    virtual void update(const Transform* transform) = 0;

    virtual bool doesCollide(const CircleCollider* other) = 0;
    virtual bool doesCollide(const ConvexCollider* other) = 0;

protected:
    // SAT is performed using the axes derived from vertexA only.
    bool SAT(const std::vector<SDL_FPoint>& vertexA, const std::vector<SDL_FPoint>& vertexB);
    bool SAT(const std::vector<SDL_FPoint>& vertexA, const float radiusB, const SDL_FPoint& posB);

private:
    bool compare(const SDL_FPoint& a, const SDL_FPoint& b);
    // Returns the unit normal vector of the edge from pointA to pointB.
    SDL_FPoint getUnitNormal(const SDL_FPoint& pointA, const SDL_FPoint& pointB);
    // Returns the length of the projection of the vertex onto the axis.
    float getDotProduct(const SDL_FPoint& axis, const SDL_FPoint& vertex);

    bool checkOverlap(const std::vector<float>& dotA, const std::vector<float>& dotB);
};

class CircleCollider : public Collider {
public:
    void setCenter(SDL_FPoint _center) { localCenter = _center; }
    void setRadius(float _radius) { localRadius = _radius; }

    void update(const Transform* transform) override;
    
    bool doesCollide(const CircleCollider* other) override;
    bool doesCollide(const ConvexCollider* other) override;

private:
    SDL_FPoint localCenter;
    SDL_FPoint center;

    float localRadius;
    float radius;
};

class ConvexCollider : public Collider {
public:
    void addVertex(SDL_FPoint point);

    void update(const Transform* transform) override;

    bool doesCollide(const CircleCollider* other) override;
    bool doesCollide(const ConvexCollider* other) override;

private:
    std::vector<SDL_FPoint> localVertices;
    std::vector<SDL_FPoint> vertices;
};