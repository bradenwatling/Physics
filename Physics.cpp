#include <iostream>

using namespace std;

#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"

easygl window("Resistor display", WHITE);

Physics::Physics() {    
    objects.push_back(new Rectangle(Point(0, 0), 10, 10));
    (*objects.begin())->applyForce(Point(2, 3), Point(-5, 0));
    
    window.set_world_coordinates(-10, -10, 10, 10);
}

Physics::~Physics() {
    for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
        delete *iter;
    }
}

void Physics::run() {
    double now = (double) clock() * SEC_PER_CLOCK;
    
    if (now - lastUpdate > 0.05) {
        (*objects.begin())->applyForce(Point(2, 3), Point(1, 0));
        
        for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
            (*iter)->update();
        }
        
        lastUpdate = now;
    }
    
    if (now - lastDraw > 0.03) {
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
