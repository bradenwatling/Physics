#include <cmath>
#include "Polygon.h"
#include "Rectangle.h"
#include "Circle.h"

#define ONE_OVER_ROOT_TWO 0.70710678118
#define NUM_TEST_POINTS 9

const Point Circle::testPoints[] = {
    Point(0, 0),
    Point(1, 0),
    Point(ONE_OVER_ROOT_TWO, ONE_OVER_ROOT_TWO),
    Point(0, 1),
    Point(-ONE_OVER_ROOT_TWO, ONE_OVER_ROOT_TWO),
    Point(-1, 0),
    Point(-ONE_OVER_ROOT_TWO, -ONE_OVER_ROOT_TWO),
    Point(0, -1),
    Point(ONE_OVER_ROOT_TWO, -ONE_OVER_ROOT_TWO),
};

Circle::Circle(const Point &_pos, double _radius, double mass, bool fixed)
                        : Object(_pos, mass) {
    radius = _radius;
    
    RoG = PI * radius * radius;
    RoG *= RoG;
    
    fixed_trans = fixed;
    fixed_rotate = fixed;
}

void Circle::draw() const {
    Point pos = getPos();

    window.gl_setcolor(RED);
    window.gl_fillarc(pos.getX(), pos.getY(), radius, 0, 360);
}

bool Circle::contains(const Point &loc) const {
    return (loc - getPos()).getMag() <= radius;
}

bool Circle::collision(const Object &obj) const {
    return obj.testCollision(*this);
}

bool Circle::testCollision(const Rectangle &rect) const {
    Point pos = getPos();
    
    for (int i = 0; i < NUM_TEST_POINTS; i++) {
        if (rect.contains(pos + testPoints[i] * radius)) {
            return true;
        }
    }
    
    return false;
}

bool Circle::testCollision(const Circle &circ) const {
    return (getPos() - circ.getPos()).getMag() <= radius + circ.radius;
}

bool Circle::testCollision(const Polygon &poly) const {
    Point pos = getPos();
    
    for (int i = 0; i < NUM_TEST_POINTS; i++) {
        if (poly.contains(pos + testPoints[i] * radius)) {
            return true;
        }
    }
    
    return false;
}

