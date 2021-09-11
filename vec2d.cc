#pragma once
using namespace std;

// class to deal with the vectors for position, velocity, etc.
class vec2d{ 
    public:
        float x;
        float y;

    vec2d(){
        x=0.0; y=0.0;
    }

    vec2d(float a, float b){
        x=a; y=b;
    }

    friend ostream &operator<<(ostream &os, vec2d const &v) { 
        return os << v.x << " " << v.y;
    }

    vec2d operator+ (const vec2d &v) const {
        return vec2d(x+v.x, y+v.y);
    }

    vec2d operator* (const float &a) const {
        return vec2d(x*a, y*a);
    }

    float mag();
};