#pragma once

// small memo just in case i forget why this exists:
// 'Sprite/Text component' only gives information about where to get the texture from
// 'Display component' gives information about where to put the texture on the screen
// both of which is then used by the 'Render component' to be rendered on the screen

/* Important note:
Only 'renderBox' holds geometric data relative to the game window (which is used to render),
all other boxes hold geometric data that is *relative* to the game object's position.
In other words, (x=0, y=0) in these boxes does NOT mean the top left corner of the window.
*/

class DisplayComponent {
    friend class RenderComponent;
public:
    DisplayComponent(Position* position) : centerPos(position) {}

    // TODO: get the old animation related code in here and transform.h/.cpp
private:
	void transform();

    // This points to the position of the object this component is part of.
    const Position* centerPos;

    // Pre-transform, object-relative box.
    // Contains the original values to perform calculations on.
    SDL_FRect baseBox;
    // Post-transform, object-relative box.
    // Contains the values after transforms are applied.
    SDL_FRect modBox;
    // Post-transform, window-relative box.
    // Contains the final values to be used on rendering.
    SDL_FRect renderBox;
};