#pragma once
#include <vector>

#include "SDL.h"

#include "engine/transform.h"
#include "engine/motion.h"

class DisplayComponent {
public:
	void initFromFile(std::string path);
    void setSpriteTransform(const Transform* spriteTransform) {
        transform = spriteTransform;
    }

	void update(ms delta);
    
private:
    void loadMotionFromFile(std::string path);
    void applyMotion(ms delta);


    std::vector<Motion> motions;
    std::vector<Motion>::iterator currentMotion;

    Transform* transform;
};