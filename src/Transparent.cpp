//
// Created by franc on 02/04/2020.
//

#include <iostream>
#include "Transparent.h"

Transparent::Transparent(vec3 kt, float refractionIndex) : Material()
{
    /*
    Kd = vec3(1.0), Ks = vec3(1.0),
Kt = vec3(0.7), index = 1.5
     */
    //
    this->specular=vec3(1,1,1)*0.01f;//.9351f;
    this->kt= vec3(1,1,1)-specular;
    //this->kt= vec3(1,1,1)*0.9f;
    this->diffuse=vec3(0,0,0);
    this->ambient=vec3(0,0,0);
    //this->kt = kt;
    this->refractionIndex = refractionIndex;
    this->refractionIndex=1.297;
    this->shininess=400;
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

    //nit=1/refractionIndex;

    //Si angleIn es menor que 90 significa que pasamos del "vacío" al material en cuestión
    // como anglein es el coseno del angulo, tenemos anglein>0 <-> angulo<90
    nit = 1/refractionIndex;
    if(in_cos>0){
        //nit = 1/refractionIndex;
    }
    //Sino significa que pasamos del material al "vació" -> refractionIndex/1
    else{
        normal=normal*-1.f;
        //nit = refractionIndex;
    }
    dentro_raiz = 1 - nit * nit * (1 - in_cos * in_cos);
    // Si es menor que 0, solo tenemos en cuenta la reflexión total interna.
    bool refraccion_total=true;
    if(dentro_raiz > 0){
        float ec1 = (nit * in_cos - sqrt(dentro_raiz));
        float ec2 = nit;
        //vec3 transmissionVector = (in_inv * nit) + normal*(nit * in_cos - sqrt(dentro_raiz));
        vec3 transmissionVector = (in * ec2) + normal * ec1;
        //vec3 transmissionVector = r_in.dirVector();
        Ray transmissionRay = Ray(rec.p + 0.001f*transmissionVector, transmissionVector);
        r_out.push_back(transmissionRay);
        //colors.push_back(vec3(0,0,0));
        colors.push_back(this->kt);
        refraccion_total=false;
    }

    //else{

        vec3 reflectedVector = normal*2.f + rec.p - in_inv;
        Ray reflectedRay = Ray(rec.p + 0.001f*reflectedVector, reflectedVector);
        r_out.push_back(reflectedRay);

        //colors.push_back(vec3(0,0,0));
        if(refraccion_total){
            colors.push_back(vec3(1,1,1));
        }else{
            colors.push_back(this->specular);
        }


    //}
    // */


    return true;
}
