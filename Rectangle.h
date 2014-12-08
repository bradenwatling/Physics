#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "Object.h"

extern easygl window;

class Rectangle : public Object {
    private:
        int width, height;
        Point vertices[4];

    public:
        Rectangle(const Point &_pos, int _width, int _height);
        
        void draw() const;
        bool contains(const Point &loc) const;
        
        bool collision(const Object &obj) const;
        bool testCollision(const Rectangle &rect) const;
        bool testCollision(const Circle &circ) const;
};

#endif /* RECTANGLE_H */
