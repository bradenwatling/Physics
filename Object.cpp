#include "Object.h"

Point Object::getPos() const {
    return pos;
}

double Object::getAngle() const {
    return angle;
}

Object::Object(const Point &_pos, float _mass)
                : pos(_pos) {
    mass = _mass;
    
    angle = 3.14159f / 4.0f;
    ang_vel = 0.0f;
    
    ang_acc = 0.0f;
    RoG = 1.0e10f;
    
    fixed_trans = false;
    fixed_rotate = false;
}

Object::~Object() {
}

void Object::update() {
    if (!fixed_trans) {
        pos += vel;
        vel += acc;
    }
    
    if (!fixed_rotate) {
        angle += ang_vel;
        ang_vel += ang_acc;
    }
}

void Object::applyForce(const Point &loc, const Point &f) {
    if (!fixed_trans) {
        // F = ma
        acc += f / mass;
    }
    
    if (!fixed_rotate) {
        // M = I * (alpha) where I = radius of gyration
        float moment = (loc - pos) ^ f; // Moment is distance vector x(cross) force
        ang_acc += moment / RoG;
    }
}

