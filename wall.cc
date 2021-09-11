#pragma once
#include "vec2d.cc"
using namespace std;

class wall : public particle1d{
    public:

    wall(float pos; float vel){
        particle1d(pos, vel, 0, 0);
    }
};
