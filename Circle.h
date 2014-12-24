#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include "Object.h"

class Circle : public Object {
    private:
        double radius;
        static const Point testPoints[];

    public:
        Circle(const Point &_pos, double _radius, double mass, bool fixed);
        
        void draw() const;
        bool contains(const Point &loc) const;
        
        bool collision(const Object &obj) const;
        bool testCollision(const Rectangle &rect) const;
        bool testCollision(const Circle &circ) const;
        bool testCollision(const Polygon &poly) const;
};

#endif /* CIRCLE_H */
