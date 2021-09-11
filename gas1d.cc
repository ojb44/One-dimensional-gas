#pragma once
#include "vec2d.cc"
#include "particle1d.cc"
using namespace std;

class gas1d{
    public:
        int n;
        particle1d particles[5];
        int next;

    gas1d(int num, particle1d particleList[5]){
        n=num;
        particles=particleList;
        next=0;
    }

    
    float nextCollision();
    void update();
    void printStates();

};

float gas1d::nextCollision(){
    float time;
    float minTime=-1;//=particles[0].timeToCollide(particles[1]);
    for (int i=0; i<n-1; i++){
        time=particles[i].timeToCollide(particles[i+1]);

        if ((time<minTime && time>0)||(minTime==-1 && time>0)){
            minTime=time;
            next=i;
        }
    }
    return minTime;
}

void gas1d::update(){
    for (int i=0; i<n; i++){
        particles[i].posStep(timeStep);
    }
    int a=next+1;
    particles[next].collide(particles[next+1]);
}

void gas1d::printStates(){
    for (int i=0; i<n; i++){
        cout<<"("<<particles[i].x<<","<<particles[i].v<<"), ";
    }
    cout<<endl;
}