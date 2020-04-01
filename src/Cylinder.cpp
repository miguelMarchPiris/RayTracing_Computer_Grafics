//
// Created by desgarrador on 9/3/20.
//

#include <include/Translate.h>
#include <iostream>
#include <algorithm>
#include "Cylinder.h"
Cylinder::Cylinder(vec3 center, float radius,float h,float data): Object(data){
    this->center=center;
    this->radius=radius;
    this->height=h;
}


bool Cylinder::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const {
    float a = pow(raig.dirVector().x, 2.0f) + pow(raig.dirVector().z, 2.0f);
    float b = (dot(raig.initialPoint().x, raig.dirVector().x) + dot(raig.initialPoint().z, raig.dirVector().z));
    float c = pow(raig.initialPoint().x, 2.0f) + pow(raig.initialPoint().z, 2.0f) - pow(radius, 2);

    float discriminant = b * b - a * c;
    float t0 = 9999, t1 = 9999, t2 = 9999, t3 = 9999;

    if (discriminant > 0) {
        t0 = (-b - sqrt(discriminant)) / a;
        if (t0 < t_max && t0 > t_min) {
            if (raig.pointAtParameter(t0).y >= center.y - height / 2 &&
                raig.pointAtParameter(t0).y <= center.y + height / 2) {
                info.t = t0;
                info.p = raig.pointAtParameter(info.t);
                info.normal = (info.p - vec3(center.x, info.p.y, center.z)) / radius;
                info.mat_ptr = material;
                return true;
            }
        }

        t1 = (-b + sqrt(discriminant)) / a;
        if (t1 < t_max && t1 > t_min) {
            if (raig.pointAtParameter(t1).y >= center.y - height / 2 &&
                raig.pointAtParameter(t1).y <= center.y + height / 2) {
                info.t = t1;
                info.p = raig.pointAtParameter(info.t);
                info.normal = (info.p - vec3(center.x, info.p.y, center.z)) / radius;
                info.mat_ptr = material;
                return true;
            }
        }

        return false;
    }
}
void Cylinder::aplicaTG(TG *t) {
    ///*
        if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
     //*/

}