#ifndef OBJECT_H
#define OBJECT_H

#include "Point.h"

class Object {
    private:
        Point pos; // Position of the center of mass
        Point vel; // Velocity
        double angle; // Angle
        double ang_vel; // Angular velocity
        double mass; // Mass
        
    protected:
        Point acc; // Acceleration
        double ang_acc; // Angular acceleration. Counter-clockwise positive
        double RoG; // Radius of gyration
        
        bool fixed_trans, fixed_rotate;
        
    public:
        Object(const Point &_pos, double _mass);
        virtual ~Object();
        
        Point getPos() const;
        double getAngle() const;
        double getMass() const;
        
        void update();
        void applyForce(const Point &loc, const Point &f);

        virtual void draw() = 0;
        virtual bool contains(const Point &loc) = 0;
        virtual bool collision(const Object &obj) = 0;
};

#endif /* OBJECT_H */
