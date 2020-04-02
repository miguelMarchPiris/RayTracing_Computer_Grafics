//
// Created by franc on 02/04/2020.
//

#include <iostream>
#include "Transparent.h"

Transparent::Transparent(vec3 kt, float refractionIndex) : Material()
{
    this->kt = kt;
    this->refractionIndex = refractionIndex;
}

Transparent::~Transparent(){
}

bool Transparent::scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    float angleIn, nit, k;
    vec3 in = normalize(r_in.dirVector());
    angleIn = dot(in, rec.normal);
    nit = 1/refractionIndex;
    k = 1 - nit*nit * (1 - cos(angleIn)*cos(angleIn));
    vec3 transmissionVector = nit * in + rec.normal * (nit * cos(angleIn) - sqrt(k));
    Ray transmissionRay = Ray(rec.p + 0.001f*transmissionVector, transmissionVector);
    r_out.push_back(transmissionRay);
    color = this->kt;
    return true;
}
