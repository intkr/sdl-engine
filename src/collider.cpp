#include "hitbox.h"

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
    updateTransform();
    radius = localRadius * transform.scale_percent;
}

void ConvexCollider::update() {
    updateTransform();
    transformVertices();
}

void Collider::updateTransform() {
    finalTransform = *displayTransform;
    Transform* currentTransform = displayTransform;
    while (currentTransform != nullptr) {
        finalTransform.position *= currentTransform->scale_percent;
        finalTransform.position += currentTransform->position;
        finalTransform.scale_percent *= currentTransform->scale_percent;
        finalTransform.angle_deg += currentTransform->angle_deg;
        currentTransform = currentTransform->parent;
    }
}

void ConvexCollider::transformVertices() {
    vertices.clear();
    // rotate
    SDL_FPoint point;
    double angle_deg = transform.angle_deg;
    for (SDL_FPoint& vertex : localVertices) {
        // Apply rotation matrix on each vertex
        point.x = vertex.x * cos(rotation_deg) - vertex.y * sin(rotation_deg);
        point.y = vertex.x * sin(rotation_deg) + vertex.y * cos(rotation_deg);
        // and push to the new vector
        vertices.push_back(point);
    }
    // scale
    
    // translate
}

SDL_FPoint Collider::getPos() {
    Transform* currentTransform = displayTransform;
    SDL_FPoint pos { 0, 0 };
    while (currentTransform != nullptr) {
        pos += currentTransform->position;
        currentTransform = currentTransform->parent;
    }
    return pos;
}

bool CircleCollider::doesCollide(const CircleCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    float sqDistance = (pos.x-otherPos.x)*(pos.x-otherPos.x) + (pos.y-otherPos.y)*(pos.y-otherPos.y);
    float sqRadius = (radius+other.radius) * (radius+other.radius);
    
    if (sqDistance < sqRadius) {
        return true;
    }
    else return false;
}

bool CircleCollider::doesCollide(const ConvexCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    if (!SAT(other.vertices, otherPos, radius, pos)) return false;
    return true;
}

bool ConvexCollider::doesCollide(const CircleCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    if (!SAT(vertices, pos, other.radius, otherPos)) return false;
    return true;
}


bool ConvexCollider::doesCollide(const ConvexCollider& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    if (!SAT(vertices, pos, other.vertices, otherPos)) return false;
    if (!SAT(other.vertices, otherPos, vertices, pos)) return false;
    return true;
}

bool Collider::SAT(const std::vector<SDL_FPoint>& vertexA, const SDL_FPoint posA, const std::vector<SDL_FPoint>& vertexB, const SDL_FPoint posB) {
    std::vector<float> dotA, dotB;
    SDL_FPoint unitNormal, dotPosA, dotPosB;
    size_t size = vertexA.size();
    for (size_t i = 0; i < size; i++) {
        unitNormal = getUnitNormal(vertexA[i], vertexA[(i+1) % size]);

        dotPosA = getDot(unitNormal, pos);
        dotPosB = getDot(unitNormal, otherPos);

        // Project each vertex onto the axis -
        // the dot product is simply the length of the projection,
        // which is used here as float is smaller than SDL_FPoint.
        for (SDL_FPoint& vertex : vertexA) {
            dotA.push_back(getDot(unitNormal, vertex));
        }
        for (SDL_FPoint& vertex : vertexB) {
            dotB.push_back(getDot(unitNormal, vertex));
        }

        if (!checkOverlap(dotA, dotPosA, dotB, dotPosB)) {
            // These shapes do not overlap from this axis,
            // therefore these do not collide.
            return false;
        }
    }

    return true;
}

bool Collider::SAT(const std::vector<SDL_FPoint>& vertexA, const SDL_FPoint posA, const float radiusB, const SDL_FPoint posB) {
    std::vector<float> dotA, dotB;
    SDL_FPoint unitNormal, dotPosA, dotPosB;
    size_t size = vertexA.size();
    for (size_t i = 0; i < size; i++) {
        unitNormal = getUnitNormal(vertexA[i], vertexA[(i+1) % size]);

        dotPosA = getDot(unitNormal, pos);
        dotPosB = getDot(unitNormal, otherPos);
        for (SDL_FPoint& vertex : vertexA) {
            dotA.push_back(getDot(unitNormal, vertex));
        }
        
        // The maximum / minimum values when projecting a circle onto an axis
        // is always the value equal to radius, positive / negative.
        // (at least that's what my intuition says, idk for sure lol)
        dotB.push_back(other.radius);
        dotB.push_back(other.radius * -1);

        if (!checkOverlap(dotA, dotPosA, dotB, dotPosB)) {
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

bool Collider::checkOverlap(const std::vector<float>& dotA, const float dotPosA, const std::vector<float>& dotB, const float dotPosB) {
    float minA = std::min_element(dotA.begin(), dotA.end(), compare);
    float maxA = std::max_element(dotA.begin(), dotA.end(), compare);
    float minB = std::min_element(dotB.begin(), dotB.end(), compare);
    float maxB = std::max_element(dotB.begin(), dotB.end(), compare);

    // Since the values of both dot vectors are local to position (0,0),
    // they need to be offset by the dot product of the shape's position and the separating axis
    // in order to correctly check the overlap between the projected vertices.
    if (!(compare(minA + dotPosA, maxB + dotPosB) && compare(minB + dotPosB, maxA + dotPosA)))
        return false;
}