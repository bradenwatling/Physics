#ifndef OBJECT_H
#define OBJECT_H

#include "easygl.h"
#include "Point.h"

class Rectangle;
class Circle;

class Object {
    private:
        Point pos; // Position of the center of mass
        Point vel; // Velocity -> pixels/sec
        double angle; // Angle
        double ang_vel; // Angular velocity -> rad/sec
        double mass; // Mass
        double lastTranslateTime, lastRotateTime;
        
    protected:
        Point acc; // Acceleration
        double ang_acc; // Angular acceleration. Counter-clockwise positive
        double RoG; // Radius of gyration
        
        bool fixed_trans, fixed_rotate;
        
        Point rotate(const Point &p) const;
        static void addToVertices(t_point *vertices, int index, const Point &p);
        
    public:
        Object(const Point &_pos, double _mass);
        virtual ~Object();
        
        Point getPos() const;
        double getAngle() const;
        double getMass() const;
        
        void update(double curTime);
        void applyForce(const Point &loc, const Point &f);

        virtual void draw() const = 0;
        virtual bool contains(const Point &loc) const = 0;
        
        virtual bool collision(const Object &obj) const = 0;
        virtual bool testCollision(const Rectangle &rect) const = 0;
        virtual bool testCollision(const Circle &circ) const = 0;
};

#endif /* OBJECT_H */
