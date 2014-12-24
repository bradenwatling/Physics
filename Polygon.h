#ifndef POLYGON_H
#define POLYGON_H

#include <cmath>
#include "Object.h"

class Polygon : public Object {
    private:
        int numVertices;
        Point **vertices;

    public:
        Polygon(const Point &_pos, const Point _vertices[], int _numVertices, double mass, bool fixed);
        ~Polygon();
        
        double area() const;
        
        void draw() const;
        bool contains(const Point &loc) const;
        
        bool collision(const Object &obj) const;
        bool testCollision(const Rectangle &rect) const;
        bool testCollision(const Circle &circ) const;
        bool testCollision(const Polygon &poly) const;
};

#endif /* POLYGON_H */
