//
// Created by desgarrador on 9/3/20.
//
#include <include/Translate.h>
#include <include/Scale.h>
#include <include/Rotate.h>
#include "Cylinder.h"

Cylinder::Cylinder(vec3 center, float radius,float h,float data): Object(data){
    this->center=center;
    this->radius=radius;
    this->height=h;
}


bool Cylinder::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const{
    float a,b,c;
    float rx,rz;
    float jx, jz;
    rx=raig.dirVector().x;
    rz=raig.dirVector().z;
    float t[4]={HUGE_VALF, HUGE_VALF, HUGE_VALF, HUGE_VALF};

    //Colision con la superficie curva.
    jx=raig.initialPoint().x - center.x;
    jz=raig.initialPoint().z - center.z;
    a = rx*rx + rz*rz;
    b = 2*(jx*raig.dirVector().x + jz*raig.dirVector().z);
    c = pow(jx, 2) + pow(jz, 2) - pow(radius,2);
    float discriminante=b*b-4*a*c;
    //Si existe solución real significa que intersecta con el cilindro infinito.
    if(discriminante>=0){
        float aux;
        //Sacamos las dos soluciones reales y comprobamos que estén dentro de las alturas del cilindo
        t[0]= (-b + sqrtf(discriminante)) / (2 * a);
        aux=raig.pointAtParameter(t[0]).y;
        if( t[0]<t_min || t[0]> t_max || (center.y + height) < aux || aux  < center.y ){
            t[0]=HUGE_VALF;
        }
        t[1]= (-b - sqrtf(discriminante)) / (2 * a);
        aux=raig.pointAtParameter(t[1]).y;
        if( t[1]<t_min || t[1]> t_max || (center.y + height) < aux || aux < center.y){
            t[1]=HUGE_VALF;
        }
        //Solo en caso de que no interseccione dos veces con la superficie curva miramos las tapas
        if(t[0] == HUGE_VALF || t[1] == HUGE_VALF) {
            t[2] = (center.y - raig.initialPoint().y) / raig.dirVector().y;//tapa inferior
            t[3] = (center.y + height - raig.initialPoint().y) / raig.dirVector().y;//tapa superior

            vec3 p = raig.pointAtParameter(t[2]);
            if (t[2]<t_min || t[2]> t_max || (pow(p.x - center.x, 2) + pow(p.z - center.z, 2) - pow(radius, 2)) > 0) {
                t[2] = HUGE_VALF;
            }

            p = raig.pointAtParameter(t[3]);
            if (t[3]<t_min || t[3]> t_max || (pow(p.x - center.x, 2) + pow(p.z - center.z, 2) - pow(radius, 2)) > 0) {
                t[3] = HUGE_VALF;
            }
        }
        //Si alguna de las intersecciones no es válida miramos también las tapas del cilindro.

        //Cogemos el mínimo.
        float min = t[0];
        int index_min = 0;

        for( int i = 1; i < 4 ; i ++){
            if(t[i] < min){
                index_min=i;
                min=t[i];
            }
        }
        if(min==HUGE_VALF || min<t_min || min>t_max){
            return false;
        }
        info.t = min;
        info.p = raig.pointAtParameter(info.t);
        info.mat_ptr = material;

        //Si la intersección seleccionada es con la superficie curva...
        if(index_min<2){
            /* Calculamos la normal como si el punto de intersección estuviera a la altura de la misma
             * base del cilindro. */
            info.normal = (vec3(info.p.x,center.y,info.p.z)-center)/radius;
        }
            //Si la intersección es con la tapa inferior
        else if(index_min==2){
            info.normal = vec3(0,-1,0);
        }
            //Si la intersección es con la tapa superior
        else{
            info.normal = vec3(0,1,0);
        }
        return true;
    }

    return false;
}
void Cylinder::aplicaTG(TG *t) {
    if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }else if (dynamic_cast<Scale *>(t)) {
        /*
         * Scale solo cambia el radio con la componente x, no cambia con el componente z.
         */
        vec4 v(1,1,1,1);
        height = height * v.y;
        radius = radius * v.x;
    }
}