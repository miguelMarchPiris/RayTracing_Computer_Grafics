//
// Created by franc on 01/04/2020.
//

#include <include/Metal.h>

Metal::Metal(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->beta = beta;
    this->shininess = shininess;
}

Metal::~Metal(){
}

bool Metal::scatter(const Ray &r_in, const IntersectionInfo &rec, vec3 &color, std::vector<Ray> &r_out) const {
    vec3 resultant = reflect(r_in.dirVector(), rec.normal);
    Ray reflection = Ray(rec.p + 0.001f*resultant, resultant);
    r_out.push_back(reflection);
    color = specular;
    return true;
}