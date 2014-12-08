#ifndef PHYSICS_H
#define PHYSICS_H

#include <thread>
#include <vector>
#include <time.h>
using namespace std;

#define PI 3.14159265359
#define SEC_PER_CLOCK 1 / CLOCKS_PER_SEC

class Object;

class Physics {
    private:
        double lastDraw, lastUpdate;
        vector<Object *> objects;

    public:
        Physics();
        ~Physics();
        
        void run();
        void draw();
};

#endif /* PHYSICS_H */
