#include "MaterialTextura.h"

MaterialTextura::MaterialTextura():Material(){
    this->diffuse = vec3(0.5,0.5,0.5);
    this->especular = vec3(0.0,0.0,0.0);
    this->ambient = vec3(0.1,0.1,0.1);
    this->alpha = 1.0;
    this->shininess = 1.0;
}

MaterialTextura::~MaterialTextura()
{}

bool MaterialTextura::scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>& r_out) const {
    /*
    float r = this->getDiffuse(vec2(rec.p.x,rec.p.z)).x;
    float g = this->getDiffuse(vec2(rec.p.x,rec.p.z)).y;
    float b = this->getDiffuse(vec2(rec.p.x,rec.p.z)).z;*/
    return false;
}

//Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta){}
MaterialTextura::MaterialTextura(vec3 a, vec3 d, vec3 s, float o, int sh):Material(a,d,s,o,sh){
    this->diffuse = d;
    this->especular = s;
    this->ambient = a;
    if(o > 1.0 + EPSILON){ o = 1.0;}
    this->alpha = o;
    if(sh > 500+EPSILON){sh = 500;}
    this->shininess = sh;
}

vec3 MaterialTextura::getDiffuse(vec2 point) const{
    return this->image->getColorPixel(point);
}