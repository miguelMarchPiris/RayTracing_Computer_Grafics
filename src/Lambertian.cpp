#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color): Material()
{
    Kdiffuse = color;
}

Lambertian::Lambertian(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess): Material()
{
    this->Kambient = ambient;
    this->Kdiffuse = diffuse;
    this->Kspecular = specular;
    this->alpha = beta;
    this->shininess = shininess;
}


Lambertian::~Lambertian()
{
}

bool Lambertian::scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    r_out.push_back(Ray(rec.p, target-rec.p));
    color = Kdiffuse;
    return true;
}
