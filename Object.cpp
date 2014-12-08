#include <cmath>
#include "Physics.h"
#include "Object.h"

Point Object::rotate(const Point &p) const {
    double cosine = cos(angle), sine = sin(angle);
    float x = p.getX(), y = p.getY();
    
    return Point(cosine * x - sine * y, sine * x + cosine * y);
}

void Object::addToVertices(t_point *vertices, int index, const Point &p) {
    vertices[index].x = p.getX();
    vertices[index].y = p.getY();
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
    
    lastTranslateTime = 0;
    lastRotateTime = 0;
}

Object::~Object() {
}

Point Object::getPos() const {
    return pos;
}

double Object::getAngle() const {
    return angle;
}

double Object::getMass() const {
    return mass;
}

void Object::update(double curTime) {
    // If the time is greater than 1 pixel * 1 / (vel [pixels/sec])
    if (!fixed_trans && vel.getMag() != 0.0 && curTime - lastTranslateTime > 1.0 / vel.getMag()) {
        pos += vel / vel.getMag() * 0.1;

        lastTranslateTime = curTime;
    }
    
    // If the time is greater than 1 rad * 1 / (ang_vel [rad/sec])
    if (!fixed_rotate && ang_vel != 0.0 && curTime - lastRotateTime > 1.0 / ang_vel) {
        angle += PI / 180.0;//ang_vel;
        
        if (abs(angle) >= 2 * PI) {
            // Determine the angle as a proportion of 2 * PI
            double proportion = abs(angle / (2 * PI));
            proportion -= (int) proportion; // Normalize to [0, 1]
            
            angle = (angle < 0 ? -1 : 1) * proportion * 2 * PI;
        }
        
        lastRotateTime = curTime;
    }
}

void Object::applyForce(const Point &loc, const Point &f) {
    if (!fixed_trans) {
        // F = ma
        vel += f / mass;
    }
    
    if (!fixed_rotate) {
        // M = I * (alpha) where I = radius of gyration
        float moment = loc ^ f; // Moment is distance vector x(cross) force
        ang_vel += moment / RoG;
    }
}

