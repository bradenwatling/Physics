#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "easygl.h"
#include "Object.h"

extern easygl window;

class Rectangle : public Object {
    private:
        int width, height;

    public:
        Rectangle(const Point &_pos, int _width, int _height);
        
        void draw();
        bool contains(const Point &loc);
        bool collision(const Object &obj);
};

#endif /* RECTANGLE_H */
