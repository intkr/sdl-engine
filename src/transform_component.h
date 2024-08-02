#pragma once

class Transform {
public:
    // idk lol wtf do i add here

    const Position& getPosition() { return position; }
    const double getRotation() { return rotation_deg; }
    const double getScale() { return scale_percent; }
    
private:
    Position position;
    double rotation_deg;
    double scale_percent;
};