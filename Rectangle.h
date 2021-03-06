#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "Object.h"

class Rectangle : public Object {
    private:
        double width, height;
        Point vertices[4];

    public:
        Rectangle(const Point &_pos, double _width, double _height, double mass, bool fixed);
        
        void draw() const;
        bool contains(const Point &loc) const;
        
        bool collision(const Object &obj) const;
        bool testCollision(const Rectangle &rect) const;
        bool testCollision(const Circle &circ) const;
        bool testCollision(const Polygon &poly) const;
};

#endif /* RECTANGLE_H */
