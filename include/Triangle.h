//
// Created by marcos on 8/3/20.
//

#ifndef RAYDATA_TRIANGLE_H
#define RAYDATA_TRIANGLE_H


#include "Plane.h"
#include <iostream>

using namespace std;

class Triangle : public Plane {
public:
    //Constructors i destructor
    Triangle(vec3 v1, vec3 v2, vec3 v3, float data);
    Triangle(vec3 cord, float r, float d);
    virtual ~Triangle();

    //intersection i aplicaTG
    virtual bool intersection(const Ray& r, float t_min, float t_max, IntersectionInfo& info) const;
    //falta
    //virtual void aplicaTG(TG *t);

private:
    float const EPSILON = 0.001;
    vector<vec3> vertex;
    vec3 v1, v2, v3;
    vec3 normal;
};


#endif //RAYDATA_TRIANGLE_H
