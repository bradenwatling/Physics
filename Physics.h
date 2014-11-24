#ifndef PHYSICS_H
#define PHYSICS_H

#include <thread>
#include <vector>
using namespace std;

class Object;

class Physics {
    private:
        int x, y;
        thread t;
        vector<Object *> objects;

    public:
        Physics();
        ~Physics();
        
        void run();
        void draw();
};

#endif /* PHYSICS_H */
