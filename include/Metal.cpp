//
// Created by Marcos Plaza Gonzalez on 2/4/20.
//

#include "Metal.h"

Metal::Metal(vec3 ambient, vec3 diffuse, vec3 specular, float beta, float shininess) {
    this->Kambient = ambient;
    this->Kdiffuse = diffuse;
    this->Kspecular = specular;
    this->alpha = beta;
    this->shininess = shininess;
}

Metal::~Metal() {

}

bool Metal::scatter(const Ray &r_in, const IntersectionInfo &rec, vec3 &color, std::vector<Ray> &r_out) const {
    vec3 resultant = reflect(r_in.dirVector(), rec.normal);
    Ray reflection = Ray(rec.p + 0.001f*resultant, resultant);
    r_out.push_back(reflection);
    color = Kspecular;
    return true;
}
