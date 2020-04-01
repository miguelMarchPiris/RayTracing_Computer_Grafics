#include "Material.h"

Material::Material(){
    this->diffuse = vec3(0.5,0.5,0.5);
    this->especular = vec3();
    this->ambient = vec3();
    this->alpha = 1.0;
    this->shininess = 50.0;
}

/*
Material::Material():
    diffuse(1.0f)
  {}*/

Material::~Material()
{}


/*Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta){
    diffuse = d;
}*/

Material::Material(vec3 a, vec3 d, vec3 s, float o, int sh) {
    this->diffuse = d;
    this->especular = s;
    this->ambient = a;
    if(o > 1.0+EPSILON){o = 1.0;}
    this->alpha = o;
    if(sh > 500+EPSILON){sh = 500;}
    this->shininess = sh;
}

vec3 Material::multVec(float f, vec3 vec) const{
    return vec3(vec.x*f,vec.y*f,vec.z*f);
}

vec3 Material::getDiffuse(vec2 point) const {
    return this->diffuse;
}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}

