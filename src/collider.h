#pragma once

#include <vector>
#include <algorithm>

#include "SDL.h"

// TODO: the vertices need to be rotated / resized based on transform

class Collider {
public:
    void setDisplayTransform(const Transform* transform) {
        displayTransform = transform;
    }

    virtual bool doesCollide(const CircleCollider* other) = 0;
    virtual bool doesCollide(const ConvexCollider* other) = 0;

protected:
    // SAT is performed using the axes derived from vertexA only.
    bool SAT(const std::vector<SDL_FPoint>& vertexA, const SDL_FPoint posA, const std::vector<SDL_FPoint>& vertexB, const SDL_FPoint posB);
    bool SAT(const std::vector<SDL_FPoint>& vertexA, const SDL_FPoint posA, const float radiusB, const SDL_FPoint posB);

    bool compare(const SDL_FPoint& a, const SDL_FPoint& b);
    // Returns the unit normal vector of the edge from pointA to pointB.
    SDL_FPoint getUnitNormal(const SDL_FPoint& pointA, const SDL_FPoint& pointB);
    // Returns the length of the projection of the vertex onto the axis.
    float getDotProduct(const SDL_FPoint& axis, const SDL_FPoint& vertex);

    bool checkOverlap(const std::vector<float>& dotA, const float dotPosA, const std::vector<float>& dotB, const float dotPosB);
    
    void updateTransform();
    SDL_FPoint getPos();

    const Transform* displayTransform;
    // Fully calculated transform based on display/parent transforms.
    Transform finalTransform;
};

class CircleCollider : public Collider {
public:
    void setRadius(float _radius);

    void update();
    
    bool doesCollide(const CircleCollider* other) override;
    bool doesCollide(const ConvexCollider* other) override;

private:
    float localRadius;
    float radius;
};

class ConvexCollider : public Collider {
public:
    void addVertex(SDL_FPoint point);

    void update();

    bool doesCollide(const CircleCollider* other) override;
    bool doesCollide(const ConvexCollider* other) override;

private:
    void transformVertices();
    // Unrotated vertex data should be stored here.
    std::vector<SDL_FPoint> localVertices;
    std::vector<SDL_FPoint> vertices;
};