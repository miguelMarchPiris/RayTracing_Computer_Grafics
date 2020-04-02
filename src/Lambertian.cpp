#include <iostream>
#include "Lambertian.h"

Lambertian::Lambertian(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess) : Material()
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->beta = beta;
    this->shininess = shininess;
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out.push_back(Ray(rec.p + 0.001f*(target-rec.p), target-rec.p));
    color = diffuse;
    return true;
}
