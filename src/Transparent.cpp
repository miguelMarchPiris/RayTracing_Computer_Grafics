//
// Created by franc on 02/04/2020.
//

#include <iostream>
#include "Transparent.h"

Transparent::Transparent(vec3 kt, float refractionIndex) : Material()
{
    this->Kt=kt;
    this->Kspecular= vec3(1, 1, 1) - this->Kt;
    this->Kdiffuse=vec3(0, 0, 0);
    this->Kambient=vec3(0, 0, 0);

    this->refractionIndex = refractionIndex;
    this->shininess=500;
}

Transparent::~Transparent(){
}

bool Transparent::scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>& r_out) const  {

    float nit;          // nit ->coeficiente de refraccion
    float dentro_raiz;  // lo que hay dentro de la raiz cuadrada
    float in_cos;       //coseno del angulo que forman la normal y el rayo incidente.
    vec3 normal = normalize(rec.normal);
    //El vector in_inv tiene que considerarse como que sale del punto de intersección, no que entra.
    //INVERTIMOS el vector director.
    vec3 in_inv = normalize(r_in.dirVector())*-1.f;
    vec3 in     = normalize(r_in.dirVector());
    in_cos = dot(in_inv, normal);
    nit = 1/refractionIndex;

    //Si angleIn es mayor que 90 significa que pasamos del material al "vació"
    //por lo tanto invertimos la normal.
    if(in_cos<0){
        normal=normal*-1.f;
    }

    dentro_raiz = 1 - nit * nit * (1 - in_cos * in_cos);
    // Si dentro_raiz es menor que 0, solo tenemos en cuenta la reflexión total interna.
    bool refraccion_total=true;
    if(dentro_raiz > 0){
        vec3 transmissionVector = (in * nit) + normal*(nit * in_cos - sqrt(dentro_raiz));
        Ray transmissionRay = Ray(rec.p + 0.001f*transmissionVector, transmissionVector);
        r_out.push_back(transmissionRay);
        colors.push_back(this->Kt);

        refraccion_total=false;
    }
    vec3 reflectedVector = normal*2.f + rec.p - in_inv;
    Ray reflectedRay = Ray(rec.p + 0.001f*reflectedVector, reflectedVector);
    r_out.push_back(reflectedRay);
    if(refraccion_total){
        //En caso de refracción total el valor del color es máximo
        colors.push_back(vec3(1,1,1));
    }else{
        colors.push_back(this->Kspecular);
    }
    return true;
}
