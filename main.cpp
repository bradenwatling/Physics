#include <iostream>

#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"

using namespace std;

void easygl::drawscreen() {
}

int main() {
    Physics phys;
    int x = 0;
    while (true) {
        phys.run();
    }
    return 0;
}
