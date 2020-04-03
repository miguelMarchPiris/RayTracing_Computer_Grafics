//
// Created by franc on 02/04/2020.
//

#ifndef RAYDATA_TRANSPARENT_H
#define RAYDATA_TRANSPARENT_H

#include "Material.h"

class Transparent: public Material{
public:
    Transparent(vec3 kt, float refractionIndex);
    virtual ~Transparent();
    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>& r_out) const;

    float refractionIndex;
};
#endif //RAYDATA_TRANSPARENT_H
