#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"


// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material
{
public:

    Material();
    Material(vec3 a, vec3 d, vec3 s, float o, int sh);
    ~Material();

    virtual bool scatter(const Ray& r_in, const IntersectionInfo& rec, std::vector<vec3>& colors, std::vector<Ray>&r_out) const = 0;
    virtual vec3 getDiffuse(vec2 point)const;

    vec3 Kdiffuse= vec3(0);
    vec3 Kspecular= vec3(0);
    vec3 Kambient= vec3(0);
    vec3 Kt = vec3(0);

    float alpha; // aka opacity
    int shininess;
    double const EPSILON = 0.001;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
