//
// Created by franc on 01/04/2020.
//

#ifndef RAYDATA_METAL_H
#define RAYDATA_METAL_H

#include "Material.h"

class Metal: public Material{
public:
    Metal(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess);
    virtual ~Metal();
    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>& r_out) const;
};

#endif //RAYDATA_METAL_H
