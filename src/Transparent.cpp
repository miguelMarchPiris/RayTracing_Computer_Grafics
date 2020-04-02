//
// Created by franc on 02/04/2020.
//

#include <iostream>
#include "Transparent.h"

Transparent::Transparent(vec3 kt, float refractionIndex) : Material()
{
    this->kt = kt;
    this->refractionIndex = refractionIndex;
}

Transparent::~Transparent(){
}

bool Transparent::scatter(const Ray& r_in, const IntersectionInfo& rec, vec3& color, std::vector<Ray>& r_out) const  {
    float angleIn, nit, k;

    float in_cos;
    vec3 normal = normalize(rec.normal);
    //El vector in tiene que considerarse como que sale del punto de intersección, no que entra.
    //INVERTIMOS el vector director.
    //vec3 in = normalize(r_in.dirVector());
    vec3 in = normalize(r_in.dirVector())*-1.f;
    angleIn = dot(in, normalize(rec.normal));
    in_cos = dot(in, normal);
    //Si angleIn es menor que 90 significa que pasamos del "vacío" al material en cuestión
    // como anglein es el coseno del angulo, tenemos anglein>0 <-> angulo<90
    if(angleIn>0){
        nit = 1/refractionIndex;
    }
    //Sino significa que pasamos del material al "vació" -> refractionIndex/1
    else{
        nit = refractionIndex;
    }
    /*
    k = 1 - nit*nit * (1 - cos(angleIn)*cos(angleIn));
    vec3 transmissionVector = nit * in + rec.normal * (nit * cos(angleIn) - sqrt(k));

     */

    vec3 transmissionVector;
    k = 1 - nit*nit * (1 - in_cos*in_cos);
    // Si es menor que 0, solo tenemos en cuenta la reflexión total interna.
    //if( k < 0){
        transmissionVector = normal*2.f + rec.p - in;
    //}
    //else{
    //    transmissionVector = (nit * in) + normal*(nit * in_cos - sqrt(k));
    //}
    Ray transmissionRay = Ray(rec.p + 0.001f*transmissionVector, transmissionVector);
    //metemos el rayo transmitido
    r_out.push_back(transmissionRay);
    color = this->kt;
    return true;
}
