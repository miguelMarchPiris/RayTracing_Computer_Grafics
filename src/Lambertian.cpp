#include <iostream>
#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material()
{
    Kdiffuse = color;
}

Lambertian::Lambertian(vec3 ambient, vec3 diffuse, vec3 specular, float alpha, float shininess) : Material()
{
    this->Kambient = ambient;
    this->Kdiffuse = diffuse;
    this->Kspecular = specular;
    this->alpha = alpha;
    this->shininess = shininess;
}

Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>& r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out.push_back(Ray(rec.p + 0.001f*(target-rec.p), target-rec.p));
    colors.push_back(Kdiffuse);
    return true;
}
