#include "Polygon.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Point &_pos, int _width, int _height, double mass, bool fixed)
                        : Object(_pos, mass) {
    width = _width;
    height = _height;
    RoG = width * width * height * height;
    vertices[0] = Point(-width / 2, -height / 2);
    vertices[1] = Point(-width / 2, height / 2);
    vertices[2] = Point(width / 2, height / 2);
    vertices[3] = Point(width / 2, -height / 2);
    fixed_trans = fixed;
    fixed_rotate = fixed;
}

void Rectangle::draw() const {
    t_point coords[4];

    Point pos = getPos();
    double angle = getAngle();
    
    addToVertices(coords, 0, pos + rotate(vertices[0], angle));
    addToVertices(coords, 1, pos + rotate(vertices[1], angle));
    addToVertices(coords, 2, pos + rotate(vertices[2], angle));
    addToVertices(coords, 3, pos + rotate(vertices[3], angle));

    window.gl_setcolor(RED);
    window.gl_fillpoly(coords, 4);
}

bool Rectangle::contains(const Point &loc) const {
    Point pos = getPos();
    
    Point transformed = pos + rotate(loc - pos, -getAngle());
    
    return transformed.getX() > pos.getX() - width / 2 && transformed.getX() < pos.getX() + width / 2
            && transformed.getY() > pos.getY() - height / 2 && transformed.getY() < pos.getY() + height / 2;
}

bool Rectangle::collision(const Object &obj) const {
    return obj.testCollision(*this);
}

bool Rectangle::testCollision(const Rectangle &rect) const {
    Point pos = getPos();
    double angle = getAngle();
    
    return rect.contains(pos + rotate(vertices[0], angle)) || rect.contains(pos + rotate(vertices[1], angle))
            || rect.contains(pos + rotate(vertices[2], angle)) || rect.contains(pos + rotate(vertices[3], angle));
}

bool Rectangle::testCollision(const Circle &circ) const {
    return false;
}

bool Rectangle::testCollision(const Polygon &poly) const {
    Point pos = getPos();
    double angle = getAngle();
    
    return poly.contains(pos + rotate(vertices[0], angle)) || poly.contains(pos + rotate(vertices[1], angle))
            || poly.contains(pos + rotate(vertices[2], angle)) || poly.contains(pos + rotate(vertices[3], angle));
}

