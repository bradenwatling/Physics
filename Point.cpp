#include "Point.h"

Point::Point() {
    x = 0.0f;
    y = 0.0f;
}

Point::Point(float _x, float _y) {
    x = _x;
    y = _y;
}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

Point &Point::operator+=(const Point &rhs) {
    x += rhs.x;
    y += rhs.y;
    
    return *this;
}

Point &Point::operator-=(const Point &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    
    return *this;
}

Point &Point::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    
    return *this;
}

Point &Point::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    
    return *this;
}

Point Point::operator+(const Point &rhs) const {
    return Point(x + rhs.x, y + rhs.y);
}

Point Point::operator-(const Point &rhs) const {
    return Point(x - rhs.x, y - rhs.y);
}

Point Point::operator/(float rhs) const {
    return Point(x / rhs, y / rhs);
}

Point Point::operator*(float rhs) const {
    return Point(x * rhs, y * rhs);
}

float Point::operator*(const Point &rhs) const {    
    return x * rhs.x + y * rhs.y;
}

float Point::operator^(const Point &rhs) const {
    // The first two components of the cross product are 0
    return x * rhs.y - y * rhs.x;
}
