#include "Rectangle.h"
#include "Polygon.h"

Polygon::Polygon(const Point &_pos, const Point _vertices[], int _numVertices, double mass, bool fixed)
                        : Object(_pos, mass) {
    numVertices = _numVertices;
    
    vertices = new Point *[numVertices];
    for (int i = 0; i < numVertices; i++) {
        vertices[i] = new Point(_vertices[i]);
    }
    
    double a = area();
    RoG = a * a;
    
    fixed_trans = fixed;
    fixed_rotate = fixed;
}

Polygon::~Polygon() {
    delete vertices;
}

double Polygon::area() const {
    float area = 0;
    int nextIndex;
    Point p1, p2;

    for (int i = 0; i < numVertices; i++) {
        nextIndex = (i + 1) % numVertices;
        
        p1 = *vertices[i];
        p2 = *vertices[nextIndex];
        
        area += p1.getX() * p2.getY() - p2.getX() * p1.getY();
    }
    
    return 0.5 * abs(area);
}

void Polygon::draw() const {
    t_point *coords = new t_point[numVertices];

    Point pos = getPos();
    double angle = getAngle();
    
    for (int i = 0; i < numVertices; i++) {
        addToVertices(coords, i, pos + rotate(*vertices[i], angle));
    }

    window.gl_setcolor(BLUE);
    window.gl_fillpoly(coords, numVertices);
    
    delete []coords;
}

bool Polygon::contains(const Point &loc) const {
    Point pos = getPos();
    Point transformed = pos + rotate(loc - pos, -getAngle());
    
    Point vecOfSide;
    float distanceAlongVector, yDistance;
    int nextIndex;
    int sidesToLeft = 0;

    for (int i = 0; i < numVertices; i++) {
        nextIndex = (i + 1) % numVertices; // Next vertex after istart
        
        vecOfSide = *vertices[nextIndex] - *vertices[i];
        yDistance = (transformed.getY() - vertices[i]->getY());
        if (vecOfSide.getY() != 0) {
            distanceAlongVector = yDistance / vecOfSide.getY();
        }
        else if (yDistance == 0) {
            distanceAlongVector = 0;
        }
        else {
            distanceAlongVector = 1e10; // Really infinity, but this is big enough
        }

        // We intersect this side if the distance (scaling) along the side vector to 
        // get to our "click" y point is between 0 and 1.  Count the first 
        // endpoint of the side as being part of the line (distanceAlongVector = 0)
        // but don't count the second endPoint; we'll intersect that point later 
        // when we check the next side.
        if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
            float xIntersection = vertices[i]->getX() + vecOfSide.getX() * distanceAlongVector;
            if (xIntersection <= transformed.getX())
                sidesToLeft++;
        }
    }

    return ((sidesToLeft % 2) == 1);
}

bool Polygon::collision(const Object &obj) const {
    return obj.testCollision(*this);
}

bool Polygon::testCollision(const Rectangle &rect) const {
    Point pos = getPos();
    double angle = getAngle();
    
    for (int i = 0; i < numVertices; i++) {
        if (rect.contains(pos + rotate(*vertices[i], angle))) {
            return true;
        }
    }
    
    return false;
}

bool Polygon::testCollision(const Circle &circ) const {
    return false;
}

bool Polygon::testCollision(const Polygon &poly) const {
    return false;
}

