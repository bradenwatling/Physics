#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"

easygl window("Resistor display", WHITE);

Physics::Physics() : t(&Physics::run, this) {
    objects.push_back(new Rectangle(Point(0, 0), 10, 10));
    (*objects.begin())->applyForce(Point(2, 3), Point(1, 1));
}

Physics::~Physics() {
    for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
        delete *iter;
    }
}

void Physics::run() {
    while (true) {
        x++;
        if (x % 1000000 == 0) {
            for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
                (*iter)->update();
            }
            draw();
        }
    }
}

void Physics::draw() {
    window.gl_clearscreen();
    
    for (vector<Object *>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
        (*iter)->draw();
    }
}
