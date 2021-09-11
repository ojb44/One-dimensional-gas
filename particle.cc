#pragma once
#include "vec2d.cc"
using namespace std;

class particle{

    public:
    vec2d pos;
    vec2d vel;
    float im; //inverse mass
    float rad;

    particle(){
        pos=vec2d(0,0); vel=vec2d(0,0);im=0;rad=0;
    }

    particle(vec2d initialPosition, vec2d initialVelocity, float mass, float radius) {
		pos = initialPosition;
		vel = initialVelocity;
		im = 1/mass;
        rad=radius;
	}

    

};