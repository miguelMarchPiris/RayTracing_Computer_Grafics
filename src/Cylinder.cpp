//
// Created by desgarrador on 9/3/20.
//

#include "Cylinder.h"
Cylinder::Cylinder(vec3 center, float radius, float h, float data): Object(data){
    this->center=center;
    this->radius=radius;
    this->height=h;
}

bool Cylinder::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const{
    bool intersecciona=false;
    float a, b, c;

    a = pow(raig.dirVector().x, 2) + pow(raig.dirVector().z, 2);
    b = 2*(raig.dirVector().x*raig.initialPoint().x + raig.dirVector().z*raig.initialPoint().z);
    c = pow(raig.initialPoint().x, 2) + pow(raig.initialPoint().z, 2) - 1;

    if(2*a == 0)
        return false;

    float t1, t2;

    t1 = -b + sqrt(pow(b, 2) - 4*a*c);
    t2 = -b - sqrt(pow(b, 2) - 4*a*c);

    if(t1 < t2){
        intersecciona = true;
        info.t = t1;
        info.p = raig.pointAtParameter(info.t);
        info.mat_ptr = material;
        info.normal =
    }else if(t2 < t1){
        intersecciona = true;
        info.t = t1;
        info.p = raig.pointAtParameter(info.t);

    }
    return intersecciona;
}

void Cylinder::aplicaTG(TG *tg) {

}