#include "animation.h"

SDL_Rect Animation::getBox() {
    SDL_Rect box;
    int row = currentFrame->row;
    int column = currentFrame->column;

    box.w = baseBox.w;
    box.h = baseBox.h;

    box.x = baseBox.x + box.w * column;
    box.y = baseBox.y + box.h * row;

    return box;
}
