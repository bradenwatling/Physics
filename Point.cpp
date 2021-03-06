#include "Point.h"

void Point::calcMag() {
    mag = sqrt(x * x + y * y);
}

Point::Point() {
    x = 0.0f;
    y = 0.0f;
}

Point::Point(float _x, float _y) {
    x = _x;
    y = _y;
    calcMag();
}

void Point::setX(float _x) {
    x = _x;
    calcMag();
}

void Point::setY(float _y) {
    y = _y;
    calcMag();
}

void Point::setXY(float _x, float _y) {
    x = _x;
    y = _y;
    
    calcMag();
}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

float Point::getMag() const {
    return mag;
}

Point &Point::operator+=(const Point &rhs) {
    x += rhs.x;
    y += rhs.y;
    
    calcMag();
    
    return *this;
}

Point &Point::operator-=(const Point &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    
    calcMag();
    
    return *this;
}

Point &Point::operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    
    calcMag();
    
    return *this;
}

Point &Point::operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    
    calcMag();
    
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
