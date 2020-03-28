//
// Created by desgarrador on 9/3/20.
//

#include "Cylinder.h"
Cylinder::Cylinder(vec3 center, float radius,float h,float data): Object(data){
    this->center=center;
    this->radius=radius;
    this->height=h;
}


bool Cylinder::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const{
    bool intersecciona=false;
    float a,b,c;
    float rx,rz,ry;
    rx=raig.dirVector().x;
    //ry=raig.dirVector().y;
    rz=raig.dirVector().z;

    a = rx*rx + rz*rz;
    b = 2*(raig.initialPoint().x + raig.initialPoint().z);
    c = pow(raig.initialPoint().x, 2) + pow(raig.initialPoint().z, 2);
    float discriminante=4*a*c - b*b;
    if(discriminante>=0){
        float t1,t2;
        t1=(-b+sqrtf(discriminante))/(2*a);
        t2=(-b-sqrtf(discriminante))/(2*a);
        if(t1<t_min || t1>t_max){
            t1=HUGE_VALF;
        }
        if(t2<t_min && t2>t_max){
            t2=HUGE_VALF;
        }
        //Si están dentro de los límites empezamos a meter la información.
        if((t1<t_max || t2<t_max)){
            t1=fmin(t1,t2);

            info.t = t1;
            info.p = raig.pointAtParameter(info.t);
            /*
             * Calculamos la normal como si el punto de intersección estuviera a la altura de la misma
             * base del cilindro.
             */
            //info.normal = (info.p - (center+vec3(0,info.p.y,0))) / radius;
            info.normal = (vec3(info.p.x,center.y,info.p.z)-center)/radius;
            info.mat_ptr = material;
        }
    }
    return intersecciona;
}