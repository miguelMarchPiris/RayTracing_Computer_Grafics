#include <include/Scale.h>
#include <iostream>
#include "Sphere.h"

Sphere::Sphere(vec3 cen, float r, float d) :Object(d) {
    center = cen;
    radius = r;
}
Sphere::Sphere( float d) :Object(d) {
    center = vec3(0,0,0);
    radius = 1;
}


bool Sphere::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const {
    vec3 oc = raig.initialPoint() - center;
    float a = dot(raig.dirVector(), raig.dirVector());
    float b = dot(oc, raig.dirVector());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            info.t = temp;
            info.p = raig.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material;
            return true;
        }
    }
    return false;
}

void Sphere::aplicaTG(TG *t) {
    if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
    else if (dynamic_cast<Scale *>(t))
    {
        vec4 c(1.0,1.0,1.0,1.0);
        c = t->getTG() * c;
        this->radius = c.x*radius;
        std::cout << this->radius << std::endl;
    }
}

