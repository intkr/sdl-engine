#pragma once

// idk if i did this right

SDL_FPoint operator+(SDL_FPoint point, const SDL_FPoint& other) {
    point.x += other.x;
    point.y += other.y;
    return point;
}

SDL_FPoint operator-(SDL_FPoint point, const SDL_FPoint& other) {
    point.x -= other.x;
    point.y -= other.y;
    return point;
}

SDL_FPoint operator*(SDL_FPoint point, const float& scalar) {
    point.x *= scalar;
    point.y *= scalar;
    return point;
}

SDL_FPoint operator/(SDL_FPoint point, const float& scalar) {
    point.x /= scalar;
    point.y /= scalar;
    return point;
}