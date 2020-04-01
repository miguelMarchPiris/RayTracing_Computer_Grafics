#include "FittedPlane.h"

FittedPlane::FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d) : Plane(normal, pass_point, d){
    this->minpoint = pass_min;
    this->maxpoint = pass_max;
}

bool FittedPlane::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const{
    if(Plane::intersection(r,t_min,t_max, info)){
        if(info.p.x <= maxpoint.x && info.p.x >= minpoint.x && info.p.z <= maxpoint.y && info.p.z >= minpoint.y){
            //En el momento d ela interseccion con el plano, tomamos el punto de la interseccion y lo hacemos corresponder con un pixel en la imagen
            /*float u = info.p.x;
            float v = info.p.z;
            info.u = u;
            info.v = v;*/
            return true;
        }
    }
    return false;
}

void FittedPlane::aplicaTG(TG *t){
    if (dynamic_cast<Translate *>(t)) {
        //movem el punt de pas del pla
        vec4 c(point, 1.0);
        c = t->getTG() * c;
        point.x = c.x; point.y = c.y; point.z = c.z;
    }
    if (dynamic_cast<Scale *>(t)){
        //consideramos la y del minpoint y maxpoint como la componente z, usamos un vec2 para definir la xmin/max y zmin/max.
        vec4 cmin(minpoint.x, 1.0, minpoint.y, 1.0);
        vec4 cmax(maxpoint.x, 1.0, maxpoint.y, 1.0);
        cmin = t->getTG() * cmin;
        cmax = t->getTG() * cmax;
        minpoint.x *= cmin.x; minpoint.y *= cmin.z;
        maxpoint.x *= cmax.x; maxpoint.y *= cmax.z;
    }
}
