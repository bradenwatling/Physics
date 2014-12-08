#include <iostream>

using namespace std;

#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"
#include "Polygon.h"

easygl window("Resistor display", WHITE);

Physics::Physics() {
    objects.push_back(new Rectangle(Point(0, -30), 100, 20, 10, true));
    objects.push_back(new Rectangle(Point(12, 0), 6, 8, 50, false));
    objects.push_back(new Rectangle(Point(-8, -4), 4, 8, 5, false));
    
    Point points[5];
    for (int i = 0; i < 5; i++) {
        points[i].setXY(5 * cos(i * 2 * PI / 5), 5 * sin(i * 2 * PI / 5));
    }
    
    objects.push_back(new Polygon(Point(0, -10), points, 5, 60, false));
    
    objects[1]->applyForce(Point(-5, 5), Point(-40000, 180000) / 2.2 * 4);
    objects[2]->applyForce(Point(30, 5), Point(200, 8000) * 2);
    objects[3]->applyForce(Point(6, 0), Point(0, 100000));
    
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
            // If two Objects are colliding
            if (i != j && ((*i)->collision(**j) || (*j)->collision(**i))) {
                // Calculate the new linear/angular velocities of each Object
                Point iVel = (*i)->getVel(), jVel = (*j)->getVel();
                
                double iMass = (*i)->getMass(), jMass = (*j)->getMass();
                double iAngVel = (*i)->getAngVel(), jAngVel = (*j)->getAngVel();
                
                double totalMass = iMass + jMass, totalAngVel = iAngVel + jAngVel;
                
                double iMoment = iMass * totalAngVel / totalMass;
                double jMoment = jMass * totalAngVel / totalMass;
                
                if ((*i)->isFixedTrans()) {
                    (*j)->setFixedTrans(true);
                }
                
                if ((*j)->isFixedTrans()) {
                    (*i)->setFixedTrans(true);
                }
                
                // Subtract 1 to cancel the velocity that each Object had previously
                // Add the velocities, multiplied by the proportion of total mass going in the corresponding direction
                Point iVelNew = iVel * (iMass / totalMass - 1) + jVel * (jMass / totalMass);
                Point jVelNew = jVel * (jMass / totalMass - 1) + iVel * (iMass / totalMass);
                
                // Multiplying by mass/RoG because when we apply a force, we divide by mass/RoG
                (*i)->applyForce(iVelNew * iMass, (iAngVel + iMoment) * -(*i)->getRoG());
                (*j)->applyForce(jVelNew * jMass, (jAngVel + jMoment) * -(*j)->getRoG());
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
