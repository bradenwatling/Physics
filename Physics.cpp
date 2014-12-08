#include <iostream>

using namespace std;

#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"

easygl window("Resistor display", WHITE);

Physics::Physics() {    
    objects.push_back(new Rectangle(Point(0, 0), 10, 10));
    objects[0]->applyForce(Point(1, 5), Point(0, 100));
    
    window.set_world_coordinates(-100, -100, 100, 100);
}

Physics::~Physics() {
    for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
        delete *iter;
    }
}

void Physics::run() {
    double now = (double) clock() * SECS_PER_CLOCK;
    
    if (now - lastUpdate > 0.05) {
        for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
            (*iter)->applyForce(Point(0, 0), Point(0, -100 * (*iter)->getMass()));
        }
        
        lastUpdate = now;
    }
    
    for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
        (*iter)->update(now);
    }
    
    if (now - lastDraw > SPF) {
        draw();
        window.gl_flush();
        
        lastDraw = now;
    }
}

void Physics::draw() {
    window.gl_clearscreen();
    
    for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
        (*iter)->draw();
    }
}
