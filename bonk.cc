#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "particle1d.cc"

using namespace std;



float nextCollision(particle1d particles[], int n, int nextCollisions[]);
void update(particle1d particles[], float timeStep, int n, int nextCollisions[], int collisionStep);
void printStates(particle1d particles[], int n);
float totEnergy(particle1d particles[], int n);
void writeSpeeds(particle1d particles[], int n, string fileName);


int main(){

    srand (time(NULL));

    int n=13;   //num particles (including walls)

    particle1d particles[13];  //list of particles
    //walls:
    particles[0]=particle1d(0,0,0,0);   //left hand wall
    particles[n-1]=particle1d(n-1,-0,0,0);   //right hand wall
    for (int l=1; l<6; l++){
        particles[l]=particle1d(l,static_cast<float>(rand()%100-50)/50,static_cast<float>(rand()%1)/100+1,0.01);   //random velocity and random mass (around 1)
        cout<<l;
        cout<<"p"<<particles[l].x<<" ";
    }
    for (int l=7; l<12; l++){
        particles[l]=particle1d(l,static_cast<float>(rand()%100-50)/50,static_cast<float>(rand()%1)/100+4,0.01);   //random velocity and random mass (around 0.25)
        cout<<l;
        cout<<"p"<<particles[l].x<<" ";
    }

    //piston:
    particles[6]=particle1d(6,0,0.002,0.01);
    
    //to set end particles:
    /*particles[1]=particle1d(1,static_cast<float>(rand()%100-50)/50,1,0.01); //heavy
    particles[8]=particle1d(8,static_cast<float>(rand()%100-50)/50,4,0.01);  //light*/


    float time=0;
    float printTimeStep=0.05;   //time inbetween data recording
    float maxTime=1000;    //time for which simulation runs
    float timeStep;
    int nextCollisions[100]={0};

    ofstream fout;
    fout.open("bonks.dat", ofstream::trunc);      //will record positions of each particle with time (equally spaced)
    ofstream gout;
    gout.open("heavyParticle.dat", ofstream::trunc);      //will record velocity and position of the heavy particle with time (equally spaced)
    ofstream hout;
    hout.open("lightParticle.dat", ofstream::trunc);     //will record velocity and position of the light particle with time (equally spaced)

    printStates(particles, n);
  
    cout<<"Initial energy: "<<totEnergy(particles, n)<<endl;
    int print=1;
    float timeTilPrint=printTimeStep;
    float timeTilCollide;

    //simulation loop (the method for doing this with regular time steps was inspired by the example on the course website!)
    while (time<maxTime){         
        if (print==1){
            fout<<time<<"\t";
            for (int k=0; k<n; k++){
                fout<<particles[k].x<<"\t";
            }
            fout<<"\n";
            gout<<time<<"\t"<<particles[1].x<<"\t"<<particles[1].v<<"\n";
            hout<<time<<"\t"<<particles[8].x<<"\t"<<particles[8].v<<"\n";
            timeTilPrint=printTimeStep;
        }
        timeTilCollide=nextCollision(particles, n, nextCollisions);
        if (timeTilCollide<timeTilPrint){
            time+=timeTilCollide;
            timeTilPrint-=timeTilCollide;
            update(particles, timeTilCollide, n, nextCollisions, 1); //1 indicates collision does take place
            print=0;
        }
        else{
            update(particles, timeTilPrint, n, nextCollisions, 0);  //0 indicates collision does take place

            time+=timeTilPrint;
            print=1;
        }

    }

    
    /*for (int j=0; j<10000; j++){
        if (j==0){writeSpeeds(particles, n, "velocities1.dat");}
        if (j==10){writeSpeeds(particles, n, "velocities10.dat");}
        if (j==100){writeSpeeds(particles, n, "velocities100.dat");}
        if (j==1000){writeSpeeds(particles, n, "velocities1000.dat");}
        if (j==9999){writeSpeeds(particles, n, "velocities9999.dat");}
        fout<<time<<"\t";
        gout<<time<<"\t"<<totEnergy(particles, n)<<"\n";
        for (int k=0; k<n; k++){
            fout<<particles[k].x<<"\t";
        }
        fout<<"\n";
        timeStep=nextCollision(particles, n, nextCollisions);
        time+=timeStep;
        update(particles, timeStep, n, nextCollisions);
    }*/

    printStates(particles, n);
    cout<<"Final energy: "<<totEnergy(particles, n)<<endl;


}

//finds the next collisions, sets the array nextCollisions to 1 for the pairs of particles which collide, and returns the time til the collision
float nextCollision(particle1d particles[], int n, int nextCollisions[]){
    float time;
    float minTime=-1;//=particles[0].timeToCollide(particles[1]);
    for (int i=0; i<n-1; i++){                                   //looping through to find the minimum time
        time=particles[i].timeToCollide(particles[i+1]);
        if ((time<minTime && time>0)||(abs(minTime+1)<0.0001 && time>0)){
            minTime=time;
        }
    }

    for (int i=0; i<n-1; i++){                                   //looping through to record those with minimum time - need to do this for when multiple collisions occur simul.
        time=particles[i].timeToCollide(particles[i+1]);
        if ((abs(minTime-time)<0.0001 && time>0)){
            nextCollisions[i]=1;
        }
    }

    return minTime;
}

//updates the particles for the time step. Collides if it is a collision step.
void update(particle1d particles[], float timeStep, int n, int nextCollisions[], int collisionStep){  //collides if collision_step is 1, doesn't if 0
    for (int i=0; i<n; i++){
        particles[i].posStep(timeStep);

    }
    if (collisionStep==1){
        for (int j=0; j<n; j++){
            if (nextCollisions[j]==1){                     //nextCollisions keeps track of which to collide
                particles[j].collide(particles[j+1]);
                nextCollisions[j]=0;
            }
        }
    }
}

void printStates(particle1d particles[], int n){
    for (int i=0; i<n; i++){
        cout<<"("<<particles[i].x<<","<<particles[i].v<<"), ";
    }
    cout<<endl;
}

float totEnergy(particle1d particles[], int n){
    float tE=0;
    for (int i=1; i<n-1; i++){
        tE+=particles[i].energy();
    }
    return tE;
}

void writeSpeeds(particle1d particles[], int n, string fileName){     //write the velocities to a file
    ofstream vout1;
    vout1.open(fileName);
    for (int i=0; i<n; i++){
        vout1<<particles[i].v<<"\n";
    }
}
