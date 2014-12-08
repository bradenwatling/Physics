#include "Rectangle.h"

Rectangle::Rectangle(const Point &_pos, int _width, int _height)
                        : Object(_pos, 100) {
    RoG = 1;
    width = _width;
    height = _height;
    vertices[0] = Point(-width, -height);
    vertices[1] = Point(-width, height);
    vertices[2] = Point(width, height);
    vertices[3] = Point(width, -height);
    fixed_trans = true;
}

void Rectangle::draw() const {
    t_point coords[4];

    Point pos = getPos();
    float x = pos.getX(), y = pos.getY();
    double angle = getAngle();
    
    addToVertices(coords, 0, rotate(vertices[0]));
    addToVertices(coords, 1, rotate(vertices[1]));
    addToVertices(coords, 2, rotate(vertices[2]));
    addToVertices(coords, 3, rotate(vertices[3]));

    /*coords[0].x = x + row1 * vertices[0];
    coords[0].y = y + row2 * vertices[0];

    coords[1].x = x + row1 * vertices[1];
    coords[1].y = y + row2 * vertices[1];

    coords[2].x = x + row1 * vertices[2];
    coords[2].y = y + row2 * vertices[2];

    coords[3].x = x + row1 * vertices[3];
    coords[3].y = y + row2 * vertices[3];*/

    window.gl_setcolor(RED);
    window.gl_fillpoly(coords, 4);
}

bool Rectangle::contains(const Point &loc) const {
    Point diff = loc - getPos();
    return true;
}

bool Rectangle::collision(const Object &obj) const {
    return obj.testCollision(*this);
}

bool Rectangle::testCollision(const Rectangle &rect) const {
    return false;
}

bool Rectangle::testCollision(const Circle &circ) const {
    return false;
}

