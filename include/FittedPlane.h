#ifndef FITTEDPLANE_H
#define FITTEDPLANE_H

#include "Plane.h"
#include "Animation.h"
#include "Translate.h"
#include "Scale.h"

class FittedPlane: public Plane
{
public:
    FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d);
    virtual ~FittedPlane(){}
    virtual bool intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const;
    virtual void aplicaTG(TG *t);


private:
    vec2 minpoint;
    vec2 maxpoint;
};

#endif // FITTEDPLANE_H
