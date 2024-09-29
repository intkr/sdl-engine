#include "collider.h"

void CircleCollider::setRadius(float _radius) {
    radius = _radius;
}

void ConvexCollider::addVertex(SDL_FPoint point) {
    // Checks if point is equal to last added vertex,
    // so that the distance between the two isn't 0.
    if (*vertices.rbegin() == point) {
        return;
    }

    vertices.push_back(point);
}

void CircleCollider::update() {
    radius = localRadius * displayTransform.scale_percent;
}

void ConvexCollider::update() {
    vertices.clear();

    double angle_deg = displayTransform.angle_deg;
    float scale_percent = displayTransform.scale_percent;
    SDL_FPoint position = displayTransform.position;

    SDL_FPoint point;
    for (SDL_FPoint& vertex : localVertices) {
        // Rotate the vertex by applying the rotation matrix,
        point.x = vertex.x * cos(rotation_deg) - vertex.y * sin(rotation_deg);
        point.y = vertex.x * sin(rotation_deg) + vertex.y * cos(rotation_deg);
        // scale and translate the vertex,
        point *= scale_percent;
        point += position;
        // and push to the new vector
        vertices.push_back(point);
    }
}

bool CircleCollider::doesCollide(const CircleCollider& other) {
    SDL_FPoint pos = displayTransform.position, otherPos = other.displayTransform.position;

    float sqDistance = (pos.x-otherPos.x)*(pos.x-otherPos.x) + (pos.y-otherPos.y)*(pos.y-otherPos.y);
    float sqRadius = (radius+other.radius) * (radius+other.radius);
    
    if (sqDistance < sqRadius) {
        return true;
    }
    else return false;
}

bool CircleCollider::doesCollide(const ConvexCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    if (!SAT(other.vertices, radius, pos)) return false;
    return true;
}

bool ConvexCollider::doesCollide(const CircleCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    if (!SAT(vertices, other.radius, otherPos)) return false;
    return true;
}


bool ConvexCollider::doesCollide(const ConvexCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    if (!SAT(vertices, other.vertices)) return false;
    if (!SAT(other.vertices, vertices)) return false;
    return true;
}

bool Collider::SAT(const std::vector<SDL_FPoint>& vertexA, const std::vector<SDL_FPoint>& vertexB) {
    std::vector<float> dotA, dotB;
    
    size_t sizeA = vertexA.size(), sizeB = vertexB.size();
    dotA.resize(sizeA);
    dotB.resize(sizeB);
    for (size_t i = 0; i < size; i++) {
        unitNormal = getUnitNormal(vertexA[i], vertexA[(i+1) % size]);

        // Project each vertex onto the axis -
        // the dot product is simply the length of the projection,
        // which is used here as float is smaller than SDL_FPoint.
        for (size_t i = 0; i < sizeA; i++) {
            dotA[i] = getDotProduct(unitNormal, vertexA[i]);
        }
        for (size_t i = 0; i < sizeB; i++) {
            dotB[i] = getDotProduct(unitNormal, vertexB[i]);
        }

        if (!checkOverlap(dotA, dotB)) {
            // These shapes do not overlap from this axis,
            // therefore these do not collide.
            return false;
        }
    }
    return true;
}

bool Collider::SAT(const std::vector<SDL_FPoint>& vertexA, const float radiusB, const SDL_FPoint& posB) {
    std::vector<float> dotA, dotB;
    float dotPosB;

    size_t size = vertexA.size();
    dotA.resize(size);
    dotB.resize(2);
    for (size_t i = 0; i < size; i++) {
        unitNormal = getUnitNormal(vertexA[i], vertexA[(i+1) % size]);

        for (size_t i = 0; i < sizeA; i++) {
            dotA[i] = getDotProduct(unitNormal, vertexA[i]);
        }
        dotPosB = getDotProduct(unitNormal, posB);
        // The maximum / minimum dot product values when projecting a circle onto an axis
        // is always the value equal to '(projection of the circle's center) +- radius'.
        // (at least that's what my intuition says, idk for sure lol)
        dotB[0] = dotPosB + other.radius;
        dotB[1] = dotPosB + other.radius * -1;

        if (!checkOverlap(dotA, dotB)) {
            return false;
        }
    }
    return true;
}

bool Collider::compare(const SDL_FPoint& a, const SDL_FPoint& b) {
    // returns true if a < b - i.e. a has lower values than b.
    // x pos takes priority over y pos.
    if (a.x < b.x) return true;
    else if (a.y < b.y) return true;
    else return false;
}

SDL_FPoint Collider::getUnitNormal(const SDL_FPoint& pointA, const SDL_FPoint& pointB) {
    SDL_FPoint normal { pointB.y-pointA.y, pointA.x-pointB.x };
    float length = sqrt(normal.x*normal.x + normal.y*normal.y);
    return (normal / length);
}

float Collider::getDotProduct(const SDL_FPoint& axis, const SDL_FPoint& vertex) {
    float dot = axis.x*vertex.x + axis.y*vertex.y;
    return dot;
}

bool Collider::checkOverlap(const std::vector<float>& dotA, const std::vector<float>& dotB) {
    float minA = std::min_element(dotA.begin(), dotA.end(), compare);
    float maxA = std::max_element(dotA.begin(), dotA.end(), compare);
    float minB = std::min_element(dotB.begin(), dotB.end(), compare);
    float maxB = std::max_element(dotB.begin(), dotB.end(), compare);

    if (!(compare(minA, maxB) && compare(minB, maxA)))
        return false;
}