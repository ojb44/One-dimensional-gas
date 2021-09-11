using namespace std;

class particle1d{
    public:
        float x;
        float v;
        float im; //inverse mass
        float rad; //radius

    particle1d(){
        x=0;v=0;im=0;rad=0;
    }

    particle1d(float xi, float vi, float inv_mass, float radius){
        x=xi;v=vi;im=inv_mass;rad=radius;
    }

    void collide(particle1d &p2);
    float timeToCollide(particle1d p2);
    void posStep(float dt);
    float energy();
    
};

void particle1d::collide(particle1d &p2){
    float v1f, v2f;
    if (im==0){
        p2.v=-p2.v+2*v;
    }
    else if (p2.im==0){
        v=-v+2*p2.im;
    }
    else{
    v1f = (v*(p2.im-im)+2*p2.v*im)/(im+p2.im);
    v2f = (p2.v*(im-p2.im)+2*v*p2.im)/(im+p2.im);
    v=v1f;
    p2.v=v2f;
    }
}

float particle1d::timeToCollide(particle1d p2){
    float time;
    float relVel=v-p2.v;
    if(relVel*(p2.x-x-p2.rad-rad)<=0){
        return -1;
    }

    else{
    time=(p2.x-x-p2.rad-rad-0.0001)/relVel;  //note if comes out negative, will not collide
    return time;
    }
}

void particle1d::posStep(float dt){
    x+=v*dt;
}

float particle1d::energy(){
    float E = 0.5*v*v/im;
    return E;
}