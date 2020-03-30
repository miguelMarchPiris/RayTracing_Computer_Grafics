//
// Created by desgarrador on 9/3/20.
//

#include <include/Translate.h>
#include "Cylinder.h"
Cylinder::Cylinder(vec3 center, float radius,float h,float data): Object(data){
    this->center=center;
    this->radius=radius;
    this->height=h;
}


bool Cylinder::intersection(const Ray& raig, float t_min, float t_max, IntersectionInfo& info) const{
    float a,b,c;
    float rx,rz,ry;
    float jx, jz;
    rx=raig.dirVector().x;
    //ry=raig.dirVector().y;
    rz=raig.dirVector().z;

    float t_arr[4]={HUGE_VALF,HUGE_VALF,HUGE_VALF,HUGE_VALF};


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
        t_arr[0]=(-b+sqrtf(discriminante))/(2*a);
        aux=raig.pointAtParameter(t_arr[0]).y;
        if( (center.y + height) < aux || aux  < center.y){
            t_arr[0]=HUGE_VALF;
        }
        t_arr[1]=(-b-sqrtf(discriminante))/(2*a);
        aux=raig.pointAtParameter(t_arr[1]).y;
        if( (center.y + height) < aux || aux < center.y){
            t_arr[1]=HUGE_VALF;
        }

        //Si alguna de las intersecciones no es válida miramos también las tapas del cilindro.
        if(t_arr[0]==HUGE_VALF || t_arr[1]==HUGE_VALF){
            t_arr[2]=(center.y        - raig.initialPoint().y)/raig.dirVector().y;//tapa inferior
            t_arr[3]=(center.y+height - raig.initialPoint().y)/raig.dirVector().y;//tapa superior

            vec3 p = raig.pointAtParameter(t_arr[2]);
            if((pow(p.x-center.x,2) + pow(p.z-center.z,2) - pow(radius,2)) > 0){
                t_arr[2]=HUGE_VALF;
            }

            p = raig.pointAtParameter(t_arr[3]);
            if((pow(p.x-center.x,2) + pow(p.z-center.z,2) - pow(radius,2)) > 0){
                t_arr[3]=HUGE_VALF;
            }
        }
        //Cogemos el mínimo.
        float min = t_arr[0];
        int index_min = 0;

        for( int i = 1; i < 4 ; i ++){
            if(t_arr[i]<min){
                index_min=i;
                min=t_arr[i];
            }
        }
        if(min==HUGE_VALF){
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
    ///*
        if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions
        vec4 c(center, 1.0);
        c = t->getTG() * c;
        center.x = c.x; center.y = c.y; center.z = c.z;
    }
     //*/

}