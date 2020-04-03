#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material
{

public:
    Lambertian(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess);
    virtual ~Lambertian();
    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>& r_out) const;
};

#endif // LAMBERTIAN_H
