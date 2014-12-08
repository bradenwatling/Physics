#include "Rectangle.h"

Rectangle::Rectangle(const Point &_pos, int _width, int _height)
                        : Object(_pos, 100) {
    RoG = 1000;
    width = _width;
    height = _height;
    //fixed_trans = true;
}

void Rectangle::draw() {
    t_point coords[4];

    Point pos = getPos();
    float x = pos.getX(), y = pos.getY();
    double angle = getAngle();

    coords[0].x = x - width * cos(angle);
    coords[0].y = y - height * sin(angle);

    coords[1].x = x - width * sin(angle);
    coords[1].y = y + height * cos(angle);

    coords[2].x = x + width * cos(angle);
    coords[2].y = y + height * sin(angle);

    coords[3].x = x + width * sin(angle);
    coords[3].y = y - height * cos(angle);

    window.gl_setcolor(RED);
    window.gl_fillpoly(coords, 4);
}

bool Rectangle::contains(const Point &loc) {
    return true;
}

bool Rectangle::collision(const Object &obj) {
    return false;
}
