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
        Rectangle(const Point &_pos, int _width, int _height) : Object(_pos, 1) {
            RoG = 100000;
            width = _width;
            height = _height;
            fixed_trans = true;
        }
        
        void draw() {
            t_point coords[4];
            
            Point pos = getPos();
            float x = pos.getX(), y = pos.getY();
            double angle = getAngle();
            
            coords[0].x = x - width * cos(2 * angle);
            coords[0].y = y - height * sin(2 * angle);
            
            coords[1].x = x - width * sin(2 * angle);
            coords[1].y = y + height * cos(2 * angle);
            
            coords[2].x = x + width * cos(2 * angle);
            coords[2].y = y + height * sin(2 * angle);
            
            coords[3].x = x + width * sin(2 * angle);
            coords[3].y = y - height * cos(2 * angle);
            
            window.gl_setcolor(RED);
            window.gl_fillpoly(coords, 4);
        }

        bool contains(const Point &loc) {
            return true;
        }

        bool collision(const Object &obj) {
            return false;
        }
};

#endif /* RECTANGLE_H */
