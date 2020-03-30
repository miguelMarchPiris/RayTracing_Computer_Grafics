//
// Created by desgarrador on 9/3/20.
//

#ifndef RAYDATA_CYLINDER_H
#define RAYDATA_CYLINDER_H


#include "Object.h"
#include "Animation.h"
#include "Translate.h"

class Cylinder : public Object {
public:
    Cylinder(vec3 c, float r, float h,float data);
    virtual ~Cylinder(){}
    virtual bool intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const;

    virtual void aplicaTG(TG *t);
private:
    vec3 center;
    float radius;
    float height;
};


#endif //RAYDATA_CYLINDER_H
