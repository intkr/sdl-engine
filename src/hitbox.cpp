#include "hitbox.h"

void CircleHitbox::setRadius(float _radius) {
    radius = _radius;
}

void ConvexHitbox::addVertex(SDL_FPoint point) {
    // Checks if point is equal to last added vertex,
    // so that the distance between the two isn't 0.
    if (*vertices.rbegin() == point) {
        return;
    }

    vertices.push_back(point);
}

SDL_FPoint Hitbox::getPos() {
    Transform* currentTransform = transform;
    SDL_FPoint pos { 0, 0 };
    while (currentTransform != nullptr) {
        pos += currentTransform->position;
        currentTransform = currentTransform->parent;
    }
    return pos;
}

bool CircleHitbox::doesCollide(const CircleHitbox& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();

    float sqDistance = (pos.x-otherPos.x)*(pos.x-otherPos.x) + (pos.y-otherPos.y)*(pos.y-otherPos.y);
    float sqRadius = (radius+other.radius) * (radius+other.radius);
    
    if (sqDistance < sqRadius) {
        return true;
    }
    else return false;
}

bool CircleHitbox::doesCollide(const ConvexHitbox& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();


}

bool ConvexHitbox::doesCollide(const CircleHitbox& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();
    

}


bool ConvexHitbox::doesCollide(const ConvexHitbox& other) {
    SDL_FPoint pos = getPos(), otherPos = other.getPos();
    

}

bool Hitbox::doesOverlap(const std::vector<SDL_FPoint>& projectionA, const std::vector<SDL_FPoint>& projectionB) {
    SDL_FPoint minA = std::min_element(projectionA.begin(), projectionA.end(), compare);
    SDL_FPoint maxA = std::max_element(projectionA.begin(), projectionA.end(), compare);
    SDL_FPoint minB = std::min_element(projectionB.begin(), projectionB.end(), compare);
    SDL_FPoint maxB = std::max_element(projectionB.begin(), projectionB.end(), compare);

    return compare(minA, maxB) && compare(minB, maxA);
}

bool Hitbox::compare(const SDL_FPoint& a, const SDL_FPoint& b) {
    // returns true if a < b - i.e. a has lower values than b.
    // x pos takes priority over y pos.
    if (a.x < b.x) return true;
    else if (a.y < b.y) return true;
    else return false;
}

SDL_FPoint Hitbox::getNormalizedNormal(const SDL_FPoint& pointA, const SDL_FPoint& pointB) {
    SDL_FPoint normal { pointB.y-pointA.y, pointA.x-pointB.x };
    float length = sqrt(normal.x*normal.x + normal.y*normal.y);
    return (normal / length);
}

SDL_FPoint Hitbox::projectVertex(const SDL_FPoint& axis, const SDL_FPoint& vertex) {
    float scalar = axis.x*vertex.x + axis.y*vertex.y;
    SDL_FPoint point { scalar * axis.x, scalar * axis.y };
    return point;
}