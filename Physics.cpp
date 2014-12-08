#include <iostream>

using namespace std;

#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"

easygl window("Resistor display", WHITE);

Physics::Physics() {
    objects.push_back(new Rectangle(Point(0, -30), 100, 20, 100, true));
    objects.push_back(new Rectangle(Point(12, 0), 3, 8, 100, false));
    objects.push_back(new Rectangle(Point(-8, 0), 4, 8, 5, false));
    
    
    objects[1]->applyForce(Point(-5, 5), Point(-40000, 180000));
    objects[2]->applyForce(Point(-30, 5), Point(500, 8000));
    
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
        for (vector<Object *>::iterator i = objects.begin(); i != objects.end(); i++) {
            // Gravity
            (*i)->applyForce(Point(0, 0), Point(0, -100 * (*i)->getMass()));
        }
        
        lastUpdate = now;
    }
    
    for (vector<Object *>::iterator i = objects.begin(); i != objects.end(); i++) {
        // Iterate over each unique pair
        for (vector<Object *>::iterator j = i + 1; j != objects.end(); j++) {
            if (i != j && ((*i)->collision(**j) || (*j)->collision(**i))) {
                // MoI1 * w1 + MoI2 * w2 = MoI1 * w1' + MoI2 * w2'
                
                Point iVel = (*i)->getVel(), jVel = (*j)->getVel();
                
                double iMass = (*i)->getMass(), jMass = (*j)->getMass();
                double iAngVel = (*i)->getAngVel(), jAngVel = (*j)->getAngVel();
                
                double iMoment = iMass / (iMass + jMass) * (iAngVel + jAngVel);
                double jMoment = jMass / (iMass + jMass) * (iAngVel + jAngVel);
                
                // Swap the linear velocities
                (*i)->applyForce(iVel * -iMass + jVel * iMass, (iAngVel + iMoment) * -(*i)->getRoG());
                (*j)->applyForce(jVel * -jMass + iVel * jMass, (jAngVel + jMoment) * -(*j)->getRoG());
            }
        }
        
        (*i)->update(now);
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
