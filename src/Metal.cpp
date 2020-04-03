//
// Created by franc on 01/04/2020.
//

#include <include/Metal.h>

Metal::Metal(vec3 ambient, vec3 diffuse, vec3 specular, float alpha, float shininess) {
    this->Kambient = ambient;
    this->Kdiffuse = diffuse;
    this->Kspecular = specular;
    this->alpha = alpha;
    this->shininess = shininess;
}

Metal::~Metal(){
}

bool Metal::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3>& colors, std::vector<Ray> &r_out) const {
    vec3 resultant = reflect(r_in.dirVector(), rec.normal);
    Ray reflection = Ray(rec.p + 0.001f*resultant, resultant);
    r_out.push_back(reflection);
    colors.push_back(Kspecular);
    return true;
}