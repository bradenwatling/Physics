#include <cmath>
#include "Physics.h"
#include "Object.h"

Point Object::getPos() const {
    return pos;
}

double Object::getAngle() const {
    return angle;
}

Object::Object(const Point &_pos, double _mass)
                : pos(_pos) {
    mass = _mass;
    
    angle = 0.0;
    ang_vel = 0.0;
    
    ang_acc = 0.0;
    RoG = 1.0e10;
    
    fixed_trans = false;
    fixed_rotate = false;
}

Object::~Object() {
}

void Object::update() {
    if (!fixed_trans) {
        pos += vel;
        //vel += acc;
    }
    
    if (!fixed_rotate) {
        angle += ang_vel;
        
        if (abs(angle) >= 2 * PI) {
            // Determine the angle as a proportion of 2 * PI
            double proportion = abs(angle / (2 * PI));
            proportion -= (int) proportion; // Normalize to [0, 1]
            
            angle = (angle < 0 ? -1 : 1) * proportion * 2 * PI;
        }
        
        //ang_vel += ang_acc;
    }
}

void Object::applyForce(const Point &loc, const Point &f) {
    if (!fixed_trans) {
        // F = ma
        /*acc*/ vel += f / mass;
    }
    
    if (!fixed_rotate) {
        // M = I * (alpha) where I = radius of gyration
        float moment = (loc - pos) ^ f; // Moment is distance vector x(cross) force
        /*ang_acc*/ ang_vel += moment / RoG;
    }
}

