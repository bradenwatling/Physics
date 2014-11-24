#include <iostream>

#include "easygl.h"
#include "Physics.h"
#include "Object.h"
#include "Rectangle.h"

using namespace std;

extern easygl window;
Physics phys;

void easygl::drawscreen() {
    phys.draw();
}

int main() {
    window.set_world_coordinates(-10, -10, 10, 10);
    window.gl_event_loop();
    return 0;
}
