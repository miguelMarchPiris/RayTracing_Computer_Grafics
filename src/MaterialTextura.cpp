#include "MaterialTextura.h"

#include <utility>

MaterialTextura::MaterialTextura():Material(){
    this->Kdiffuse = vec3(0.5, 0.5, 0.5);
    this->Kspecular = vec3(0.0, 0.0, 0.0);
    this->Kambient = vec3(0.1, 0.1, 0.1);
    this->alpha = 1.0;
    this->shininess = 1.0;
    this->image = new Texture("://resources/map.png");
}

MaterialTextura::~MaterialTextura()
= default;

bool MaterialTextura::scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>&r_out) const
{
    /*
    float r = this->getDiffuse(vec2(rec.p.x,rec.p.z)).x;
    float g = this->getDiffuse(vec2(rec.p.x,rec.p.z)).y;
    float b = this->getDiffuse(vec2(rec.p.x,rec.p.z)).z;*/
    return false;
}

MaterialTextura::MaterialTextura(QString im)
{
    this->Kdiffuse = vec3(1.0, 1.0, 1.0);
    this->Kspecular = vec3(0.0, 0.0, 0.0);
    this->Kambient = vec3(0.0, 0.0, 0.0);
    this->alpha = 1.0;
    this->shininess = 1.0;
    this->image = new Texture(im);
}

MaterialTextura::MaterialTextura(vec3 a, vec3 d, vec3 s, float o, int sh):Material(a,d,s,o,sh){
    this->Kdiffuse = d;
    this->Kspecular = s;
    this->Kambient = a;
    if(o > 1.0 + EPSILON){ o = 1.0;}
    this->alpha = o;
    if(sh > 500+EPSILON){sh = 500;}
    this->shininess = sh;
}

vec3 MaterialTextura::getDiffuse(vec2 point) const{
    return this->image->getColorPixel(point);
}
