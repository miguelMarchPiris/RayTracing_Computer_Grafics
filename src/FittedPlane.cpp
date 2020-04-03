#include "FittedPlane.h"

FittedPlane::FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d) : Plane(normal, pass_point, d){
    this->minpoint = pass_min;
    this->maxpoint = pass_max;
}

bool FittedPlane::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const{
    if(Plane::intersection(r,t_min,t_max, info))
        if(info.p.x <= maxpoint.x && info.p.x >= minpoint.x && info.p.z <= maxpoint.y && info.p.z >= minpoint.y)
            return true;

    return false;
}

void FittedPlane::aplicaTG(TG *t){
    if (dynamic_cast<Translate *>(t)) {
        //Mourem el pla al voltant del seu pass_point
        vec4 c(point, 1.0);
        c = t->getTG() * c;
        point.x = c.x; point.y = c.y; point.z = c.z;
    }
    if (dynamic_cast<Scale *>(t)){
        //Nomes tenim en compte els components x i z a l'hora de fer l'escalat
        vec4 cmin(minpoint.x, 1.0, minpoint.y, 1.0);
        vec4 cmax(maxpoint.x, 1.0, maxpoint.y, 1.0);
        cmin = t->getTG() * cmin;
        cmax = t->getTG() * cmax;
        minpoint.x *= cmin.x; minpoint.y *= cmin.z;
        maxpoint.x *= cmax.x; maxpoint.y *= cmax.z;
    }
}
