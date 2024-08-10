#pragma once
#include <vector>

#include "SDL.h"

#include "transform.h"
#include "motion.h"

class DisplayComponent {
public:
	void initFromFile(std::string path);
    void setParentTransform(const Transform* parentTransform) {
        transform.parent = parentTransform;
    }

	void update(ms delta);

    Transform getTransform();
    
private:
    void loadMotionFromFile(std::string path);
    void applyMotion(ms delta);


    std::vector<Motion> motions;
    std::vector<Motion>::iterator currentMotion;

    Transform transform;
};