#ifndef POINT_H
#define POINT_H

class Point {
    private:
        float x, y;
    public:
        Point();
        Point(float _x, float _y);
        
        float getX() const;
        float getY() const;
        
        Point &operator+=(const Point &rhs); // Vector addition
        Point &operator-=(const Point &rhs); // Vector subtraction
        
        Point &operator/=(float rhs); // Division by scalar
        Point &operator*=(float rhs); // Multiplication by scalar
        
        Point operator+(const Point &rhs) const; // Vector addition
        Point operator-(const Point &rhs) const; // Vector subtraction
        
        Point operator/(float rhs) const; // Division by scalar
        Point operator*(float rhs) const; // Multiplication by scalar
        
        float operator*(const Point &rhs) const; // Dot product
        float operator^(const Point &rhs) const; // Magnitude of cross product
};

#endif /* POINT_H */
