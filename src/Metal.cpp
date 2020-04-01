//
// Created by franc on 01/04/2020.
//

#include <include/Metal.h>
#include <iostream>

Metal::Metal(vec3 ambient, vec3 diffuse, vec3 specular, float k, float beta, float shininess) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->k = k;
    this->beta = beta;
    this->shininess = shininess;
}

Metal::~Metal(){
}

bool Metal::scatter(const Ray &r_in, const IntersectionInfo &rec, vec3 &color, std::vector<Ray> &r_out) const {
    Ray reflection = Ray(rec.p + 0.001f*reflect(r_in.dirVector(), rec.normal), reflect(r_in.dirVector(), rec.normal));
    r_out.push_back(reflection);
    color = specular;
    return true;
}